/**
 * EventBus.hpp
 * 12 Dec 2020
 * Gaétan "The Aarnold" Jalin
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
#include "zengine/Event/EventSubscriber.hpp"
#include "zengine/Event/Event.hpp"

#include <vector>
#include <set>
#include <map>

namespace ze
{
   class ZE_API EventBus
   {
   public:
      using SubscriberList = std::map<Priority, std::set<Subscriber<Event&>*>, std::greater<Priority> >;

      template<typename EventType, typename... Args>
      void pushEvent(Args&&... args);

      template<typename EventType>
      void pushEvent(EventType&& event);

      template<typename EventType>
      [[nodiscard]]
      EventSubscriber<EventType> subscribe(std::function<void (EventType&)> callback, Priority priotity = Priority::Normal);

      template<typename EventType, typename ReceiverType>
      [[nodiscard]]
      EventSubscriber<EventType> subscribe(void (ReceiverType::*callback)(EventType&), ReceiverType* receiver, Priority priotity = Priority::Normal);

      void dispatchEvents();
      void fireEvent(Event& event);

      EventBus() = default;
      ~EventBus() = default;

   private:
      std::vector<std::shared_ptr<Event> > m_events;
      SubscriberList m_subscribers;
   };
}

#include "EventBus.inl"

#endif // ZE_EVENTBUS_HPP
