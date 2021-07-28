#include "zengine/Core/Application.hpp"

#include "zengine/Core/Core.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   Application::Application(std::string const& name)
      : m_name(name), m_appWriter(getName() + ".log"), m_appLogger(getName(), &m_appWriter) {}
}
