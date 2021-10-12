#include "zepch.hpp"

#include "zapi/Module/SharedObject.hpp"

#define dlcheck(x) \
   char const* lastError = dlerror(); \
   if (lastError) \
      LOG_TRACE("Unhandled error : ", lastError); \
   x;

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
         // TODO
      #else
         dlcheck(m_handle = dlopen(filename.string().c_str(), RTLD_NOW));
         if (!m_handle)
         {
            LOG_TRACE("Fail to load shared object ", filename, " : ", dlerror());
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
         // TODO
      #else
         if (!isLoaded()) return nullptr;

         dlcheck(void* symbol = dlsym(m_handle, id.c_str()));

         if (!symbol)
            LOG_TRACE("Fail to load symbol at ", m_path, " : ", dlerror());

         return symbol;
      #endif
   }

   SharedObject::~SharedObject()
   {
      if (isLoaded())
         dlclose(m_handle);
   }
}
