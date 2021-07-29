#include "zengine/Memory/New.hpp"

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber() noexcept
   : m_list(nullptr), m_handler{}, m_priority(Priority::Normal) {}

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber(EventSubscriber const& other)
   : m_list(other.m_list), m_handler(other.m_handler), m_priority(other.m_priority)
{
   subscribe();
}

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber(HandlerFn handler, Priority priority)
   : EventSubscriber(nullptr, handler, priority) {}

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber(SubscriberList* list, HandlerFn handler, Priority priority)
   : m_list(list), m_handler(std::move(handler)), m_priority(priority)
{
   subscribe();
}

template<typename EventType>
ze::EventSubscriber<EventType>& ze::EventSubscriber<EventType>::operator=(EventSubscriber const& other)
{
   m_priority = other.m_priority;
   m_handler = other.m_handler;
   m_list = other.m_list;
   
   subscribe();

   return *this;
}

template<typename EventType>
inline bool ze::EventSubscriber<EventType>::subscribe()
{
   return m_list ? (*m_list)[getPriority()].insert(this).second : false;
}

template<typename EventType>
inline bool ze::EventSubscriber<EventType>::unsubscribe()
{
   return m_list ? (*m_list)[getPriority()].erase(this) : false;
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::notify(ze::Event& event)
{
   EventType* castedEvent = dynamic_cast<EventType*>(&event);
   if (m_handler && castedEvent)
      m_handler(*castedEvent);
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::setHandler(HandlerFn handler) noexcept
{
   m_handler = handler;
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::setList(SubscriberList* list)
{
   unsubscribe();
   m_list = list;
   subscribe();
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::setPriority(Priority priority)
{
   unsubscribe();
   m_priority = priority;
   subscribe();
}

template<typename EventType>
inline std::function<void (EventType&)> ze::EventSubscriber<EventType>::getHandler() const noexcept
{
   return m_handler;
}

template<typename EventType>
inline ze::Priority ze::EventSubscriber<EventType>::getPriority() const noexcept
{
   return m_priority;
}

template<typename EventType>
ze::EventSubscriber<EventType>::~EventSubscriber<EventType>()
{
   unsubscribe();
}

#include "zengine/Memory/NewOff.hpp"
