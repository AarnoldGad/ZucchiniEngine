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
#ifndef ZE_SUBSCRIBER
#define ZE_SUBSCRIBER

#include "zemacros.hpp"

#include "zengine/Common/Priority.hpp"
#include "zengine/Event/EventHandler.hpp"
#include "zengine/Event/CallbackList.hpp"
#include "zengine/Common/TypeTraits.hpp"

#include <map>
#include <set>
#include <functional>

namespace ze
{
   template<typename EventType, typename = if_is_event<EventType> >
   class Subscriber
   {
   public:
      using CallbackType = std::function<void(EventType&)>;
      using SubscriberType = Subscriber<EventType>;

      void subscribe();
      void unsubscribe();

      Priority getPriority() const noexcept;
      EventHandler<EventType>& getHandler() noexcept;

      Subscriber(CallbackList& list, CallbackType callback, Priority priority = Priority::NORMAL);
      Subscriber() noexcept;

   private:
      Priority m_priority;
      EventHandler<EventType> m_handler;
      CallbackList* m_list;
   };
}

#include "inline/Event/Subscriber.inl"

#endif // ZE_SUBSCRIBER
