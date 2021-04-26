#include "zepch.hpp"

#include "zengine/Memory/MemoryManager.hpp"
#include "zengine/Memory/Memory.hpp"

void* operator new(size_t size) // Sufficient to handle all standard allocations (No new[] needed)
{
   return ze::MemoryManager::Allocate(size);
}

void* operator new(size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Allocate(size, file, line);
}

void* operator new[](size_t size, char const* file, unsigned int line)
{
   return ze::MemoryManager::Allocate(size, file, line);
}

void operator delete(void* pointer) noexcept
{
   ze::MemoryManager::Release(pointer);
}

void operator delete[](void* pointer) noexcept
{
   ze::MemoryManager::Release(pointer);
}

void operator delete(void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Release(pointer);
}

void operator delete[](void* pointer, [[maybe_unused]] size_t size) noexcept
{
   ze::MemoryManager::Release(pointer);
}

void operator delete(void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryManager::NextRelease(file, line);
   ze::MemoryManager::Release(pointer);
}

void operator delete[](void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryManager::NextRelease(file, line);
   ze::MemoryManager::Release(pointer);
}
