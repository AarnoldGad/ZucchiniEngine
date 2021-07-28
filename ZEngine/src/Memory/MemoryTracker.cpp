#include "zepch.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

#include "zengine/Log/ConsoleWriter.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Time/Date.hpp"

#include <fstream>

namespace ze
{
   namespace
   {
      constexpr char const* memoryLoggerFileName = "memtrack.log";

      // Identification hashes
      constexpr unsigned int s_allocationHash = 0xA110CA73; // Identify a block allocated with this manager
      constexpr unsigned int s_releaseHash = 0xF533D; // Identify a block freed

      class MemoryWriter : public ConsoleWriter
      {
      public:
         void write(std::string_view name, Logger::Level level, std::string_view line) override;
         void flush() override;
         void newLine() override;

         MemoryWriter();

      private:
         bool isAtLineBegin() const noexcept;
         void printDate(FILE* file, std::string_view name, Logger::Level level);

         bool m_lineStart;
      };

      class MemoryAllocator
      {
      public:
         struct Block
         {
            size_t size;
            char const* file;
            unsigned int line;
            unsigned int guardHash; // c.f s_allocationHash / s_releaseHash

            Block* previous;
            Block* next;
         };

         Logger& useMemoryLogger() noexcept;

         size_t getTotalAllocations() const noexcept;
         size_t getMemoryAllocated() const noexcept;

         void* allocate(size_t size, char const* file, unsigned int line);
         void nextRelease(char const* file, unsigned int line) noexcept;
         void release(void* pointer) noexcept;

         MemoryAllocator();
         ~MemoryAllocator();

      private:
         Block* allocateBlock(size_t size, char const* file, unsigned int line);
         Block* retrieveBlock(void* pointer) noexcept;

         void initBlock(Block* block, size_t size, char const* file, unsigned int line) const noexcept;
         void deinitBlock(Block* block) const noexcept;

         bool isBlockDeletable(Block* block) const noexcept;

         void pushBlockToList(Block* block) noexcept;
         void popBlockFromList(Block* block) noexcept;

         void increaseMemoryStats(size_t size) noexcept;
         void decreaseMemoryStats(size_t size) noexcept;

         void logAllocation(Block* block, size_t size, char const* file, unsigned int line);
         void logRelease(void* pointer) noexcept;

         void traceLeaks();

      private:
         Block m_blockList;

         MemoryWriter m_writer;
         Logger m_logger;

         // Debugs deletions
         char const* m_nextFile;
         unsigned int m_nextLine;

         // Debug stats
         size_t m_totalAllocations;
         size_t m_sizeAllocated;
      };

      MemoryWriter::MemoryWriter()
         : ConsoleWriter(std::cout), m_lineStart(true)
      {
         FILE* file = fopen(memoryLoggerFileName, "a");

         // TODO Error handling

         if (file)
            fclose(file);
      }

      void MemoryWriter::write(std::string_view name, Logger::Level level, std::string_view line)
      {
         ConsoleWriter::write(name, level, line);

         FILE* file = fopen(memoryLoggerFileName, "a");

         if (!file)
            return;
         // TODO Error handling

         if (isAtLineBegin())
            printDate(file, name, level);

         fputs(line.data(), file);

         fclose(file);
      }

      void MemoryWriter::flush()
      {
         ConsoleWriter::flush();
      }

      void MemoryWriter::newLine()
      {
         ConsoleWriter::newLine();

         FILE* file = fopen(memoryLoggerFileName, "a");

         if (!file) return;

         fputc('\n', file);
         fclose(file);

         m_lineStart = true;
      }

      inline bool MemoryWriter::isAtLineBegin() const noexcept
      {
         return m_lineStart;
      }

      inline void MemoryWriter::printDate(FILE* file, std::string_view name, Logger::Level level)
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         char timeString[9];
         strftime(timeString, 9, "%H:%M:%S", &tm);
         fprintf(file, "[%s] [%s] <%s> ", timeString, Logger::LevelToString(level), name.data());

         m_lineStart = false;
      }

      MemoryAllocator::MemoryAllocator()
         : m_blockList{ 0, nullptr, 0, 0, &m_blockList, &m_blockList },
           m_writer{}, m_logger("MEMORYTRACKER", &m_writer),
           m_nextFile(nullptr), m_nextLine{},
           m_totalAllocations{}, m_sizeAllocated{}
      {
         useMemoryLogger().logLine(Logger::Level::Info, "------ Memory Tracker Started ------");
      }

      inline Logger& MemoryAllocator::useMemoryLogger() noexcept
      {
         return m_logger;
      }

      inline size_t MemoryAllocator::getTotalAllocations() const noexcept
      {
         return m_totalAllocations;
      }

      inline size_t MemoryAllocator::getMemoryAllocated() const noexcept
      {
         return m_sizeAllocated;
      }

      void* MemoryAllocator::allocate(size_t size, char const* file, unsigned int line)
      {
         Block* allocatedBlock = allocateBlock(size, file, line);
         initBlock(allocatedBlock, size, file, line);
         pushBlockToList(allocatedBlock);
         increaseMemoryStats(size);

         #ifdef ZE_DEBUG_LOG_MEMORYALLOC
            logAllocation(allocatedBlock, size, file, line);
         #endif

         return reinterpret_cast<uint8_t*>(allocatedBlock) + sizeof(Block);
      }

      void MemoryAllocator::nextRelease(char const* file, unsigned int line) noexcept
      {
         m_nextFile = file;
         m_nextLine = line;
      }

      void MemoryAllocator::release(void* pointer) noexcept
      {
         if (pointer == nullptr) return;

         Block* allocatedBlock = retrieveBlock(pointer);

         if (!isBlockDeletable(allocatedBlock))
         {
            useMemoryLogger().logLine(Logger::Level::Error, allocatedBlock->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion");
            if (m_nextFile)
               useMemoryLogger().logLine(Logger::Level::Error, "   at %s:%u", m_nextFile, m_nextLine);
            else
               useMemoryLogger().logLine(Logger::Level::Error, "   at undefined position");
            return;
         }

         deinitBlock(allocatedBlock);
         popBlockFromList(allocatedBlock);
         decreaseMemoryStats(allocatedBlock->size);

         #ifdef ZE_DEBUG_LOG_MEMORYALLOC
            logRelease(pointer);
         #endif

         std::free(allocatedBlock);

         nextRelease(nullptr, 0); // Reset release data
      }

      MemoryAllocator::Block* MemoryAllocator::allocateBlock(size_t size, char const* file, unsigned int line)
      {
         Block* block = static_cast<Block*>(std::malloc(size + sizeof(Block)));

         if (block == nullptr)
         {
            useMemoryLogger().logLine(Logger::Level::Error, "Unable to allocate %u bytes", size);

            if (file)
               useMemoryLogger().logLine(Logger::Level::Error, "   at %s:%o", file, line);
            else
               useMemoryLogger().logLine(Logger::Level::Error, "   at undefined position");

            throw std::bad_alloc{};
         }

         return block;
      }

      MemoryAllocator::Block* MemoryAllocator::retrieveBlock(void* pointer) noexcept
      {
         return reinterpret_cast<Block*>(static_cast<uint8_t*>(pointer) - sizeof(Block));
      }

      void MemoryAllocator::initBlock(Block* block, size_t size, char const* file, unsigned int line) const noexcept
      {
         block->size = size;
         block->file = file;
         block->line = line;
         block->guardHash = s_allocationHash;
      }

      bool MemoryAllocator::isBlockDeletable(Block* block) const noexcept
      {
         if (block->guardHash != s_allocationHash)
            return false;

         return true;
      }

      void MemoryAllocator::deinitBlock(Block* block) const noexcept
      {
         block->guardHash = s_releaseHash;
      }

      void MemoryAllocator::pushBlockToList(Block* block) noexcept
      {
         block->previous = m_blockList.previous;
         block->next = &m_blockList;

         m_blockList.previous->next = block;
         m_blockList.previous = block;
      }

      void MemoryAllocator::popBlockFromList(Block* block) noexcept
      {
         block->previous->next = block->next;
         block->next->previous = block->previous;
      }

      void MemoryAllocator::increaseMemoryStats(size_t size) noexcept
      {
         ++m_totalAllocations;
         m_sizeAllocated += size;
      }

      void MemoryAllocator::decreaseMemoryStats(size_t size) noexcept
      {
         --m_totalAllocations;
         m_sizeAllocated -= size;
      }

      void MemoryAllocator::logAllocation(Block* block, size_t size, char const* file, unsigned int line)
      {
         useMemoryLogger().logLine(Logger::Level::Debug, "Allocating %u bytes of memory", size);
         if (file)
            useMemoryLogger().logLine(Logger::Level::Debug, "   to 0x%x at %s:%u", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(block) + sizeof(Block)), file, line);
         else
            useMemoryLogger().logLine(Logger::Level::Debug, "   to 0x%x at undefined position", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(block) + sizeof(Block)));
      }

      void MemoryAllocator::logRelease(void* pointer) noexcept
      {
         useMemoryLogger().logLine(Logger::Level::Debug, "Deallocating 0x%x", reinterpret_cast<uintptr_t>(pointer));
         if (m_nextFile)
            useMemoryLogger().logLine(Logger::Level::Debug, "   at %s:%u", m_nextFile, m_nextLine);
         else
            useMemoryLogger().logLine(Logger::Level::Debug, "   at undefined position");
      }

      void MemoryAllocator::traceLeaks()
      {
         Block* leakedPointer = m_blockList.next;
         while (leakedPointer != &m_blockList)
         {
            useMemoryLogger().logLine(Logger::Level::Error, "--- ", leakedPointer->size, " bytes");
            if (leakedPointer->file)
               useMemoryLogger().logLine(Logger::Level::Error, "---    at 0x%x %s:%u", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)), leakedPointer->file, leakedPointer->line);
            else
               useMemoryLogger().logLine(Logger::Level::Error, "---    at 0x%x", reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)));

            void* handledLeak = leakedPointer;
            leakedPointer = leakedPointer->next;

            std::free(handledLeak);
         }
      }

      MemoryAllocator::~MemoryAllocator()
      {
         if (m_totalAllocations == 0)
            useMemoryLogger().logLine(Logger::Level::Info, "------ Memory Tracker Ended with no leak ------");
         else
         {
            useMemoryLogger().logLine(Logger::Level::Error, "--- Memory Tracker registered %u leaks ! ------", m_totalAllocations);
            useMemoryLogger().logLine(Logger::Level::Error, "--- %u bytes leaked", m_sizeAllocated);
            useMemoryLogger().logLine(Logger::Level::Error, "--- Leaks trace");

            traceLeaks();
         }
      }

      MemoryAllocator& GetAllocator()
      {
         static MemoryAllocator allocator;
         return allocator;
      }
   }

   void* MemoryTracker::Allocate(size_t size, char const* file, unsigned int line)
   {
      return GetAllocator().allocate(size, file, line);
   }

   void MemoryTracker::NextRelease(char const* file, unsigned int line) noexcept
   {
      GetAllocator().nextRelease(file, line);
   }

   void MemoryTracker::Release(void* pointer) noexcept
   {
      GetAllocator().release(pointer);
   }

   size_t MemoryTracker::GetTotalAllocations() noexcept
   {
      return GetAllocator().getTotalAllocations();
   }

   size_t MemoryTracker::GetTotalMemoryAllocated() noexcept
   {
      return GetAllocator().getMemoryAllocated();
   }
}
