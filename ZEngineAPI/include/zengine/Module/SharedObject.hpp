/**
 * SharedObject.hpp
 * 9 Oct 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_SHAREDOBJECT_HPP
#define ZE_SHAREDOBJECT_HPP

#include "zengine/defines.hpp"

#include <filesystem>

namespace ze
{
   class ZE_API SharedObject
   {
   public:
      bool load(std::filesystem::path const& filename);

      bool isLoaded() const noexcept;
      explicit operator bool() const noexcept;

      void* getSymbol(std::string const& symbol) const;
      void* getHandle() const noexcept;

      explicit SharedObject(std::filesystem::path const& filename = {});
      ~SharedObject();

   protected:
      std::filesystem::path m_path;
      #if defined(_WIN32)
         HMODULE m_handle;
      #else
         void* m_handle;
      #endif
   };
}

#include "SharedObject.inl"

#endif /* ZE_SHAREDOBJECT_HPP */
