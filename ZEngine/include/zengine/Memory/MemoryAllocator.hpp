/**
 * Allocator.hpp
 * 12 Aug 2021
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
#ifndef ZE_ALLOCATOR_HPP
#define ZE_ALLOCATOR_HPP

#include "zengine/zemacros.hpp"

namespace ze
{
   class MemoryAllocator
   {
   public:
      virtual void* allocate(size_t size, SourceLocation const& location) = 0;
      virtual size_t release(void* pointer, size_t size, SourceLocation const& location) noexcept = 0;

      MemoryAllocator() = default;
      MemoryAllocator(MemoryAllocator const&) = delete;
      MemoryAllocator(MemoryAllocator&&) = delete;
      MemoryAllocator& operator=(MemoryAllocator const&) = delete;
      MemoryAllocator& operator=(MemoryAllocator&&) = delete;
   };
}

#endif /* ZE_ALLOCATOR_HPP */
