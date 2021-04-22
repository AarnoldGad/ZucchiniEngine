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
#ifndef ZE_SIGNAL
#define ZE_SIGNAL

#include "zemacros.hpp"

#include "zengine/Signal/Connection.hpp"

#include <functional>
#include <list>

namespace ze
{
   template<typename... FnSignature>
   class Signal;

   template<typename ReturnType, typename... Args>
   class Signal<ReturnType(Args...)>
   {
   public:
      using ConnectionType = ze::Connection<ReturnType(Args...)>;
      using ReceiverType = std::function<ReturnType(Args...)>;
      using SignalType = Signal<ReturnType(Args...)>;

      ConnectionType connect(ReceiverType receiver) noexcept;
      void connect(ConnectionType& connection) noexcept;
      void disconnect(ConnectionType& connection) noexcept;
      void clearConnections() noexcept;

      void emit(Args&&... args);

      Signal() noexcept;
      ~Signal() noexcept;

      Signal(SignalType const&) = delete;
      Signal(SignalType&&) = delete;
      SignalType& operator=(SignalType const&) = delete;
      SignalType& operator=(SignalType&&) = delete;

   private:
      void replaceConnection(ConnectionType& oldConnection, ConnectionType& newConnection) noexcept;

      std::list<ConnectionType*> m_connections;

      friend class ze::Connection<ReturnType(Args...)>;
   };
}

#include "inline/Signal/Signal.inl"

#endif // ZE_SIGNAL
