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
            ConsoleWriter::write(name, level, line);

            FILE* file;
            fopen_s(&file, MEMORYLOGGER_FILENAME, "a");

            if (!file)
               return;
            // TODO Error handling

            if (isAtLineBegin())
            {
               Date date = Date::CurrentDate();
               std::tm tm = date.getTm();
               char timeString[9];
               strftime(timeString, 9, "%H:%M:%S", &tm);
               fprintf(file, "[%s] [%s] <%s> ", timeString, LevelToString(level), name.data());

               m_lineStart = false;
            }

            fputs(line.data(), file);

            fclose(file);
         }

         void flush() override
         {
            ConsoleWriter::flush();
         }

         void newLine() override
         {
            ConsoleWriter::newLine();

            FILE* file;
            fopen_s(&file, MEMORYLOGGER_FILENAME, "a");

            if (!file) return;

            fputc('\n', file);
            fclose(file);

            m_lineStart = true;
         }

         MemoryWriter()
            : ConsoleWriter(std::cout), m_lineStart(true)
         {
            FILE* file;
            fopen_s(&file, MEMORYLOGGER_FILENAME, "w+");

            // TODO Error handling

            if (file)
               fclose(file);
         }

      private:
         inline bool isAtLineBegin() const noexcept
         {
            return m_lineStart;
         }

         bool m_lineStart;
      };

      MemoryWriter memWriter; // Custom writer to avoid heap allocation
      Logger s_memoryLogger("MEMORYTRACKER");

      // Debugs deletions
      char const* s_nextFile = nullptr;
      unsigned int s_nextLine = 0;

      // Debug stats
      unsigned int s_totalAllocations = 0;
      size_t s_sizeAllocated = 0;

      // Identification hashes
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

      // Linked list of allocated memory blocks
      Block s_blockList
      {
         0, nullptr, 0, 0,
         &s_blockList, &s_blockList
      };

      Block* AllocateBlock(size_t size, char const* file, unsigned int line)
      {
         Block* block = static_cast<Block*>(std::malloc(size + sizeof(Block)));

         if (block == nullptr)
         {
            s_memoryLogger.logLine(Level::Error, "Unable to allocate %u bytes", size);

            if (file)
               s_memoryLogger.logLine(Level::Error, "   at %s:%o", file, line);
            else
               s_memoryLogger.logLine(Level::Error, "   at undefined position");

            throw std::bad_alloc{};
         }

         return block;
      }

      Block* RetrieveBlock(void* pointer)
      {
         return reinterpret_cast<Block*>(static_cast<uint8_t*>(pointer) - sizeof(Block));
      }

      void InitBlock(Block* block, size_t size, char const* file, unsigned int line)
      {
         block->size = size;
         block->file = file;
         block->line = line;
         block->guardHash = s_allocationHash;
      }

      bool IsBlockDeletable(Block* block)
      {
         if (block->guardHash != s_allocationHash)
            return false;

         return true;
      }

      void DeinitBlock(Block* block)
      {
         block->guardHash = s_releaseHash;
      }

      void PushBlockToList(Block* block)
      {
         block->previous = s_blockList.previous;
         block->next = &s_blockList;

         s_blockList.previous->next = block;
         s_blockList.previous = block;
      }

      void PopBlockFromList(Block* block)
      {
         block->previous->next = block->next;
         block->next->previous = block->previous;
      }

      void IncreaseMemoryStats(size_t size)
      {
         ++s_totalAllocations;
         s_sizeAllocated += size;
      }

      void DecreaseMemoryStats(size_t size)
      {
         --s_totalAllocations;
         s_sizeAllocated -= size;
      }

      void LogAllocation(Block* block, size_t size, char const* file, unsigned int line)
      {
         s_memoryLogger.logLine(Level::Debug, "Allocating %u bytes of memory", size);
         if (file)
            s_memoryLogger.logLine(Level::Debug, "   to 0x%x at %s:%u", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(block) + sizeof(Block)), file, line);
         else
            s_memoryLogger.logLine(Level::Debug, "   to 0x%x at undefined position", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(block) + sizeof(Block)));
      }

      void LogRelease(void* pointer)
      {
         s_memoryLogger.logLine(Level::Debug, "Deallocating 0x%x", reinterpret_cast<uintptr_t>(pointer));
         if (s_nextFile)
            s_memoryLogger.logLine(Level::Debug, "   at %s:%u", s_nextFile, s_nextLine);
         else
            s_memoryLogger.logLine(Level::Debug, "   at undefined position");
      }

      void TraceLeaks()
      {
         Block* leakedPointer = s_blockList.next;
         while (leakedPointer != &s_blockList)
         {
            s_memoryLogger.logLine(Level::Error, "--- ", leakedPointer->size, " bytes");
            if (leakedPointer->file)
               s_memoryLogger.logLine(Level::Error, "---    at 0x%x %s:%u", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)), leakedPointer->file, leakedPointer->line);
            else
               s_memoryLogger.logLine(Level::Error, "---    at 0x%x", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)));

            void* handledLeak = leakedPointer;
            leakedPointer = leakedPointer->next;

            std::free(handledLeak);
         }
      }
   }

   void MemoryManager::Initialise()
   {
      static MemoryManager instance; // This instance is used to RAII termination of memory tracker

      s_memoryLogger.setWriter(&memWriter);
      s_memoryLogger.logLine(Level::Info, "------ Memory Tracker Started ------");

      s_isInitialised = true;
   }

   void* MemoryManager::Allocate(size_t size, char const* file, unsigned int line)
   {
      if (!s_isInitialised)
         MemoryManager::Initialise();

      Block* allocatedBlock = AllocateBlock(size, file, line);
      InitBlock(allocatedBlock, size, file, line);
      PushBlockToList(allocatedBlock);
      IncreaseMemoryStats(size);

      #ifdef ZE_DEBUG_LOG_MEMORYALLOC
         LogAllocation(allocatedBlock, size, file, line);
      #endif

      return reinterpret_cast<uint8_t*>(allocatedBlock) + sizeof(Block);
   }

   void MemoryManager::NextRelease(char const* file, unsigned int line) noexcept
   {
      s_nextFile = file;
      s_nextLine = line;
   }

   void MemoryManager::Release(void* pointer) noexcept
   {
      if (pointer == nullptr) return;

      Block* allocatedBlock = RetrieveBlock(pointer);

      if (!IsBlockDeletable(allocatedBlock))
      {
         s_memoryLogger.logLine(Level::Error, allocatedBlock->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion");
         if (s_nextFile)
            s_memoryLogger.logLine(Level::Error, "   at %s:%u", s_nextFile,s_nextLine);
         else
            s_memoryLogger.logLine(Level::Error, "   at undefined position");
         return;
      }

      DeinitBlock(allocatedBlock);
      PopBlockFromList(allocatedBlock);
      DecreaseMemoryStats(allocatedBlock->size);

      #ifdef ZE_DEBUG_LOG_MEMORYALLOC
         LogRelease(pointer);
      #endif

      std::free(allocatedBlock);

      NextRelease(nullptr, 0); // Reset release data
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
         s_memoryLogger.logLine(Level::Info, "------ Memory Tracker Ended with no leak ------");
      else
      {
         s_memoryLogger.logLine(Level::Error, "--- Memory Tracker registered %u leaks ! ------", GetTotalAllocations());
         s_memoryLogger.logLine(Level::Error, "--- %u bytes leaked", GetTotalMemoryAllocated());
         s_memoryLogger.logLine(Level::Error, "--- Leaks trace");

         TraceLeaks();
      }
   }

   MemoryManager::~MemoryManager()
   {
      Terminate();
   }
}
