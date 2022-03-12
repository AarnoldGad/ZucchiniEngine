/**
 * Listener.hpp
 * 6 Feb 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
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
#ifndef ZE_LISTENER_HPP
#define ZE_LISTENER_HPP

#include "zengine/defines.hpp"

#include "zengine/Common/Observer.hpp"
#include "zengine/Signal/Signal.hpp"

#include <functional>

namespace ze
{
   template<typename FnSignature>
   class Listener;

   template<typename Return, typename... Args>
   class Listener<Return (Args...)> : public Observer<Return (Args...)>
   {
   public:
      using SignalType = Signal<Return (Args...)>;
      using HandlerFn = std::function<Return (Args...)>;

      bool listen(SignalType& signal);
      bool isListening() const noexcept;
      bool quitListening();

      Return notify(Args&&... args) override;

      template<typename ReceiverType>
      void setHandler(Return (ReceiverType::*handler)(Args...), ReceiverType* receiver) noexcept;
      void setHandler(HandlerFn handler) noexcept;
      HandlerFn getHandler() const noexcept;

      template<typename ReceiverType>
      Listener(Return (ReceiverType::*handler)(Args...), ReceiverType* receiver, SignalType* signal = nullptr);
      explicit Listener(HandlerFn handler, SignalType* signal = nullptr) noexcept;

      Listener(Listener const& other) noexcept;
      Listener(Listener&& other) noexcept;
      Listener& operator=(Listener const& other) noexcept;
      Listener& operator=(Listener&& other) noexcept;

      Listener() noexcept;
      ~Listener() noexcept;

   private:
      HandlerFn m_handler;
      SignalType* m_signal;
   };
}

#include "Listener.inl"

#endif // ZE_LISTENER_HPP
