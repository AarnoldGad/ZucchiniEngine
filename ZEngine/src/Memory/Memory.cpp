#include "zepch.hpp"

#include "zengine/Memory/MemoryManager.hpp"
#include "zengine/Memory/Memory.hpp"

void* operator new(size_t size)
{
   return ze::MemoryManager::Instance().allocate(size);
}

void* operator new[](size_t size)
{
   return ze::MemoryManager::Instance().allocate(size);
}

void* operator new(size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Instance().allocate(size, file, line);
}

void* operator new[](size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Instance().allocate(size, file, line);
}

void operator delete(void* pointer) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete(void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete(void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] unsigned int line) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}

void operator delete[](void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] unsigned int line) noexcept
{
   ze::MemoryManager::Instance().release(pointer);
}
