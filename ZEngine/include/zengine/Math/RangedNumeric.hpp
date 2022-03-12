/**
 * RangedNumeric.hpp
 * 1 Apr 2021
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
#ifndef ZE_RANGEDNUMERIC_HPP
#define ZE_RANGEDNUMERIC_HPP

#include "zengine/defines.hpp"

#include <type_traits>
#include <cstdint>

namespace ze
{
   template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue>
   class RangedNumeric
   {
      static_assert(MinValue < MaxValue);
      static_assert(std::is_arithmetic_v<NumericType>);

   public:
      operator NumericType() noexcept;

      RangedNumeric();
      RangedNumeric(NumericType value);
      RangedNumeric<NumericType, MinValue, MaxValue>& operator=(NumericType value);

   private:
      NumericType m_value;
   };

   template<std::intmax_t min, std::intmax_t max>
   using RangedInt = RangedNumeric<int, min, max>;

   template<std::intmax_t min, std::intmax_t max>
   using RangedUnsigned = RangedNumeric<unsigned, min, max>;
}

#include "RangedNumeric.inl"

#endif // ZE_RANGEDNUMERIC_HPP
