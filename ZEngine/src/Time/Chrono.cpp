#include "zepch.hpp"

#include "zengine/Time/Chrono.hpp"

#include "zengine/Memory/New.hpp"

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
      m_accumTime += elapsed(); // Accumulate elapsed time so we can reset startTime
      m_paused = true;
   }

   void Chrono::resume() noexcept
   {
      m_startTime = Time::Now();
      m_paused = false;
   }
}
