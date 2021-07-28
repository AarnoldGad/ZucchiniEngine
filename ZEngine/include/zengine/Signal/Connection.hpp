/**
 * Connection.hpp
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
#ifndef ZE_CONNECTION_HPP
#define ZE_CONNECTION_HPP

#include "zengine/zemacros.hpp"

#include <functional>

namespace ze
{
   template<typename... FnSignature>
   class Signal;

   template<typename... FnSignature>
   class Connection;

   template<typename ReturnType, typename... Args>
   class Connection<ReturnType(Args...)>
   {
   public:
      using SignalType = Signal<ReturnType(Args...)>;
      using ConnectionType = Connection<ReturnType(Args...)>;
      using ReceiverType = std::function<ReturnType(Args...)>;

      void connect(SignalType* signal, ReceiverType receiver) noexcept;
      void disconnect() noexcept;

      explicit operator bool() const noexcept;
      bool isConnected() const noexcept;

      Connection(SignalType& signal, ReceiverType receiver) noexcept;

      Connection(ConnectionType const& other) noexcept;
      Connection(ConnectionType&& other);
      ConnectionType& operator=(ConnectionType const& other) noexcept;
      ConnectionType& operator=(ConnectionType&& other) noexcept;

      Connection() noexcept;
      ~Connection() noexcept;

   private:
      void receiveSignal(Args&&... args);

      SignalType* m_signal;
      ReceiverType m_receiver;

      friend class Signal<ReturnType(Args...)>;
   };
}

#include "Connection.inl"

#endif // ZE_CONNECTION_HPP
