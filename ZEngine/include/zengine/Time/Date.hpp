/**
 * Date.hpp
 * 29 Jan 2021
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
#ifndef ZE_DATE_HPP
#define ZE_DATE_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Math/RangedNumeric.hpp"

#include <sstream>
#include <ctime>

namespace ze
{
   class ZE_API Date
   {
   public:
      enum class Month : char
      {
         JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE,
         JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,
         NUMBER_OF_MONTH
      };

      enum class WeekDay : char
      {
         SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, NUMBER_OF_DAY
      };

      static Date CurrentDate();

      bool isLeapYear() const noexcept;
      bool is31DayMonth() const noexcept;
      bool is30DayMonth() const noexcept;

      Date& addSeconds(int seconds);
      Date& addMinutes(int minutes);
      Date& addHours(int hours);
      Date& addDays(int days);
      Date& addMonths(int months);
      Date& addYears(int years);

      Date& setSecond(RangedNumeric<int, 0, 60> second);
      Date& setMinute(RangedNumeric<int, 0, 59> minute);
      Date& setHour(RangedNumeric<int, 0, 23> hour);
      Date& setDay(RangedNumeric<int, 1, 31> day);
      Date& setMonth(RangedNumeric<int, 0, 11> month);
      Date& setMonth(Month month);
      Date& setYear(int year);

      int getSeconds() const noexcept;
      int getMinutes() const noexcept;
      int getHours() const noexcept;
      int getDay() const noexcept;
      WeekDay getWeekDay() const noexcept;
      int getYearDay() const noexcept;
      Month getMonth() const noexcept;
      int getYear() const noexcept;
      bool isDST() const noexcept;

      std::tm getTm() const noexcept;

      std::string format(std::string const& formatString) const;

      explicit Date(int year, Month month, RangedNumeric<int, 1, 31> day,
           RangedNumeric<int, 0, 23> hour = 0, RangedNumeric<int, 0, 59> minute = 0, RangedNumeric<int, 0, 60> second = 0);
      explicit Date(int year, RangedNumeric<int, 0, 11> month, RangedNumeric<int, 1, 31> day,
           RangedNumeric<int, 0, 23> hour = 0, RangedNumeric<int, 0, 59> minute = 0, RangedNumeric<int, 0, 60> second = 0);
      Date(std::tm time);
      Date() noexcept;

   private:
      void adjustDate();

      std::tm m_date;
   };

   Date::Month operator++(Date::Month& month, int) noexcept;
   Date::Month operator--(Date::Month& month, int) noexcept;

   Date::Month& operator++(Date::Month& month) noexcept;
   Date::Month& operator--(Date::Month& month) noexcept;

   Date::WeekDay operator++(Date::WeekDay& day, int) noexcept;
   Date::WeekDay operator--(Date::WeekDay& day, int) noexcept;

   Date::WeekDay& operator++(Date::WeekDay& day) noexcept;
   Date::WeekDay& operator--(Date::WeekDay& day) noexcept;
}

#include "Date.inl"

#endif // ZE_DATE_HPP
