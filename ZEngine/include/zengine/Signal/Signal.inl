#include "zengine/Memory/New.hpp"

template<typename Return, typename... Args>
ze::Signal<Return (Args...)>::Signal() noexcept
   : m_listeners{} {}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)> ze::Signal<Return (Args...)>::connect(HandlerFn handler) noexcept
{
   return ListenerType(this, handler);
}

template<typename Return, typename... Args>
void ze::Signal<Return (Args...)>::connect(ListenerType& listener) noexcept
{
   if (listener.m_signal != this) return; // TODO Error Handling ?

   m_listeners.push_back(&listener);
}

template<typename Return, typename... Args>
void ze::Signal<Return (Args...)>::disconnect(ListenerType& listener) noexcept
{
   m_listeners.erase(&listener);
}

template<typename Return, typename... Args>
void ze::Signal<Return (Args...)>::disconnectAll() noexcept
{
   for (auto& listener : m_listeners)
      listener->disconnect();
}

template<typename Return, typename... Args>
void ze::Signal<Return (Args...)>::emit(Args&&... args)
{
   for (auto& listener : m_listeners)
      listener->receive(std::forward<Args>(args)...);
}

template<typename Return, typename... Args>
ze::Signal<Return (Args...)>::~Signal() noexcept
{
   disconnectAll();
}

#include "zengine/Memory/NewOff.hpp"
