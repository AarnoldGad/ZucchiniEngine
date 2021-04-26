inline bool ze::Date::isLeapYear() const noexcept
{
   return !(getYear() % 4);
}

inline bool ze::Date::is31DayMonth() const noexcept
{
   return getMonth() == Month::JANUARY ||
          getMonth() == Month::MARCH   ||
          getMonth() == Month::MAY     ||
          getMonth() == Month::JULY    ||
          getMonth() == Month::AUGUST  ||
          getMonth() == Month::OCTOBER ||
          getMonth() == Month::DECEMBER;
}

inline bool ze::Date::is30DayMonth() const noexcept
{
   return getMonth() == Month::APRIL     ||
          getMonth() == Month::JUNE      ||
          getMonth() == Month::SEPTEMBER ||
          getMonth() == Month::NOVEMBER;
}

inline std::tm ze::Date::getTm() const noexcept
{
   return m_date;
}

inline int ze::Date::getSeconds() const noexcept
{
   return m_date.tm_sec;
}

inline int ze::Date::getMinutes() const noexcept
{
   return m_date.tm_min;
}

inline int ze::Date::getHours() const noexcept
{
   return m_date.tm_hour;
}

inline int ze::Date::getDay() const noexcept
{
   return m_date.tm_mday;
}

inline ze::Date::WeekDay ze::Date::getWeekDay() const noexcept
{
   return static_cast<Date::WeekDay>(m_date.tm_wday);
}

inline int ze::Date::getYearDay() const noexcept
{
   return m_date.tm_yday;
}

inline ze::Date::Month ze::Date::getMonth() const noexcept
{
   return static_cast<Date::Month>(m_date.tm_mon);
}

inline int ze::Date::getYear() const noexcept
{
   return m_date.tm_year + 1900;
}

inline bool ze::Date::isDST() const noexcept
{
   return m_date.tm_isdst;
}

inline std::string ze::Date::format(std::string const& formatString) const
{
   std::stringstream formatted;

   formatted << std::put_time(&m_date, formatString.c_str());

   return formatted.str();
}
