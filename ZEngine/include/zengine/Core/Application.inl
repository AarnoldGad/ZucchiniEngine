#include "zengine/Memory/New.hpp"

inline std::string const& ze::Application::getName() const noexcept
{
   return m_name;
}

inline ze::Logger& ze::Application::useAppLogger() noexcept
{
   return m_appLogger;
}

#include "zengine/Memory/NewOff.hpp"