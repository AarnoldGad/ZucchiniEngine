/**
 * OutputStream.hpp
 * 10 Feb 2022
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
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
#ifndef ZE_OUTPUTSTREAM_HPP
#define ZE_OUTPUTSTREAM_HPP

#include "zengine/defines.hpp"

namespace ze
{
   class ZE_API OutputStream
   {
   public:
      virtual OutputStream& put(char ch) = 0;
      virtual OutputStream& write(std::string_view str) = 0;
      virtual OutputStream& flush() = 0;

      virtual ptrdiff_t tellp() = 0;
      virtual OutputStream& seekp(ptrdiff_t pos) = 0;

      virtual OutputStream& operator<<(std::string_view str) = 0;
      virtual explicit operator bool() const = 0;

      virtual ~OutputStream() = default;
   };
}

#endif // ZE_OUTPUTSTREAM_HPP

