#include "zepch.hpp"

#include "zengine/Time/Date.hpp"

namespace ze
{
   Date Date::CurrentDate()
   {
      std::time_t t = time(nullptr);
      std::tm tm;
      #ifdef __GNUC__
         localtime_r(&t, &tm);
      #else
         localtime_s(&tm, &t);
      #endif
      return tm;
   }

   Date::Date(int year, Month month, RangedNumeric<int, 1, 31> day,
              RangedNumeric<int, 0, 23> hour, RangedNumeric<int, 0, 59> minute, RangedNumeric<int, 0, 60> second)
   {
      setYear(year).setMonth(month).setDay(day).setHour(hour).setMinute(minute).setSecond(second);
   }

   Date::Date(int year, RangedNumeric<int, 0, 11> month, RangedNumeric<int, 1, 31> day,
              RangedNumeric<int, 0, 23> hour, RangedNumeric<int, 0, 59> minute, RangedNumeric<int, 0, 60> second)
   {
      setYear(year).setMonth(month).setDay(day).setHour(hour).setMinute(minute).setSecond(second);
   }

   Date::Date(std::tm time)
      : m_date(time)
   {
      adjustDate();
   }

   Date::Date() noexcept
   {
      setYear(1970).setMonth(Month::JANUARY).setDay(1).setHour(0).setMinute(0).setSecond(0);
   }

   Date& Date::setSecond(RangedNumeric<int, 0, 60> second)
   {
      m_date.tm_sec = second;
      return *this;
   }

   Date& Date::setMinute(RangedNumeric<int, 0, 59> minute)
   {
      m_date.tm_min = minute;
      return *this;
   }

   Date& Date::setHour(RangedNumeric<int, 0, 23> hour)
   {
      m_date.tm_hour = hour;
      return *this;
   }

   Date& Date::setDay(RangedNumeric<int, 1, 31> day)
   {
      if (day >= 29)
      {
         if (day == 31)
         {
            if (is31DayMonth())
               m_date.tm_mday = 31;
            else if (is30DayMonth())
               m_date.tm_mday = 30;
            else if (isLeapYear())
               m_date.tm_mday = 29;
            else
               m_date.tm_mday = 28;
         }

         if (day == 30)
         {
            if (is30DayMonth())
               m_date.tm_mday = 30;
            else if (getMonth() == Month::FEBRUARY && isLeapYear())
               m_date.tm_mday = 29;
            else
               m_date.tm_mday = 28;
         }

         if (day == 29 && isLeapYear())
            m_date.tm_mday = 29;
         else
            m_date.tm_mday = 28;
      }
      else
         m_date.tm_mday = day; // days from 1-28

      return *this;
   }

   Date& Date::setMonth(RangedNumeric<int, 0, 11> month)
   {
      m_date.tm_mon = month;
      return *this;
   }

   Date& Date::setMonth(Month month)
   {
      m_date.tm_mon = static_cast<int>(month);
      return *this;
   }

   Date& Date::setYear(int year)
   {
      m_date.tm_year = year - 1900;
      return *this;
   }

   Date& Date::addSeconds(int seconds)
   {
      m_date.tm_sec += seconds;
      adjustDate();
      return *this;
   }

   Date& Date::addMinutes(int minutes)
   {
      m_date.tm_min += minutes;
      adjustDate();
      return *this;
   }

   Date& Date::addHours(int hours)
   {
      m_date.tm_hour += hours;
      adjustDate();
      return *this;
   }

   Date& Date::addDays(int days)
   {
      m_date.tm_mday += days;
      adjustDate();
      return *this;
   }

   Date& Date::addMonths(int months)
   {
      m_date.tm_mon += months;
      adjustDate();
      return *this;
   }

   Date& Date::addYears(int years)
   {
      m_date.tm_year += years;
      adjustDate();
      return *this;
   }

   void Date::adjustDate()
   {
      std::mktime(&m_date);
   }

   Date::Month operator++(Date::Month& month, int) noexcept
   {
      Date::Month previousMonth = month;
      char incrementedMonth = static_cast<char>(month);

      incrementedMonth++;
      if (incrementedMonth >= static_cast<char>(Date::Month::NUMBER_OF_MONTH))
         incrementedMonth = 0;

      month = static_cast<Date::Month>(incrementedMonth);
      return previousMonth;
   }

   Date::Month operator--(Date::Month& month, int) noexcept
   {
      Date::Month previousMonth = month;
      char decrementedMonth = static_cast<char>(month);

      decrementedMonth--;
      if (decrementedMonth < 0)
         decrementedMonth = static_cast<char>(Date::Month::DECEMBER);

      month = static_cast<Date::Month>(decrementedMonth);
      return previousMonth;
   }

   Date::Month& operator++(Date::Month& month) noexcept
   {
      month++;
      return month;
   }

   Date::Month& operator--(Date::Month& month) noexcept
   {
      month--;
      return month;
   }

   Date::WeekDay operator++(Date::WeekDay& day, int) noexcept
   {
      Date::WeekDay previousDay = day;
      char incrementedDay = static_cast<char>(day);

      incrementedDay++;
      if (incrementedDay >= static_cast<char>(Date::WeekDay::NUMBER_OF_DAY))
         incrementedDay = 0;

      day = static_cast<Date::WeekDay>(incrementedDay);
      return previousDay;
   }

   Date::WeekDay operator--(Date::WeekDay& day, int) noexcept
   {
      Date::WeekDay previousDay = day;
      char decrementedDay = static_cast<char>(day);

      decrementedDay--;
      if (decrementedDay < 0)
         decrementedDay = static_cast<char>(Date::WeekDay::SATURDAY);

      day = static_cast<Date::WeekDay>(decrementedDay);
      return previousDay;
   }

   Date::WeekDay& operator++(Date::WeekDay& day) noexcept
   {
      day++;
      return day;
   }

   Date::WeekDay& operator--(Date::WeekDay& day) noexcept
   {
      day--;
      return day;
   }
}
