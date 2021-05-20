#include "zengine/Memory/New.hpp"

template<typename EventType, typename E>
ze::EventHandler<EventType, E>::EventHandler(CallbackType callback) noexcept
   : m_callback(std::move(callback)) {}

template<typename EventType, typename E>
void ze::EventHandler<EventType, E>::operator()(Event& event)
{
   EventType* castEvent = dynamic_cast<EventType*>(&event);
   if (m_callback && castEvent)
      m_callback(*castEvent);
}

#include "zengine/Memory/NewOff.hpp"
