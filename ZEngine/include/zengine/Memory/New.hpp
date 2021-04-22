#ifndef ZE_NEW
#define ZE_NEW

#include <zengine/Memory/MemoryManager.hpp>
#include <cstdlib>

void* operator new(size_t size, char const* file, int line)
{
   return ze::MemoryManager::Instance().allocate(size, file, line);
}

void* operator new[](size_t size, char const* file, int line)
{
   return ze::MemoryManager::Instance().allocateArray(size, file, line);
}

void operator delete(void* pointer) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer) noexcept
{
   ze::MemoryManager::Instance().releaseArray(pointer);
}

void operator delete(void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Instance().releaseArray(pointer);
}

void operator delete(void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] int line) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] int line) noexcept
{
   ze::MemoryManager::Instance().releaseArray(pointer);
}

#endif // ZE_NEW

#ifndef new
   #define new new(__FILE__, __LINE__)
#endif
