#include "zepch.hpp"

#include "zengine/Time/Time.hpp"

namespace ze
{
   Time const Time::Zero = Time(std::chrono::nanoseconds::zero());

   Time::Time() noexcept
      : m_time(std::chrono::nanoseconds::zero()) {}

   Time::Time(int64_t nanoseconds) noexcept
      : m_time(nanoseconds) {}

   Time Time::Now() noexcept
   {
      return Time(std::chrono::steady_clock::now().time_since_epoch());
   }

   Time Seconds(double seconds) noexcept
   {
      return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(seconds)));
   }

   Time Milliseconds(int64_t milliseconds) noexcept
   {
      return Time(std::chrono::milliseconds(milliseconds));
   }

   Time Microseconds(int64_t microseconds) noexcept
   {
      return Time(std::chrono::microseconds(microseconds));
   }

   Time Nanoseconds(int64_t nanoseconds) noexcept
   {
      return Time(nanoseconds);
   }

   void Sleep(ze::Time time)
   {
      // TODO More reliable sleep function
      std::this_thread::sleep_for(std::chrono::nanoseconds(time.asNanoseconds()));
   }


   Time Time::operator-() const noexcept
   {
      return -asNanoseconds();
   }

   Time& Time::operator+=(Time const& other) noexcept
   {
      m_time += std::chrono::nanoseconds(other.asNanoseconds());
      return *this;
   }

   Time& Time::operator-=(Time const& other) noexcept
   {
      m_time -= std::chrono::nanoseconds(other.asNanoseconds());
      return *this;
   }

   Time& Time::operator*=(double factor) noexcept
   {
      m_time = std::chrono::nanoseconds(static_cast<int64_t>(static_cast<double>(asNanoseconds()) * factor));
      return *this;
   }

   Time& Time::operator/=(double factor)
   {
      ZE_ASSERT(factor != 0.0, "Division by zero !");
      m_time = std::chrono::nanoseconds(static_cast<int64_t>(static_cast<double>(asNanoseconds()) / factor));
      return *this;
   }

   Time& Time::operator%=(Time const& other) noexcept
   {
      m_time %= other.m_time;
      return *this;
   }

   bool Time::operator==(Time const& other) const noexcept
   {
      return m_time == other.m_time;
   }

   bool Time::operator!=(Time const& other) const noexcept
   {
      return m_time != other.m_time;
   }

   bool Time::operator<=(Time const& other) const noexcept
   {
      return m_time <= other.m_time;
   }

   bool Time::operator>=(Time const& other) const noexcept
   {
      return m_time >= other.m_time;
   }

   bool Time::operator<(Time const& other) const noexcept
   {
      return m_time < other.m_time;
   }

   bool Time::operator>(Time const& other) const noexcept
   {
      return m_time > other.m_time;
   }

   Time Time::operator+(Time const& other) const noexcept
   {
      return m_time + other.m_time;
   }

   Time Time::operator-(Time const& other) const noexcept
   {
      return m_time - other.m_time;
   }

   Time Time::operator*(double factor) const noexcept
   {
      return static_cast<int64_t>(static_cast<double>(asNanoseconds()) * factor);
   }

   Time Time::operator/(double factor) const
   {
      ZE_ASSERT(factor != 0.0, "Division by Zero !");
      return static_cast<int64_t>(static_cast<double>(asNanoseconds()) / factor);
   }

   Time Time::operator%(Time const& other) const noexcept
   {
      return m_time % other.m_time;
   }
}
