template<typename Rep, typename Period>
ze::Time::Time(std::chrono::duration<Rep, Period> time) noexcept
   : m_time(std::chrono::duration_cast<std::chrono::nanoseconds>(time)) {}

inline double ze::Time::asSecondsFloat() const noexcept
{
   return static_cast<double>(m_time.count()) / 1e+9;
}

inline int64_t ze::Time::asSeconds() const noexcept
{
   return std::chrono::duration_cast<std::chrono::seconds>(m_time).count();
}

inline int64_t ze::Time::asMilliseconds() const noexcept
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(m_time).count();
}

inline int64_t ze::Time::asMicroseconds() const noexcept
{
   return std::chrono::duration_cast<std::chrono::microseconds>(m_time).count();
}

inline int64_t ze::Time::asNanoseconds() const noexcept
{
   return m_time.count();
}
