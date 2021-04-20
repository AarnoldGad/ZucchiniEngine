template<typename EventType, typename>
void ze::EventDispatcher::dispatch(std::function<void (EventType&)> handler)
{
   if (isEventReceivable<EventType>(m_event))
      handler(*(dynamic_cast<EventType*>(&m_event)));
}

template<typename EventType, typename Receiver, typename>
void ze::EventDispatcher::dispatch(void (Receiver::*handler)(EventType&), Receiver* receiver)
{
   dispatch<EventType>(std::bind(handler, receiver, std::placeholders::_1));
}

template<typename EventType>
inline bool ze::EventDispatcher::isEventReceivable(Event& event) const
{
   return dynamic_cast<EventType*>(&event); // C++ RTTI, returns nullptr if "event" is not convertible to EventType (i.e is not of polymorphic type EventType)
}
