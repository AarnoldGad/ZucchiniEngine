template<typename EventType>
void ze::EventDispatcher::dispatch(std::function<void (EventType&)> handler)
{
   EventType* event = dynamic_cast<EventType*>(m_event);
   if (event)
      handler(*event);
}

template<typename EventType, typename Receiver>
void ze::EventDispatcher::dispatch(void (Receiver::*handler)(EventType&), Receiver* receiver)
{
   dispatch<EventType>(std::bind(handler, receiver, std::placeholders::_1));
}
