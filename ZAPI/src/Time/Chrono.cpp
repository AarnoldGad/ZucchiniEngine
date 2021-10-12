#include "zepch.hpp"

#include "zapi/Time/Chrono.hpp"

namespace ze
{
   Chrono::Chrono() noexcept
      : m_startTime(Time::Now()), m_accumTime(Time::Zero), m_paused(false) {}

   Time Chrono::restart() noexcept
   {
      Time totalTimeElapsed = elapsed();

      m_startTime = Time::Now();
      m_accumTime = Time::Zero;
      m_paused = false;

      return totalTimeElapsed;
   }

   void Chrono::pause() noexcept
   {
      if (isPaused()) return;

      m_accumTime += elapsed(); // Accumulate elapsed time before pausing
      m_paused = true;
   }

   void Chrono::resume() noexcept
   {
      if (!isPaused()) return;

      m_startTime = Time::Now();
      m_paused = false;
   }
}
