/**
 * Subscriber.hpp
 * 12 Mar 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
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
#ifndef ZE_EVENTSUBSCRIBER_HPP
#define ZE_EVENTSUBSCRIBER_HPP

#include "zengine/defines.hpp"

#include "zengine/Common/Priority.hpp"
#include "zengine/Common/Observer.hpp"
#include "zengine/Event/EventBus.hpp"

#include <functional>

namespace ze
{
   template<typename EventType>
   class EventSubscriber : public Observer<void (Event&)>
   {
   public:
      using HandlerFn = std::function<void (EventType&)>;

      bool subscribe(EventBus& bus, Priority priority = Priority::Normal);
      bool unsubscribe();

      void notify(Event& event) override;

      template<typename ReceiverType>
      void setHandler(void (ReceiverType::*handler)(EventType&), ReceiverType* receiver);
      void setHandler(HandlerFn handler) noexcept;
      HandlerFn getHandler() const noexcept;
      Priority getPriority() const noexcept;

      template<typename ReceiverType>
      EventSubscriber(void (ReceiverType::*handler)(EventType&), ReceiverType* receiver, EventBus* bus = nullptr, Priority priority = Priority::Normal);
      explicit EventSubscriber(HandlerFn handler, EventBus* bus = nullptr, Priority priority = Priority::Normal);
      EventSubscriber(EventSubscriber const& other);
      EventSubscriber() noexcept;
      ~EventSubscriber();

      EventSubscriber& operator=(EventSubscriber const& other);

   private:
      HandlerFn m_handler;
      EventBus* m_bus;
      Priority m_priority;
   };
}

#include "EventSubscriber.inl"

#endif // ZE_EVENTSUBSCRIBER_HPP
