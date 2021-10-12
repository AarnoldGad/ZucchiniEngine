inline ze::Time ze::Chrono::elapsed() const noexcept
{
   return isPaused() ? m_accumTime : (ze::Time::Now() - m_startTime + m_accumTime);
}

inline bool ze::Chrono::isPaused() const noexcept
{
   return m_paused;
}
