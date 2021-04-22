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
#ifndef ZE_RANDOM
#define ZE_RANDOM

#include "zengine/zemacros.hpp"

#include <random>

#ifdef ZE_BUILD_WINDOWS
   #undef min
   #undef max
#endif

namespace ze
{
   class ZE_API Random
   {
   public:
      static void Seed(unsigned int seed);

      static uint32_t Generate(uint32_t minimum = std::default_random_engine::min(), uint32_t maximum = std::default_random_engine::max());
      static uint64_t GenerateLong(uint64_t minimum = std::default_random_engine::min(), uint64_t maximum = std::default_random_engine::max());
      static float GenerateFloat(float minimum = 0.f, float maximum = 1.f);
      static double GenerateDouble(double minimum = 0.F, double maximum = 1.F);

   private:
      Random() = delete;

      static std::default_random_engine s_engine;
   };
}

#endif // ZE_RANDOM
