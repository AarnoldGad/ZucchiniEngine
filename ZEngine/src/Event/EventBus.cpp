#include "zepch.hpp"

#include "zengine/Event/EventBus.hpp"
#include "zengine/Event/Callback.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   void EventBus::subscribe(Callback<Event&>& callback, Priority priority)
   {
      m_callbacks[priority].insert(&callback);
   }

   void EventBus::unsubscribe(Callback<Event&>& callback, Priority priority)
   {
      m_callbacks[priority].erase(&callback);
   }

   void EventBus::dispatchEvents()
   {
      for (auto& event : std::exchange(m_events, {}))
         fireEvent(*event);
   }

   void EventBus::fireEvent(Event& event)
   {
      for (auto& callbackStack : m_callbacks)
      {
         for (auto& callback : callbackStack.second)
            (*callback)(event);

         if (event.isCanceled())
            break;
      }
   }
}
