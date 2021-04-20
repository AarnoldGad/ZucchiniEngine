#include "zepch.hpp"

#include "zengine/Event/EventBus.hpp"
#include "zengine/Event/Callback.hpp"

namespace ze
{
   void EventBus::subscribe(Callback<Event&>& callback, Priority priority)
   {
      m_callbacks.subscribe(callback, priority);
   }

   void EventBus::unsubscribe(Callback<Event&>& callback, Priority priority)
   {
      m_callbacks.unsubscribe(callback, priority);
   }

   void EventBus::dispatchEvents()
   {
      for (auto& event : std::exchange(m_events, {}))
         fireEvent(std::move(*event));
   }

   void EventBus::fireEvent(Event&& event)
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
