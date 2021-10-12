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

#include "zapi/defines.hpp"

#include "zapi/Memory/StandardAllocator.hpp"

#define ALLOCATE(...) ze::New(__VA_ARGS__, CURRENT_SOURCE_LOCATION)
#define RELEASE(...) ze::Delete(__VA_ARGS__, CURRENT_SOURCE_LOCATION)

namespace ze
{
   ZE_API StandardAllocator& GetStandardAllocator() noexcept;
   
   ZE_API void* Allocate(size_t size, SourceLocation const& location);
   ZE_API void* Allocate(size_t size, Allocator* allocator, SourceLocation const& location);
   ZE_API void Release(void* pointer, SourceLocation const& location) noexcept;
   ZE_API void Release(void* pointer, Allocator* allocator, SourceLocation const& location) noexcept;
}

#endif /* ZE_NEW_HPP */