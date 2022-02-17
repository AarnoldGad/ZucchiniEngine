/**
 * StackFrame.hpp
 * 18 Aug 2021
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
#ifndef ZE_STACKFRAME_HPP
#define ZE_STACKFRAME_HPP

#include "zengine/defines.hpp"

#include <string>

namespace ze
{
   class ZE_API StackFrame
   {
   public:
      int getNumber() const noexcept;
      std::string getFile() const noexcept;
      std::string getFunction() const noexcept;

      std::string toString() const noexcept;

      StackFrame(int number, std::string const& file, std::string const& function);

   private:
      int m_number;
      std::string m_file;
      std::string m_function;
   };
}

#include "StackFrame.inl"

#endif /* ZE_STACKFRAME_HPP */
