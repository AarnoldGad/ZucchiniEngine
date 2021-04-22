/**
 * CallbackList.hpp
 * 11 Apr 2021
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
#ifndef ZE_CALLBACKLIST
#define ZE_CALLBACKLIST

#include "zemacros.hpp"

#include "zengine/Common/Priority.hpp"
#include "zengine/Event/Event.hpp"
#include "zengine/Event/Callback.hpp"

#include <map>
#include <set>

namespace ze
{
   class ZE_API CallbackList
   {
   public:
      using Callbacks = std::map<Priority, std::set<Callback<Event&>*>, std::greater<Priority> >;
      using Iterator = Callbacks::iterator;
      using ReverseIterator = Callbacks::reverse_iterator;
      using ConstIterator = Callbacks::const_iterator;
      using ConstReverseIterator = Callbacks::const_reverse_iterator;

      void subscribe(Callback<Event&>& callback, Priority priority = Priority::NORMAL);
      void unsubscribe(Callback<Event&>& callback, Priority priority);

      Iterator begin() noexcept;
      Iterator end() noexcept;
      ReverseIterator rbegin() noexcept;
      ReverseIterator rend() noexcept;

      ConstIterator begin() const noexcept;
      ConstIterator end() const noexcept;
      ConstReverseIterator rbegin() const noexcept;
      ConstReverseIterator rend() const noexcept;

      CallbackList() noexcept = default;

   private:
      Callbacks m_callbacks;
   };
}

#include "inline/Event/CallbackList.inl"

#endif // ZE_CALLBACKLIST
