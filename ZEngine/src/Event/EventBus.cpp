#include "zepch.hpp"

#include "zengine/Event/EventBus.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   void EventBus::dispatchEvents()
   {
      for (auto& event : std::exchange(m_events, {}))
         fireEvent(*event);
   }

   void EventBus::fireEvent(Event& event)
   {
      for (auto& subscriberList : m_subscribers)
      {
         for (Subscriber<Event&>* subscriber : subscriberList.second)
            subscriber->notify(event);

         if (event.isCanceled())
            break;
      }
   }
}
