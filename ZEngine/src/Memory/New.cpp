#include "zepch.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   void Release(void* pointer, SourceLocation const& location) noexcept
   {
      Release(pointer, &StandardAllocator::GetStandardAllocator(), location);
   }

   void Release(void* pointer, Allocator* allocator, SourceLocation const& location) noexcept
   {
      allocator->release(pointer, location);
   }
}
