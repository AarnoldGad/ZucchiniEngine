#ifndef ZE_NEW
#define ZE_NEW

#include <cstdlib>

#if defined(_DEBUG)
   #define zenew new(__FILE__, __LINE__)
#else
   #define zenew new
#endif

#define zedelete delete

void* operator new(size_t size);
void* operator new[](size_t size);

void* operator new(size_t size, char const* file, unsigned int line);
void* operator new[](size_t size, char const* file, unsigned int line);

void operator delete(void* pointer) noexcept;
void operator delete[](void* pointer) noexcept;

void operator delete(void* pointer, [[maybe_unused]] size_t size) noexcept;
void operator delete[](void* pointer, [[maybe_unused]] size_t size) noexcept;

void operator delete(void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] unsigned int line) noexcept;
void operator delete[](void* pointer, [[maybe_unused]] char const* file, [[maybe_unused]] unsigned int line) noexcept;

#endif // ZE_NEW
