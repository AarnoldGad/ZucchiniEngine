template<typename EventType, typename... Args>
void ze::EventBus::pushEvent(Args&&... args)
{
   m_events.push_back(std::make_unique<EventType>(std::forward<Args>(args)...));
}

template<typename EventType>
[[nodiscard]]
inline ze::Subscriber<EventType> ze::EventBus::subscribe(std::function<void (EventType&)> callback, Priority priority)
{
   return Subscriber<EventType>(m_callbacks, callback, priority);
}

template<typename EventType, typename Receiver>
[[nodiscard]]
inline ze::Subscriber<EventType> ze::EventBus::subscribe(void (Receiver::*callback)(EventType&), Receiver* receiver, Priority priority)
{
   return subscribe<EventType>(std::bind(callback, receiver, std::placeholders::_1), priority);
}
