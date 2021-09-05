/**
 * Memory.hpp
 * 24 Apr 2021
 * Ga�tan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Ga�tan Jalin
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
#ifndef ZE_MEMORY_HPP
#define ZE_MEMORY_HPP

#include "zengine/zemacros.hpp"

#include <cstdlib>

#if !defined(__APPLE__) && !defined(__clang__)
   ZE_API void* operator new(size_t size, SourceLocation const& location);
   ZE_API void* operator new[](size_t size, SourceLocation const& location);

   ZE_API void operator delete(void* pointer, SourceLocation const& location) noexcept;
   ZE_API void operator delete[](void* pointer, SourceLocation const& location) noexcept;
#endif

#endif // ZE_MEMORY_HPP
