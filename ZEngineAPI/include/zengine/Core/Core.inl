inline bool ze::Core::IsInitialised()
{
   return Instance().isInitialised();
}

inline ze::EventBus& ze::Core::UseEventBus() noexcept
{
   return Instance().m_eventBus;
}

inline unsigned int ze::Core::GetTickRate() noexcept
{
   return Instance().m_tickRate;
}

inline ze::Time ze::Core::GetRunTime() noexcept
{
   return IsInitialised() ? Instance().m_runTime.elapsed() : Time::Zero;
}

inline bool ze::Core::isInitialised()
{
   return m_initialised;
}
