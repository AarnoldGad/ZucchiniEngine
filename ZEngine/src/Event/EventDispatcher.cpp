#include "zepch.hpp"

#include "zengine/Event/EventDispatcher.hpp"

namespace ze
{
   EventDispatcher::EventDispatcher(Event& event) noexcept
      : m_event(event) {}
}
