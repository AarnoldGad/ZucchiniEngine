/**
 * StringUtils.hpp
 * 4 Feb 2021
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
#ifndef ZE_STRINGUTILS_HPP
#define ZE_STRINGUTILS_HPP

#include "zengine/defines.hpp"

namespace ze
{
   #define STRING_LITERAL(type, str) ze::StringLiteral<type>(str, L##str, u##str, U##str)

   template<typename CharType>
   constexpr CharType const* StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr);
}

#include "StringUtils.inl"

#endif // ZE_STRINGUTILS_HPP
