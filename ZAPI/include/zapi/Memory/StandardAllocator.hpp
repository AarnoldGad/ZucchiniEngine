/**
 * StandardAllocator.hpp
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
#ifndef ZE_STANDARDALLOCATOR_HPP
#define ZE_STANDARDALLOCATOR_HPP

#include "zapi/defines.hpp"

#include "zapi/Memory/Allocator.hpp"

namespace ze
{
   class ZE_API StandardAllocator : public Allocator
   {
   public:
      void* allocate(size_t size, SourceLocation const& location) override;
      size_t release(void* pointer, SourceLocation const& location) noexcept override;

      StandardAllocator();
      ~StandardAllocator();

   private:
      struct Block
      {
         size_t size;
         SourceLocation location;
         unsigned int guardHash; // c.f s_allocationHash / s_releaseHash

         Block* previous;
         Block* next;
      };

      Block* allocateBlock(size_t size, SourceLocation const& location);
      Block* retrieveBlock(void* pointer) noexcept;

      void initBlock(Block* block, size_t size, SourceLocation const& location) const noexcept;
      void deinitBlock(Block* block) const noexcept;

      bool isBlockDeletable(Block* block) const noexcept;

      void pushBlockToList(Block* block) noexcept;
      void popBlockFromList(Block* block) noexcept;

      void traceLeaks();

   private:
      Block m_blockList;
   };
}

#endif /* ZE_STANDARDALLOCATOR_HPP */
