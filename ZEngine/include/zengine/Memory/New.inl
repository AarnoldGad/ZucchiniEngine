template<typename PtrType>
PtrType* ze::Allocate(size_t size, SourceLocation const& location)
{
   return (PtrType*) Allocate<PtrType>(size, location, &StandardAllocator::GetStandardAllocator());
}

template<typename PtrType>
PtrType* ze::Allocate(size_t size, SourceLocation const& location, ze::Allocator* allocator)
{
   return (PtrType*) allocator->allocate(size, location);
}
