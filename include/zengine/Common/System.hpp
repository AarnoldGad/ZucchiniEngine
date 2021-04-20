/**
 * System.hpp
 * 3 Apr 2021
 * Ga�tan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Ga�tan Jalin
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
#ifndef ZE_SYSTEM
#define ZE_SYSTEM

#include "zemacros.hpp"

namespace ze
{
   struct System
   {
      std::string systemName;
      std::string userName;

      struct OS
      {
         std::string name;
         std::string versionString;

         struct Version
         {
            unsigned int major;
            unsigned int minor;
            unsigned int patch;
            unsigned int rev;
         } version;
      } os;
   };

   enum class Architecture
   {
      x86, x64, ARM, ARM64, IA64, UNKNOWN
   };

   enum class Endianess
   {
      LITTLE, BIG
   };

   struct Processor
   {
      std::string model;
      Architecture arch;
      Endianess endian;

      struct Cores
      {
         unsigned int physical;
         unsigned int logical;
      } cores;
   };

   struct Memory
   {
      uint64_t total;
      uint64_t available;
      uint64_t used;
   };

   ZE_API System GetSystemInfo();
   ZE_API Processor GetProcessorInfo();
   ZE_API Memory GetMemoryInfo();

   ZE_API std::string ArchToString(Architecture arch);
}

#endif // ZE_SYSTEM
