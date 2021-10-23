#include "zepch.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   StandardAllocator& GetStandardAllocator() noexcept
   {
      static StandardAllocator allocator;

      return allocator;
   }

   void* Allocate(size_t size, SourceLocation const& location)
   {
      return Allocate(size, &GetStandardAllocator(), location);
   }

   void* Allocate(size_t size, Allocator* allocator, SourceLocation const& location)
   {
      return allocator->allocate(size, location);
   }

   void Release(void* pointer, SourceLocation const& location) noexcept
   {
      Release(pointer, &GetStandardAllocator(), location);
   }

   void Release(void* pointer, Allocator* allocator, SourceLocation const& location) noexcept
   {
      allocator->release(pointer, location);
   }
}
