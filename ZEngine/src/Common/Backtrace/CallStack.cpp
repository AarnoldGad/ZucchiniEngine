#include "zepch.hpp"

#include "zengine/Common/Backtrace/CallStack.hpp"

#include <algorithm>
#include <cstdlib>

#if defined(__GNUC__) || defined(__APPLE__) || defined(__MACH__)
   #include <execinfo.h>
   #include <cxxabi.h>
   #include <dlfcn.h>
#endif

#include "zengine/Memory/New.hpp"

namespace ze
{
   CallStack::CallStack(RangedInt<0, 32> size, int skip)
   {
      #if defined(__GNUC__) || defined(__APPLE__) || defined(__MACH__)
         void* trace[32];
         int depth = std::min<int>(backtrace(trace, 32), size);

         for (int i = skip + 2; i < depth; ++i)
         {
            Dl_info dlinfo;
            if(!dladdr(trace[i], &dlinfo))
               break;

            char const* symname = dlinfo.dli_sname;

            int status;
            char* demangled = abi::__cxa_demangle(symname, nullptr, 0, &status);
            if(!status && demangled)
               symname = demangled;

            if (dlinfo.dli_fname && symname)
               m_frames.emplace_back(i - skip - 2, dlinfo.dli_fname, symname);
            else
               break;

            if (demangled)
               free(demangled);
         }
      #endif
   }

   CallStack Stacktrace(RangedInt<0, 32> size, int skip)
   {
      return CallStack(size, skip + 1);
   }
}
