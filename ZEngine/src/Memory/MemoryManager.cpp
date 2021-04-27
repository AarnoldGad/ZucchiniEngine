#include "zepch.hpp"

#include "zengine/Log/Logger.hpp"
#include "zengine/Memory/MemoryManager.hpp"

#include <fstream>

namespace ze
{
   namespace
   {
      std::ofstream s_memoryLogFile;
      Logger s_memoryLogger("MEMORY", nullptr, true); // Allocation functions should be "heap allocation free". Don't use Logger::logFormattedLine as it uses std::strings !

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

      // TODO File Utils
      s_memoryLogFile.open("memory.log");
      if (!s_memoryLogFile.is_open())
         LOG_TRACE("Unable to open memory log !");
      else
         s_memoryLogger.setOutput(s_memoryLogFile);

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
         s_memoryLogger.logLine(Logger::ERR, "Unable to allocate ", size, " bytes");
         if (file)
            s_memoryLogger.logLine(Logger::ERR, "   at ", file, ":", line);
         else
            s_memoryLogger.logLine(Logger::ERR, "   at undefined position");
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
         s_memoryLogger.logLine(Logger::DEBUG, "Allocating ", size, " bytes of memory");
         if (file) 
            s_memoryLogger.logLine(Logger::DEBUG, "   at ", file, ":", line);
         else
            s_memoryLogger.logLine(Logger::DEBUG, "   at undefined position");
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
         s_memoryLogger.logLine(Logger::ERR, allocated->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion");
         if (s_nextFile)
            s_memoryLogger.logLine(Logger::ERR, "   at ", s_nextFile, ":", s_nextLine);
         else
            s_memoryLogger.logLine(Logger::ERR, "   at undefined position");
         return;
      }
      
      allocated->guardHash = s_releaseHash;
      allocated->previous->next = allocated->next;
      allocated->next->previous = allocated->previous;

      --s_totalAllocations;
      s_sizeAllocated -= allocated->size;

      #if _DEBUG
      s_memoryLogger.logLine(Logger::DEBUG, "Deallocating 0x", std::hex, (size_t)(pointer), std::dec);
      if (s_nextFile)
         s_memoryLogger.logLine(Logger::DEBUG, "   at ", s_nextFile, ":", s_nextLine);
      else
         s_memoryLogger.logLine(Logger::DEBUG, "   at undefined position");
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
         s_memoryLogger.logLine(Logger::ERR, "--- Memory Tracker registered ", GetTotalAllocations(), " leaks ! ------");
         s_memoryLogger.logLine(Logger::ERR, "--- ", s_sizeAllocated, " bytes leaked");
         s_memoryLogger.logLine(Logger::ERR, "--- Leaks trace");
         
         Block* pointer = s_blockList.next;
         while (pointer != &s_blockList)
         {
            s_memoryLogger.logLine(Logger::ERR, "--- ", pointer->size, " bytes");
            if (pointer->file)
               s_memoryLogger.logLine(Logger::ERR, "---    at 0x", std::hex, (size_t)(reinterpret_cast<uint8_t*>(pointer) + sizeof(Block)), std::dec, " ", pointer->file, ":", pointer->line);
            else
               s_memoryLogger.logLine(Logger::ERR, "---    at 0x", std::hex, (size_t)(reinterpret_cast<uint8_t*>(pointer) + sizeof(Block)), std::dec);

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
