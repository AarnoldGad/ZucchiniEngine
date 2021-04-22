#include "zepch.hpp"

#include "zengine/Memory/MemoryManager.hpp"

namespace ze
{
   MemoryManager& MemoryManager::Instance()
   {
      static MemoryManager instance;
      return instance;
   }

   void* MemoryManager::allocate(size_t size)
   {
      return std::malloc(size);
   }

   void* MemoryManager::allocate(size_t size, char const* file, unsigned int line)
   {
      void* allocated = std::malloc(size);

      // TODO Log

      m_blocks[allocated] = {size, file, line};

      return allocated;
   }

   void MemoryManager::release(void* pointer) noexcept
   {
      auto it = m_blocks.find(pointer);
      if (it != m_blocks.end())
      {
         // TODO Log

         m_blocks.erase(pointer);
      }

      std::free(pointer);
   }

   void MemoryManager::logMemoryLeaks() noexcept
   {
      LOG_TRACE("------ ", m_blocks.size(), " Unhandled memory leaks registered ! ------");
      std::for_each(m_blocks.begin(), m_blocks.end(), [](std::pair<void*, BlockInfo> leak)
      {
         LOG_TRACE("   address : ", std::hex, leak.first, std::dec, " (size ", leak.second.size, "B)");
         LOG_TRACE("   at ", leak.second.file, ":", leak.second.line, "\n");
      });
   }

   MemoryManager::~MemoryManager() noexcept
   {
      if (!m_blocks.empty())
         logMemoryLeaks();
   }
}
