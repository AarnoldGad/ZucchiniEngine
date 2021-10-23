inline bool ze::Core::IsInitialised()
{
   return Instance().isInitialised();
}

inline ze::EventBus& ze::Core::UseEventBus() noexcept
{
   return Instance().m_eventBus;
}

inline ze::Logger& ze::Core::UseCoreLogger() noexcept
{
   return Instance().m_coreLogger;
}

inline ze::Logger& ze::Core::UseAppLogger() noexcept
{
   return Instance().m_appLogger;
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
