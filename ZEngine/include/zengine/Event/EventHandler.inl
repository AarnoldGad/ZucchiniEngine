#include "zengine/Memory/New.hpp"

template<typename EventType, typename E>
ze::EventHandler<EventType, E>::EventHandler(CallbackType callback) noexcept
   : m_callback(std::move(callback)) {}

template<typename EventType, typename E>
void ze::EventHandler<EventType, E>::operator()(Event& event)
{
   if (m_callback && isEventReceivable(event))
      m_callback(*(dynamic_cast<EventType*>(&event)));
}

template<typename EventType, typename E>
inline bool ze::EventHandler<EventType, E>::isEventReceivable(Event& event) const noexcept
{
   return dynamic_cast<EventType*>(&event); // C++ RTTI, returns nullptr if "event" is not convertible to EventType (i.e is not of polymorphic type EventType)
}

#include "zengine/Memory/NewOff.hpp"
