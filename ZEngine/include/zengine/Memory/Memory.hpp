/**
 * Memory.hpp
 * 24 Apr 2021
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
#ifndef ZE_MEMORY_HPP
#define ZE_MEMORY_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Memory/MemoryManager.hpp"

#include <cstdlib>

#if defined(_WIN32)
   #pragma warning(disable:4595)
#endif

inline void* operator new(size_t size) // Sufficient to handle all standard allocations (No new[] needed)
{
   return ze::MemoryManager::Allocate(size);
}

inline void* operator new(size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Allocate(size, file, line);
}

inline void* operator new[](size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Allocate(size, file, line);
}

inline void operator delete(void* pointer) noexcept
{
   ze::MemoryManager::Release(pointer);
}

inline void operator delete[](void* pointer) noexcept
{
   ze::MemoryManager::Release(pointer);
}

inline void operator delete(void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Release(pointer);
}

inline void operator delete[](void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Release(pointer);
}

inline void operator delete(void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryManager::NextRelease(file, line);
   ze::MemoryManager::Release(pointer);
}

inline void operator delete[](void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryManager::NextRelease(file, line);
   ze::MemoryManager::Release(pointer);
}

#if defined(_WIN32)
   #pragma warning(default:4595)
#endif

#endif // ZE_MEMORY_HPP
