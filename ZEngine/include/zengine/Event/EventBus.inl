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

#include "zengine/Memory/NewOff.hpp"
