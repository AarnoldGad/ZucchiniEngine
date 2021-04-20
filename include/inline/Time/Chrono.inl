inline ze::Time ze::Chrono::elapsed() const noexcept
{
   return m_paused ? m_accumTime : (ze::Time::Now() - m_startTime + m_accumTime);
}
