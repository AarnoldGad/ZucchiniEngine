/**
 * Time.hpp
 * 18 Dec 2020
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
#ifndef ZE_TIME_HPP
#define ZE_TIME_HPP

#include "zapi/defines.hpp"

#include <chrono>

namespace ze
{
   class ZE_API Time
   {
   public:
      static Time const Zero;
      static Time Now() noexcept;

      double asSecondsFloat() const noexcept;
      int64_t asSeconds() const noexcept;
      int64_t asMilliseconds() const noexcept;
      int64_t asMicroseconds() const noexcept;
      int64_t asNanoseconds() const noexcept;

      template<typename Rep, typename Period>
      Time(std::chrono::duration<Rep, Period> time) noexcept;
      Time(int64_t nanoseconds) noexcept;
      Time() noexcept;

      Time operator-() const noexcept;

      Time& operator+=(Time const& other) noexcept;

      Time& operator-=(Time const& other) noexcept;

      Time& operator*=(double factor) noexcept;

      Time& operator/=(double factor);

      Time& operator%=(Time const& mod) noexcept;

      bool operator==(Time const& other) const noexcept;
      bool operator!=(Time const& other) const noexcept;
      bool operator<=(Time const& other) const noexcept;
      bool operator>=(Time const& other) const noexcept;
      bool operator<(Time const& other) const noexcept;
      bool operator>(Time const& other) const noexcept;

      Time operator+(Time const& other) const noexcept;

      Time operator-(Time const& other) const noexcept;

      Time operator*(double factor) const noexcept;

      Time operator/(double factor) const;

      Time operator%(Time const& other) const noexcept;

   private:
      std::chrono::nanoseconds m_time;
   };

   Time Seconds(double seconds) noexcept;
   Time Milliseconds(int64_t milliseconds) noexcept;
   Time Microseconds(int64_t microseconds) noexcept;
   Time Nanoseconds(int64_t nanoseconds) noexcept;
   void Sleep(Time time); // TODO Program wide equivalent (Currently pause calling thread)
}

#include "Time.inl"

#endif // ZE_TIME_HPP
