#include "zepch.hpp"

#include "zengine/Module/SharedObject.hpp"

#include "zengine/Common/Console.hpp"

#if !defined(_WIN32)
   #define dlcheck(x) \
      char const* lastError = dlerror(); \
      if (lastError) \
         Console::Trace("Unhandled error : {}", lastError); \
      x;
#endif

namespace ze
{
   SharedObject::SharedObject(std::filesystem::path const& filename)
      : m_handle(nullptr)
   {
      load(filename);
   }

   bool SharedObject::load(std::filesystem::path const& filename)
   {
      #if defined(_WIN32)
         m_handle = LoadLibrary(filename.string().c_str());
         if (!m_handle)
         {
            DWORD errorCode = GetLastError();
            LPSTR errorMessage = nullptr;
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorMessage, 0, NULL);

            Console::Trace("Fail to load shared object {} : {}", filename, errorMessage);
            m_path.clear();
            LocalFree(errorMessage);
            return false;
         }

         m_path = filename;
         return true;
      #else
         dlcheck(m_handle = dlopen(filename.string().c_str(), RTLD_NOW));
         if (!m_handle)
         {
            Console::Trace("Fail to load shared object {} : {}", filename, dlerror());
            m_path.clear();
            return false;
         }

         m_path = filename;
         return true;
      #endif
   }

   void* SharedObject::getSymbol(std::string const& id) const
   {
      #if defined(_WIN32)
         if (!isLoaded()) return nullptr;

         void* symbol = GetProcAddress(m_handle, id.c_str());

         if (!symbol)
         {
            DWORD errorCode = GetLastError();
            LPSTR errorMessage = nullptr;
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorMessage, 0, NULL);

            Console::Trace("Fail to load symbol \"{}\" at {} : {}", id, m_path, errorMessage);
            LocalFree(errorMessage);
         }

         return symbol;
      #else
         if (!isLoaded()) return nullptr;

         dlcheck(void* symbol = dlsym(m_handle, id.c_str()));

         if (!symbol)
            Console::Trace("Fail to load symbol \"{}\" at {} : {}", id, m_path, dlerror());

         return symbol;
      #endif
   }

   SharedObject::~SharedObject()
   {
      if (isLoaded())
         #if defined(_WIN32)
            FreeLibrary(m_handle);
         #else
            dlclose(m_handle);
         #endif
   }
}
