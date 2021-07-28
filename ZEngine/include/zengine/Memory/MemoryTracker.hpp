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

#include <cstdlib>

namespace ze
{
   class ZE_API MemoryTracker final
   {
   public:
      static void* Allocate(size_t size, char const* file = nullptr, unsigned int line = 0);

      static void NextRelease(char const* file, unsigned int line) noexcept;
      static void Release(void* pointer) noexcept;

      static size_t GetTotalAllocations() noexcept;
      static size_t GetTotalMemoryAllocated() noexcept;

   private:
      MemoryTracker() = delete;
      MemoryTracker(MemoryTracker const&) = delete;
      MemoryTracker(MemoryTracker&&) = delete;
      MemoryTracker& operator=(MemoryTracker const&) = delete;
      MemoryTracker& operator=(MemoryTracker&&) = delete;
      ~MemoryTracker() = delete;
   };
}

#endif // ZE_MEMORYTRACKER_HPP
