#include "zengine/Memory/Memory.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

void* operator new(size_t size, char const* file, unsigned int line)
{
   return ze::MemoryTracker::Allocate(size, file, line);
}

void* operator new[](size_t size, char const* file, unsigned int line)
{
   return ze::MemoryTracker::Allocate(size, file, line);
}

void operator delete(void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryTracker::NextRelease(file, line);
   ze::MemoryTracker::Release(pointer);
}

void operator delete[](void* pointer, char const* file, unsigned int line) noexcept
{
   ze::MemoryTracker::NextRelease(file, line);
   ze::MemoryTracker::Release(pointer);
}

/*
void* operator new(size_t size)
{
   return ze::MemoryTracker::Allocate(size);
}

void* operator delete(void* pointer, [[maybe_unused]] size_t size)
{
   ze::MemoryTracker::Release(pointer);
}

void* operator delete[](void* pointer, [[maybe_unused]] size_t size)
{
   ze::MemoryTracker::Release(pointer);
}

void* operator delete(void* pointer)
{
   ze::MemoryTracker::Release(pointer);
}

void* operator delete[](void* pointer)
{
   ze::MemoryTracker::Release(pointer);
}

 */
