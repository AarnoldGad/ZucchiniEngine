template<typename PtrType>
PtrType* ze::Allocate(size_t size, SourceLocation const& location)
{
   return Allocate<PtrType>(size, &StandardAllocator::GetStandardAllocator(), location);
}

template<typename PtrType>
PtrType* ze::Allocate(size_t size, ze::Allocator* allocator, SourceLocation const& location)
{
   return (PtrType*) allocator->allocate(size, location);
}
