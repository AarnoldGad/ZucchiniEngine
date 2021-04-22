/**
 * MemoryManager.hpp
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
#ifndef ZE_MEMORYMANAGER
#define ZE_MEMORYMANAGER

#include "zengine/zemacros.hpp"

#include "zengine/Abstract/Singleton.hpp"

#include <cstdlib>
#include <map>

namespace ze
{
   // TODO Compute allocations per frame
   class ZE_API MemoryManager
   {
   public:
      static MemoryManager& Instance();

      void* allocate(size_t size);
      void* allocate(size_t size, char const* file, unsigned int line);

      void release(void* pointer) noexcept;

   private:
      MemoryManager() noexcept = default;
      ~MemoryManager() noexcept;

      struct BlockInfo
      {
         size_t size;
         char const* file;
         unsigned int line;
      };

      void logMemoryLeaks() noexcept;

      std::map<void*, BlockInfo> m_blocks;
   };
}

#endif // ZE_MEMORYMANAGER
