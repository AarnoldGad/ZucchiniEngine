#include "zepch.hpp"

#include "zengine/Log/Logger.hpp"
#include "zengine/Log/ConsoleWriter.hpp"
#include "zengine/Memory/MemoryManager.hpp"
#include "zengine/Time/Date.hpp"

#include <fstream>

#define MEMORYLOGGER_FILENAME "memtrack.log"

namespace ze
{
   namespace
   {
      class MemoryWriter : public ConsoleWriter
      {
      public:
         void write(std::string_view name, Level level, std::string_view line) override
         {
            #if defined(_DEBUG)
               ConsoleWriter::write(name, level, line);
            #endif

            FILE* file = std::fopen(MEMORYLOGGER_FILENAME, "a");

            if (isAtLineBegin())
            {
               Date date = Date::CurrentDate();
               std::tm tm = date.getTm();
               char timeString[9];
               std::strftime(timeString, 9, "%H:%M:%S", &tm);
               std::fprintf(file, "[%s] [%s] <%s>", timeString, LevelToString(level), name.data());
               m_lineStart = false;
            }

            std::fputs(line.data(), file);

            std::fclose(file);
         }

         void flush() override
         {
            ConsoleWriter::flush();
            m_lineStart = true;
         }

         MemoryWriter()
            : ConsoleWriter(std::cout), m_lineStart(true)
         {
            FILE* file = std::fopen(MEMORYLOGGER_FILENAME, "w+");

            // TODO Error handling

            std::fclose(file);
         }

      private:
         inline bool isAtLineBegin() const noexcept
         {
            return m_lineStart;
         }

         bool m_lineStart;
      };
      
      MemoryWriter memWriter; // Custom writer to avoid heap allocation
      Logger s_memoryLogger("MEMORY");

      char const* s_nextFile = nullptr;
      unsigned int s_nextLine = 0;

      unsigned int s_totalAllocations = 0;
      size_t s_sizeAllocated = 0;

      const unsigned int s_allocationHash = 0xA110CA73; // Identify a block allocated with this manager
      const unsigned int s_releaseHash = 0xF533D; // Identify a block freed

      bool s_isInitialised = false;

      struct Block
      {
         size_t size;
         char const* file;
         unsigned int line;
         unsigned int guardHash; // c.f s_allocationHash / s_releaseHash

         Block* previous;
         Block* next;
      };

      Block s_blockList
      {
         0, nullptr, 0, 0,
         &s_blockList, &s_blockList
      };
   }

   void MemoryManager::Initialise()
   {
      static MemoryManager instance;

      s_memoryLogger.setWriter(&memWriter);
      s_memoryLogger.info() << "------ Memory Tracker Started ------" << Logger::newLine;

      s_isInitialised = true;
   }

   void* MemoryManager::Allocate(size_t size, char const* file, unsigned int line)
   {
      if (!s_isInitialised)
         MemoryManager::Initialise();

      Block* allocated = (Block*) std::malloc(size + sizeof(Block));
      if (allocated == nullptr)
      {
         s_memoryLogger.logLine(Level::Error, "Unable to allocate %u bytes", size);
         if (file)
            s_memoryLogger.logLine(Level::Error, "   at %s:%o", file, line);
         else
            s_memoryLogger.logLine(Level::Error, "   at undefined position");
         throw std::bad_alloc{};
      }

      allocated->size = size;
      allocated->file = file;
      allocated->line = line;
      allocated->guardHash = s_allocationHash;

      allocated->previous = s_blockList.previous;
      allocated->next = &s_blockList;

      s_blockList.previous->next = allocated;
      s_blockList.previous = allocated;

      ++s_totalAllocations;
      s_sizeAllocated += size;

      #if _DEBUG
         s_memoryLogger.logLine(Level::Debug, "Allocating %u bytes of memory", size);
         if (file) 
            s_memoryLogger.logLine(Level::Debug, "   at 0x%x %s:%u", (size_t)(reinterpret_cast<uint8_t*>(allocated) + sizeof(Block)), file, line);
         else
            s_memoryLogger.logLine(Level::Debug, "   at 0x%x undefined position", (size_t)(reinterpret_cast<uint8_t*>(allocated) + sizeof(Block)));
      #endif

      return reinterpret_cast<uint8_t*>(allocated) + sizeof(Block);
   }

   void MemoryManager::NextRelease(char const* file, unsigned int line) noexcept
   {
      s_nextFile = file;
      s_nextLine = line;
   }

   void MemoryManager::Release(void* pointer) noexcept
   {
      if (pointer == nullptr) return;

      Block* allocated = reinterpret_cast<Block*>(static_cast<uint8_t*>(pointer) - sizeof(Block));
      if (allocated->guardHash != s_allocationHash)
      {
         s_memoryLogger.logLine(Level::Error, allocated->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion");
         if (s_nextFile)
            s_memoryLogger.logLine(Level::Error, "   at %s:%u", s_nextFile,s_nextLine);
         else
            s_memoryLogger.logLine(Level::Error, "   at undefined position");
         return;
      }
      
      allocated->guardHash = s_releaseHash;
      allocated->previous->next = allocated->next;
      allocated->next->previous = allocated->previous;

      --s_totalAllocations;
      s_sizeAllocated -= allocated->size;

      #if _DEBUG
      s_memoryLogger.logLine(Level::Debug, "Deallocating 0x%x", (size_t)(pointer));
      if (s_nextFile)
         s_memoryLogger.logLine(Level::Debug, "   at %s:%u", s_nextFile, s_nextLine);
      else
         s_memoryLogger.logLine(Level::Debug, "   at undefined position");
      #endif

      std::free(allocated);
      
      s_nextFile = nullptr;
      s_nextLine = 0;
   }

   size_t MemoryManager::GetTotalAllocations() noexcept
   {
      return s_totalAllocations;
   }

   size_t MemoryManager::GetTotalMemoryAllocated() noexcept
   {
      return s_sizeAllocated;
   }

   void MemoryManager::Terminate()
   {
      if (s_totalAllocations == 0)
         s_memoryLogger.info() << "------ Memory Tracker Ended with no leak ------" << Logger::newLine;
      else
      {
         s_memoryLogger.logLine(Level::Error, "--- Memory Tracker registered %u leaks ! ------", GetTotalAllocations());
         s_memoryLogger.logLine(Level::Error, "--- %u bytes leaked", GetTotalMemoryAllocated());
         s_memoryLogger.logLine(Level::Error, "--- Leaks trace");
         
         Block* pointer = s_blockList.next;
         while (pointer != &s_blockList)
         {
            s_memoryLogger.logLine(Level::Error, "--- ", pointer->size, " bytes");
            if (pointer->file)
               s_memoryLogger.logLine(Level::Error, "---    at 0x%x %s:%u", (size_t)(reinterpret_cast<uint8_t*>(pointer) + sizeof(Block)), pointer->file, pointer->line);
            else
               s_memoryLogger.logLine(Level::Error, "---    at 0x%x", (size_t)(reinterpret_cast<uint8_t*>(pointer) + sizeof(Block)));

            void* leak = pointer;
            pointer = pointer->next;

            std::free(leak);
         }
      }
   }

   MemoryManager::~MemoryManager()
   {
      Terminate();
   }
}
