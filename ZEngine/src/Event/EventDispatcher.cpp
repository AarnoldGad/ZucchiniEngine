#include "zepch.hpp"

#include "zengine/Event/EventDispatcher.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   EventDispatcher::EventDispatcher(Event& event) noexcept
      : m_event(&event) {}
}
