/**
 * MemoryTracker.hpp
 * 6 Mar 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_MEMORYTRACKER_HPP
#define ZE_MEMORYTRACKER_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/Logger.hpp"

#include <cstdlib>
#include <array>

namespace ze
{
   class ZE_API MemoryTracker final
   {
   public:
      static void* Allocate(size_t size, SourceLocation const& location = { nullptr, 0, nullptr });

      template<typename... Args>
      static void MemoryLog(char const* format, Args&&... args);
      static void MemoryLog(char const* line);

      static void NextRelease(SourceLocation const& location) noexcept;
      static void Release(void* pointer, size_t size = 0) noexcept;

      static size_t GetTotalAllocations() noexcept;
      static size_t GetTotalMemoryAllocated() noexcept;

   private:
      static MemoryTracker& GetInstance();

      size_t getTotalAllocations() const noexcept;
      size_t getTotalMemoryAllocated() const noexcept;

      void increaseMemoryStats(size_t) noexcept;
      void decreaseMemoryStats(size_t) noexcept;

      MemoryTracker();
      ~MemoryTracker();

      MemoryTracker(MemoryTracker const&) = delete;
      MemoryTracker(MemoryTracker&&) = delete;
      MemoryTracker& operator=(MemoryTracker const&) = delete;
      MemoryTracker& operator=(MemoryTracker&&) = delete;

   private:
      size_t m_totalAllocations;
      size_t m_sizeAllocated;

      SourceLocation m_nextRelease;
   };
}

#include "MemoryTracker.inl"

#endif // ZE_MEMORYTRACKER_HPP
