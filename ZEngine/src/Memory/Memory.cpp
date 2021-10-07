#include "zepch.hpp"

#include "zengine/Memory/Memory.hpp"

#include "zengine/Memory/MemoryTracker.hpp"

#include <new>

#if !defined(__clang__)
   void* operator new(size_t size)
   {
      return ze::MemoryTracker::Allocate(size);
   }

   void operator delete(void* pointer) noexcept
   {
      ze::MemoryTracker::Release(pointer);
   }

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
#endif
