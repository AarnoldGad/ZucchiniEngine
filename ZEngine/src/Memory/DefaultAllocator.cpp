#include "zepch.hpp"

#include "zengine/Memory/DefaultAllocator.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   namespace
   {
      // Identification hashes
      constexpr unsigned int s_allocationHash = 0xA110CA73; // Identify a block allocated with this allocator
      constexpr unsigned int s_releaseHash = 0xF533D; // Identify a block freed
   }

   DefaultAllocator::DefaultAllocator()
      : m_blockList{ 0, {nullptr, 0, nullptr}, 0, &m_blockList, &m_blockList } {}

   void* DefaultAllocator::allocate(size_t size, SourceLocation const& location)
   {
      Block* allocatedBlock = allocateBlock(size, location);
      initBlock(allocatedBlock, size, location);
      pushBlockToList(allocatedBlock);
      return reinterpret_cast<uint8_t*>(allocatedBlock) + sizeof(Block);
   }

   size_t DefaultAllocator::release(void* pointer, [[maybe_unused]] size_t size, SourceLocation const& location) noexcept
   {
      if (pointer == nullptr) return 0;

      Block* allocatedBlock = retrieveBlock(pointer);
      size_t blockSize = allocatedBlock->size;

      if (!isBlockDeletable(allocatedBlock))
      {
         MemoryTracker::MemoryLog(allocatedBlock->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion");
         if (location.file)
            MemoryTracker::MemoryLog("   at %s::%s:%u",
                                                             location.file, location.function, location.line);
         else
            MemoryTracker::MemoryLog("   at undefined position");
         return 0;
      }

      deinitBlock(allocatedBlock);
      popBlockFromList(allocatedBlock);

      std::free(allocatedBlock);

      return blockSize;
   }

   DefaultAllocator::Block* DefaultAllocator::allocateBlock(size_t size, SourceLocation const& location)
   {
      Block* block = static_cast<Block*>(std::malloc(size + sizeof(Block)));

      if (block == nullptr)
      {
         MemoryTracker::MemoryLog("Unable to allocate %u bytes", size);

         if (location.file)
            MemoryTracker::MemoryLog("   at %s::%s:%u",
                                                             location.file, location.function, location.line);
         else
            MemoryTracker::MemoryLog("   at undefined position");

         throw std::bad_alloc{};
      }

      return block;
   }

   inline DefaultAllocator::Block* DefaultAllocator::retrieveBlock(void* pointer) noexcept
   {
      return reinterpret_cast<Block*>(static_cast<uint8_t*>(pointer) - sizeof(Block));
   }

   void DefaultAllocator::initBlock(Block* block, size_t size, SourceLocation const& location) const noexcept
   {
      block->size = size;
      block->location = location;
      block->guardHash = s_allocationHash;
   }

   inline bool DefaultAllocator::isBlockDeletable(Block* block) const noexcept
   {
      if (block->guardHash != s_allocationHash)
         return false;

      return true;
   }

   inline void DefaultAllocator::deinitBlock(Block* block) const noexcept
   {
      block->guardHash = s_releaseHash;
   }

   void DefaultAllocator::pushBlockToList(Block* block) noexcept
   {
      block->previous = m_blockList.previous;
      block->next = &m_blockList;

      m_blockList.previous->next = block;
      m_blockList.previous = block;
   }

   void DefaultAllocator::popBlockFromList(Block* block) noexcept
   {
      block->previous->next = block->next;
      block->next->previous = block->previous;
   }

   void DefaultAllocator::traceLeaks()
   {
      Block* leakedPointer = m_blockList.next;
      while (leakedPointer != &m_blockList)
      {
         if (leakedPointer->location.file)
         {
            MemoryTracker::MemoryLog("--- %u bytes", leakedPointer->size);
            MemoryTracker::MemoryLog("---    at 0x%x %s::%s:%u",
                                     reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)),
                                     leakedPointer->location.file, leakedPointer->location.function, leakedPointer->location.line);
         }

         void* handledLeak = leakedPointer;
         leakedPointer = leakedPointer->next;

         std::free(handledLeak);
      }
   }

   DefaultAllocator::~DefaultAllocator()
   {
      if (MemoryTracker::GetTotalAllocations() != 0) // TODO
      {
         MemoryTracker::MemoryLog("--- Memory Allocator registered %u leaks ! ------", MemoryTracker::GetTotalAllocations());
         MemoryTracker::MemoryLog("--- %u bytes leaked", MemoryTracker::GetTotalMemoryAllocated());

         traceLeaks();
      }
   }
}
