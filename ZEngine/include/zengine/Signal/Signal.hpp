/**
 * Signal.hpp
 * 6 Feb 2021
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
#ifndef ZE_SIGNAL_HPP
#define ZE_SIGNAL_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Common/Observer.hpp"

#include <functional>
#include <unordered_set>

namespace ze
{
   template<typename FnSignature>
   class Signal;

   template<typename Return, typename... Args>
   class Signal<Return (Args...)>
   {
   public:
      using ListenerType = ze::Observer<Return (Args...)>;
      using HandlerFn = std::function<Return (Args...)>;

      bool addListener(ListenerType& listener);
      bool hasListener(ListenerType& listener);
      bool removeListener(ListenerType& listener);

      void emit(Args&&... args);

      Signal(Signal const&) = delete;
      Signal(Signal&&) = delete;
      Signal& operator=(Signal const&) = delete;
      Signal& operator=(Signal&&) = delete;

      Signal() = default;
      ~Signal() noexcept;

   private:
      std::unordered_set<ListenerType*> m_listeners;
   };
}

#include "Signal.inl"

#endif // ZE_SIGNAL_HPP
