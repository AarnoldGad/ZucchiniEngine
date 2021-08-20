#include "zengine/Memory/New.hpp"

inline void ze::Core::Initialise()
{
   Instance().initialise();
}

inline bool ze::Core::IsInitialised() noexcept
{
   return Instance().m_initialised;
}

inline ze::Application* ze::Core::PlaceApplication(Application& app)
{
   return Instance().placeApplication(app);
}

inline void ze::Core::ConnectEngine(Engine& engine)
{
   Instance().connectEngine(engine);
}

inline void ze::Core::DisconnectEngine(Engine& engine)
{
   Instance().disconnectEngine(engine);
}

inline ze::Application* ze::Core::GetApplication() noexcept
{
   return Instance().m_app;
}

inline ze::Application* ze::Core::RemoveApplication()
{
   return Instance().removeApplication();
}

inline void ze::Core::Terminate()
{
   Instance().terminate();
}

inline bool ze::Core::IsRunning() noexcept
{
   return Instance().m_running;
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

inline ze::Time ze::Core::GetRunTime() noexcept
{
   return IsInitialised() ? Instance().m_runTime.elapsed() : 0;
}

inline unsigned int ze::Core::GetTickRate() noexcept
{
   return Instance().m_tickRate;
}

#include "zengine/Memory/NewOff.hpp"
