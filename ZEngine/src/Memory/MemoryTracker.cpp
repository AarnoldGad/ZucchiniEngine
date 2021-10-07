#include "zepch.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

#include "zengine/Memory/DefaultAllocator.hpp"

#include <fstream>

namespace ze
{
   namespace
   {
      [[maybe_unused]] void LogAllocation(void* pointer, size_t size, SourceLocation const& location) noexcept
      {
         MemoryTracker::MemoryLog("Allocating %u bytes of memory", size);
         if (location.file)
            MemoryTracker::MemoryLog("   to 0x%x at %s::%s:%u", reinterpret_cast<uintptr_t>(pointer),
                      location.file, location.function, location.line);
         else
            MemoryTracker::MemoryLog("   to 0x%x",  reinterpret_cast<uintptr_t>(pointer));
      }

      [[maybe_unused]] void LogRelease(void* pointer, size_t size, SourceLocation const& location) noexcept
      {
         if (size)
            MemoryTracker::MemoryLog("Releasing %u bytes of memory from 0x%x", size, reinterpret_cast<uintptr_t>(pointer));
         else
            MemoryTracker::MemoryLog("Releasing memory from 0x%x", reinterpret_cast<uintptr_t>(pointer));

         if (location.file)
            MemoryTracker::MemoryLog("   at %s::%s:%u", location.file, location.function, location.line);
      }

      // TODO Extends allocator concept
      MemoryAllocator& GetAllocator()
      {
         static DefaultAllocator allocator;
         return allocator;
      }
   }

   void MemoryTracker::MemoryLog(char const* line)
   {
      FILE* file = fopen("memtrack.log", "a");
      if (!file)
         return LOG_TRACE("Fail to open memory log file");

      char timeBuf[9];
      time_t date = std::time(nullptr);
      std::strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", std::localtime(&date));

      fprintf(file, "[%s] ", timeBuf);
      fputs(line, file);
      fprintf(file, "\n");

      printf("[%s] %s\n", timeBuf, line);

      fclose(file);
   }

   MemoryTracker::MemoryTracker()
      : m_totalAllocations{}, m_sizeAllocated{}
   {
      FILE* logFile = fopen("memtrack.log", "w+");

      if (logFile)
         fclose(logFile);
      else
         LOG_TRACE("Fail to open memory log file : ", std::strerror(errno));

      MemoryTracker::MemoryLog("------ Memory Tracker Started ------");
   }

   MemoryTracker& MemoryTracker::GetInstance()
   {
      static MemoryTracker instance;
      return instance;
   }

   void* MemoryTracker::Allocate(size_t size, SourceLocation const& location)
   {
      try
      {
         void* pointer = GetAllocator().allocate(size, location);
         GetInstance().increaseMemoryStats(size);
         #if defined(ZE_DEBUG_LOG_MEMORYALLOC)
            LogAllocation(pointer, size, location);
         #endif
         return pointer;
      }
      catch (std::bad_alloc const&)
      {
         throw;
      }
   }

   void MemoryTracker::NextRelease(SourceLocation const& location) noexcept
   {
      GetInstance().m_nextRelease = location;
   }

   void MemoryTracker::Release(void* pointer, size_t size) noexcept
   {
      size_t sizeReleased = GetAllocator().release(pointer, size, GetInstance().m_nextRelease);
      GetInstance().decreaseMemoryStats(sizeReleased);
      #if defined(ZE_DEBUG_LOG_MEMORYALLOC)
         LogRelease(pointer, size, GetInstance().m_nextRelease);
      #endif
      NextRelease({ nullptr, 0, nullptr });
   }

   size_t MemoryTracker::GetTotalAllocations() noexcept
   {
      return GetInstance().getTotalAllocations();
   }

   size_t MemoryTracker::GetTotalMemoryAllocated() noexcept
   {
      return GetInstance().getTotalMemoryAllocated();
   }

   void MemoryTracker::increaseMemoryStats(size_t size) noexcept
   {
      ++m_totalAllocations;
      m_sizeAllocated += size;
   }

   void MemoryTracker::decreaseMemoryStats(size_t size) noexcept
   {
      --m_totalAllocations;
      m_sizeAllocated -= size;
   }

   size_t MemoryTracker::getTotalAllocations() const noexcept
   {
      return m_totalAllocations;
   }

   size_t MemoryTracker::getTotalMemoryAllocated() const noexcept
   {
      return m_sizeAllocated;
   }

   MemoryTracker::~MemoryTracker()
   {
      MemoryTracker::MemoryLog("------ Memory Tracker Ended (remaining %u allocations, %u bytes) ------", m_totalAllocations, m_sizeAllocated);
   }
}
