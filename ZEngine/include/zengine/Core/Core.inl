#include "zengine/Memory/New.hpp"

//template<typename StateType, typename... Args>
//void ze::Core::pushState(Args&&... args)
//{
//   m_states.push_back(new StateType(std::forward<Args>(args)...));
//   m_states.back()->onConnection();
//}

inline ze::Application* ze::Core::GetApplication() noexcept
{
   return s_app;
}

inline bool ze::Core::IsRunning() noexcept
{
   return s_running;
}

inline ze::Logger& ze::Core::UseCoreLogger() noexcept
{
   return s_coreLogger;
}

inline ze::Time ze::Core::GetRunTime() noexcept
{
   return IsInitialised() ? s_runTime.elapsed() : 0;
}

inline unsigned int ze::Core::GetTickRate() noexcept
{
   return s_tickRate;
}

#include "zengine/Memory/NewOff.hpp"
