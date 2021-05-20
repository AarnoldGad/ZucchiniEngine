/**
 * EventHandler.hpp
 * 12 Dec 2020
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
#ifndef ZE_EVENTHANDLER_HPP
#define ZE_EVENTHANDLER_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Event/Event.hpp"
#include "zengine/Event/Callback.hpp"
#include "zengine/Common/TypeTraits.hpp"

#include <functional>
#include <type_traits>

namespace ze
{
   template<typename EventType, typename = if_is_event<EventType> >
   class EventHandler : public Callback<Event&>
   {
   public:
      using CallbackType = std::function<void (EventType&)>;

      EventHandler() = default;
      explicit EventHandler(CallbackType callback) noexcept;

      virtual void operator()(Event& event) override;

   private:
      CallbackType m_callback;
   };
}

#include "EventHandler.inl"

#endif // ZE_EVENTHANDLER_HPP
