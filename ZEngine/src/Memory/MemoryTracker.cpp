#include "zepch.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

#include "zengine/Memory/DefaultAllocator.hpp"
#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/Logger.hpp"

#include <fstream>

namespace ze
{
   namespace
   {
      constexpr char const* memoryLoggerFileName = "memtrack.log";

      [[maybe_unused]] void LogAllocation(void* pointer, size_t size, SourceLocation const& location) noexcept
      {
         MemoryTracker::UseMemoryLogger().debug().logLine("Allocating %u bytes of memory", size);
         if (location.file)
            MemoryTracker::UseMemoryLogger().debug().logLine("   to 0x%x at %s::%s:%u",
                                                             reinterpret_cast<uintptr_t>(pointer),
                                                             location.file, location.function, location.line);
         else
            MemoryTracker::UseMemoryLogger().debug().logLine("   to 0x%x",
                                                             reinterpret_cast<uintptr_t>(pointer));
      }

      [[maybe_unused]] void LogRelease(void* pointer, size_t size, SourceLocation const& location) noexcept
      {
         if (size)
            MemoryTracker::UseMemoryLogger().debug().logLine("Releasing %u bytes of memory from 0x%x",
                                                             size, reinterpret_cast<uintptr_t>(pointer));
         else
            MemoryTracker::UseMemoryLogger().debug().logLine("Releasing memory from 0x%x",
                                                             reinterpret_cast<uintptr_t>(pointer));

         if (location.file)
            MemoryTracker::UseMemoryLogger().debug().logLine("   at %s::%s:%u",
                                                             location.file, location.function, location.line);
      }

      // TODO Extends allocator concept
      MemoryAllocator& GetAllocator()
      {
         static DefaultAllocator allocator;
         return allocator;
      }
   }

   MemoryTracker::MemoryTracker()
      : m_writer(memoryLoggerFileName), m_logger("MemoryTracker", &m_writer), m_totalAllocations{}, m_sizeAllocated{}
   {
      useMemoryLogger().debug().logLine("------ Memory Tracker started ------");
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
      catch (std::bad_alloc const& e)
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

   Logger& MemoryTracker::UseMemoryLogger()
   {
      return GetInstance().useMemoryLogger();
   }

   size_t MemoryTracker::GetTotalAllocations() noexcept
   {
      return GetInstance().getTotalAllocations();
   }

   size_t MemoryTracker::GetTotalMemoryAllocated() noexcept
   {
      return GetInstance().getTotalMemoryAllocated();
   }

   Logger& MemoryTracker::useMemoryLogger() noexcept
   {
      return m_logger;
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
      useMemoryLogger().debug().logLine("------ Memory Tracker Ended (%u allocations, %u bytes) ------", m_totalAllocations, m_sizeAllocated);
   }
}
