/**
 * EventBus.hpp
 * 12 Dec 2020
 * Ga�tan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Ga�tan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_EVENTBUS_HPP
#define ZE_EVENTBUS_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Common/Priority.hpp"
#include "zengine/Event/Event.hpp"
#include "zengine/Event/Subscriber.hpp"

#include <vector>
#include <set>
#include <map>

namespace ze
{
   template<typename... CallbackParameters>
   class Callback;

   class ZE_API EventBus
   {
   public:
      using Callbacks = std::map<Priority, std::set<Callback<Event&>*>, std::greater<Priority> >;

      template<typename EventType, typename... Args>
      void pushEvent(Args&&... args);

      template<typename EventType>
      [[nodiscard]]
      Subscriber<EventType> subscribe(std::function<void (EventType&)> callback, Priority priotity = Priority::Normal);

      template<typename EventType, typename Receiver>
      [[nodiscard]]
      Subscriber<EventType> subscribe(void (Receiver::*callback)(EventType&), Receiver* receiver, Priority priotity = Priority::Normal);

      void subscribe(Callback<Event&>& callback, Priority priority = Priority::Normal);
      void unsubscribe(Callback<Event&>& callback, Priority priority);

      void dispatchEvents();
      void fireEvent(Event& event);

      EventBus() = default;
      ~EventBus() = default;

   private:
      std::vector<std::shared_ptr<Event> > m_events;
      Callbacks m_callbacks;
   };
}

#include "EventBus.inl"

#endif // ZE_EVENTBUS_HPP
