/**
 * Random.hpp
 * 4 Apr 2021
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
#ifndef ZE_RANDOM_HPP
#define ZE_RANDOM_HPP

#include "zengine/zemacros.hpp"

#include <random>

#ifdef ZE_PLATFORM_WINDOWS
   #undef min
   #undef max
#endif

namespace ze
{
   class ZE_API Random
   {
   public:
      static void Seed(unsigned int seed);

      static uint64_t GenerateInteger(uint64_t minimum = std::default_random_engine::min(), uint64_t maximum = std::default_random_engine::max());
      static double GenerateFloat(double minimum = 0., double maximum = 1.);

   private:
      Random() = delete;

      static std::default_random_engine s_engine;
   };
}

#endif // ZE_RANDOM_HPP
