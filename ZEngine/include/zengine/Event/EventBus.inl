#include "zengine/Memory/New.hpp"

template<typename EventType, typename... Args>
inline void ze::EventBus::pushEvent(Args&&... args)
{
   m_events.push_back(std::make_shared<EventType>(std::forward<Args>(args)...));
}

template<typename EventType>
inline void ze::EventBus::pushEvent(EventType&& event)
{
   m_events.push_back(std::make_shared<EventType>(std::move(event)));
}

template<typename EventType>
[[nodiscard]]
inline ze::EventSubscriber<EventType> ze::EventBus::subscribe(std::function<void (EventType&)> callback, Priority priority)
{
   return EventSubscriber<EventType>(&m_subscribers, callback, priority);
}

template<typename EventType, typename ReceiverType>
[[nodiscard]]
inline ze::EventSubscriber<EventType> ze::EventBus::subscribe(void (ReceiverType::*callback)(EventType&), ReceiverType* receiver, Priority priority)
{
   return EventSubscriber<EventType>(&m_subscribers, std::bind(callback, receiver, std::placeholders::_1), priority);
}

#include "zengine/Memory/NewOff.hpp"
