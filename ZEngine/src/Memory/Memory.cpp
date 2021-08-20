#include "zengine/Memory/Memory.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

void* operator new(size_t size, SourceLocation const& location)
{
   return ze::MemoryTracker::Allocate(size, location);
}

void* operator new[](size_t size, SourceLocation const& location)
{
   return ze::MemoryTracker::Allocate(size, location);
}

void operator delete(void* pointer, SourceLocation const& location) noexcept
{
   ze::MemoryTracker::NextRelease(location);
   ze::MemoryTracker::Release(pointer);
}

void operator delete[](void* pointer, SourceLocation const& location) noexcept
{
   ze::MemoryTracker::NextRelease(location);
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
