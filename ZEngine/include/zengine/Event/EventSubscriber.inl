#include "zengine/Memory/New.hpp"

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber() noexcept
   : m_handler{}, m_bus(nullptr), m_priority(Priority::Normal) {}

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber(EventSubscriber const& other)
   : m_handler(other.m_handler), m_bus(other.m_bus), m_priority(other.m_priority)
{
   if (m_bus)
      subscribe(*m_bus);
}

template<typename EventType>
ze::EventSubscriber<EventType>::EventSubscriber(HandlerFn handler, EventBus* bus, Priority priority)
   : m_handler(std::move(handler)), m_bus(bus), m_priority(priority)
{
   if (m_bus)
      subscribe(*m_bus);
}

template<typename EventType>
template<typename ReceiverType>
ze::EventSubscriber<EventType>::EventSubscriber(void (ReceiverType::*handler)(EventType&), ReceiverType* receiver, EventBus* bus, Priority priority)
   : m_handler{}, m_bus(bus), m_priority(priority)
{
   if (handler && receiver)
      m_handler = [receiver, handler]
         (EventType& event)
         {
            (receiver->*handler)(event);
         };

   if (m_bus)
      subscribe(*m_bus);
}

template<typename EventType>
ze::EventSubscriber<EventType>& ze::EventSubscriber<EventType>::operator=(EventSubscriber const& other)
{
   m_priority = other.m_priority;
   m_handler = other.m_handler;
   m_bus = other.m_bus;
   
   subscribe();

   return *this;
}

template<typename EventType>
inline bool ze::EventSubscriber<EventType>::subscribe(EventBus& bus, Priority priority)
{
   unsubscribe();
   m_bus = &bus;
   m_priority = priority;
   return m_bus->addSubscriber(*this, priority);
}

template<typename EventType>
inline bool ze::EventSubscriber<EventType>::unsubscribe()
{
   bool unsubscribed = m_bus ? m_bus->removeSubscriber(*this, m_priority) : false;
   m_bus = nullptr;
   return unsubscribed;
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::notify(ze::Event& event)
{
   EventType* castedEvent = dynamic_cast<EventType*>(&event);
   if (m_handler && castedEvent)
      m_handler(*castedEvent);
}

template<typename EventType>
template<typename ReceiverType>
inline void ze::EventSubscriber<EventType>::setHandler(void (ReceiverType::*handler)(EventType&), ReceiverType* receiver)
{
   if (!handler || !receiver) return;

   m_handler = [receiver, handler]
      (EventType& event)
      {
         (receiver->*handler)(event);
      };
}

template<typename EventType>
inline void ze::EventSubscriber<EventType>::setHandler(HandlerFn handler) noexcept
{
   m_handler = handler;
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
