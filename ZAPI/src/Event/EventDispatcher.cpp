#include "zepch.hpp"

#include "zapi/Event/EventDispatcher.hpp"

namespace ze
{
   EventDispatcher::EventDispatcher(Event& event) noexcept
      : m_event(&event) {}
}
