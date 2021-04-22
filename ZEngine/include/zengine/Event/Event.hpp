/**
 * Event.hpp
 * 12 Dec 2020
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
#ifndef ZE_EVENT
#define ZE_EVENT

#include "zengine/zemacros.hpp"

#include "zengine/Time/Date.hpp"

#include <string>
#include <sstream>
#include <ctime>

namespace ze
{
   class ZE_API Event
   {
   public:
      void cancel() noexcept;
      void setCanceled(bool cancel) noexcept;
      bool isCanceled() const noexcept;

      ze::Date getTimestamp() const noexcept;

      virtual std::string toString() const = 0;

      Event() noexcept;
      virtual ~Event() noexcept = default;

   private:
      bool m_canceled;
      Date const m_timestamp;
   };
}

#include "Event.inl"

#endif // ZE_EVENT
