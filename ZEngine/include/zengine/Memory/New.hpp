/**
 * New.hpp
 * 12 Oct 2021
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
#ifndef ZE_NEW_HPP
#define ZE_NEW_HPP

#include "zengine/defines.hpp"

#include "zengine/Memory/StandardAllocator.hpp"

#define ALLOCATE_1(count, type) ze::Allocate<type>(sizeof(type) * count, CURRENT_SOURCE_LOCATION)
#define ALLOCATE_2(count, type, allocator) ze::Allocate<type>(sizeof(type) * count, CURRENT_SOURCE_LOCATION, &allocator)

#define FIND_ALLOCATE_FN(_1, _2, _3, ALLOCATE_FN, ...) ALLOCATE_FN
#define ALLOCATE(...) FIND_ALLOCATE_FN(__VA_ARGS__, ALLOCATE_2, ALLOCATE_1)(__VA_ARGS__)

#define RELEASE(...) ze::Release(__VA_ARGS__, CURRENT_SOURCE_LOCATION)

namespace ze
{
   template<typename PtrType>
   PtrType* Allocate(size_t size, SourceLocation const& location);
   template<typename PtrType>
   PtrType* Allocate(size_t size, SourceLocation const& location, Allocator* allocator);

   ZE_API void Release(void* pointer, SourceLocation const& location) noexcept;
   ZE_API void Release(void* pointer, Allocator* allocator, SourceLocation const& location) noexcept;
}

#include "New.inl"

#endif /* ZE_NEW_HPP */
