template<typename EventType, typename E>
ze::Subscriber<EventType, E>::Subscriber() noexcept
   : m_priority(Priority::NORMAL), m_list(nullptr) {}

template<typename EventType, typename E>
ze::Subscriber<EventType, E>::Subscriber(CallbackList& list, CallbackType callback, Priority priority)
   : m_priority(priority), m_handler(std::move(callback)), m_list(&list)
{
   subscribe();
}

template<typename EventType, typename E>
inline void ze::Subscriber<EventType, E>::subscribe()
{
   if (m_list)
      m_list->subscribe(m_handler, m_priority);
}

template<typename EventType, typename E>
inline void ze::Subscriber<EventType, E>::unsubscribe()
{
   if (m_list)
      m_list->unsubscribe(m_handler, m_priority);
}

template<typename EventType, typename E>
inline ze::Priority ze::Subscriber<EventType, E>::getPriority() const noexcept
{
   return m_priority;
}

template<typename EventType, typename E>
inline ze::EventHandler<EventType>& ze::Subscriber<EventType, E>::getHandler() noexcept
{
   return m_handler;
}
