/**
 * Chrono.hpp
 * 20 Dec 2020
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
#ifndef ZE_CHRONO
#define ZE_CHRONO

#include "zengine/zemacros.hpp"

#include "zengine/Time/Time.hpp"

namespace ze
{
   class ZE_API Chrono
   {
   public:
      Time elapsed() const noexcept;
      Time restart() noexcept;

      void pause() noexcept;
      void resume() noexcept;

      Chrono() noexcept;

   private:

      Time m_startTime;
      Time m_accumTime;
      bool m_paused;
   };
}

#include "Chrono.inl"

#endif // ZE_CHRONO
