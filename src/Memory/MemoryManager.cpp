#include "zepch.hpp"

#include "zengine/Memory/MemoryManager.hpp"

namespace ze
{
   MemoryManager::MemoryManager() noexcept
   : m_blocks{} {}

   void* MemoryManager::allocate(size_t size, char const* file, int line)
   {
      void* allocatedMemory = std::malloc(size);

      BlockInfo info{size, file, line, false};
      m_blocks[allocatedMemory] = info;

      return allocatedMemory;
   }

   void* MemoryManager::allocateArray(size_t size, char const* file, int line)
   {
      void* allocatedMemory = std::malloc(size);

      BlockInfo info{size, file, line, true};
      m_blocks[allocatedMemory] = info;

      return allocatedMemory;
   }

   void MemoryManager::release(void* pointer) noexcept
   {
      auto blockData = m_blocks.find(pointer);
      if (blockData != m_blocks.end())
      {
         m_blocks.erase(pointer);
         // TODO Logging
      }

      std::free(pointer);
   }

   void MemoryManager::releaseArray(void* pointer) noexcept
   {
      if (m_blocks.find(pointer) != m_blocks.end())
      {
         m_blocks.erase(pointer);
         // TODO Logging
      }

      std::free(pointer);
   }

   void MemoryManager::logMemoryLeaks() noexcept
   {
      // TODO Core Logger
   }

   MemoryManager::~MemoryManager() noexcept
   {
      if (!m_blocks.empty())
      {
         // TODO Core Logger
         logMemoryLeaks();
      }
   }
}
