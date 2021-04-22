template<typename StateType, typename... Args>
void ze::Core::pushState(Args&&... args)
{
   m_states.push_back(new StateType(std::forward<Args>(args)...));
}

inline std::string ze::Core::getApplicationName() const noexcept
{
   return m_appName;
}

inline bool ze::Core::isRunning() const noexcept
{
   return m_running;
}

inline ze::Logger& ze::Core::useCoreLogger() noexcept
{
   return m_coreLogger;
}

inline ze::Logger& ze::Core::useClientLogger() noexcept
{
   return m_clientLogger;
}

inline ze::EventBus& ze::Core::useEventBusTo() noexcept
{
   return m_eventBus;
}

inline ze::Time ze::Core::getRunTime() const noexcept
{
   return m_runTime.elapsed();
}

inline unsigned int ze::Core::getTickRate() const noexcept
{
   return m_tickRate;
}
