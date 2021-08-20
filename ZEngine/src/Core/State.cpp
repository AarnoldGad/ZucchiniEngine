#include "zepch.hpp"

#include "zengine/Core/State.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   State::State(std::string const& name) noexcept
      : m_name(name) {}
}
