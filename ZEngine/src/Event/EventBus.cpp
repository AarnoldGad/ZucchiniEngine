#include "zepch.hpp"

#include "zengine/Event/EventBus.hpp"

namespace ze
{
   bool EventBus::addSubscriber(Observer<void (Event&)>& subscriber, Priority priority)
   {
      return m_subscribers[priority].insert(&subscriber).second;
   }

   bool EventBus::removeSubscriber(Observer<void (Event&)>& subscriber, Priority priority)
   {
      return m_subscribers[priority].erase(&subscriber);
   }

   void EventBus::dispatchEvents()
   {
      for (auto& event : std::exchange(m_events, {}))
         fireEvent(*event);
   }

   void EventBus::fireEvent(Event& event)
   {
      for (auto const& subscriberList : m_subscribers)
      {
         for (Observer<void (Event&)>* const subscriber : subscriberList.second)
            subscriber->notify(event);

         if (event.isCanceled())
            break;
      }
   }
}
