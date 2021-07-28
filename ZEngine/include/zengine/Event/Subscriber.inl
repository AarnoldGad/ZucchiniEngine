#include "zengine/Memory/New.hpp"

template<typename EventType, typename E>
ze::Subscriber<EventType, E>::Subscriber() noexcept
   : m_priority(Priority::Normal), m_list(nullptr) {}

template<typename EventType, typename E>
ze::Subscriber<EventType, E>::Subscriber(SubscriberType const& other)
   : m_priority(other.m_priority), m_handler(other.m_handler), m_list(other.m_list)
{
   subscribe();
}

template<typename EventType, typename E>
ze::Subscriber<EventType, E>::Subscriber(CallbackList& list, CallbackType callback, Priority priority)
   : m_priority(priority), m_handler(std::move(callback)), m_list(&list)
{
   subscribe();
}

template<typename EventType, typename E>
ze::Subscriber<EventType>& ze::Subscriber<EventType, E>::operator=(SubscriberType const& other)
{
   m_priority = other.m_priority;
   m_handler = other.m_handler;
   m_list = other.m_list;

   subscribe();

   return *this;
}

template<typename EventType, typename E>
inline void ze::Subscriber<EventType, E>::subscribe()
{
   if (m_list)
      (*m_list)[m_priority].insert(&m_handler);
}

template<typename EventType, typename E>
inline void ze::Subscriber<EventType, E>::unsubscribe()
{
   if (m_list)
      (*m_list)[m_priority].erase(&m_handler);
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

template<typename EventType, typename E>
ze::Subscriber<EventType, E>::~Subscriber<EventType, E>()
{
   unsubscribe();
}

#include "zengine/Memory/NewOff.hpp"
