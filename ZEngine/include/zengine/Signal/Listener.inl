#include "zengine/Memory/New.hpp"

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener() noexcept
   : m_signal(nullptr), m_handler() {}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(Listener const& other) noexcept
   : m_signal(other.m_signal), m_handler(other.m_handler) {}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(Listener&& other)
   : m_signal(other.m_signal), m_handler(std::move(other.m_handler))
{
   other.disconnect();
   if (m_signal)
      m_signal->connect(*this);
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(HandlerFn handler, SignalType* signal) noexcept
   : m_signal(signal), m_handler(std::move(handler))
{
   if (m_signal)
      m_signal->connect(*this);
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>& ze::Listener<Return (Args...)>::operator=(Listener const& other) noexcept
{
   m_signal = other.m_signal;
   m_handler = other.m_handler;

   return *this;
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>& ze::Listener<Return (Args...)>::operator=(Listener&& other) noexcept
{
   other.disconnect();
   disconnect();

   m_signal = std::exchange(other.m_signal, nullptr);
   m_handler = std::move(other.m_handler);

   if (m_signal)
      m_signal->connect(*this);

   return *this;
}

template <typename Return, typename... Args>
void ze::Listener<Return (Args...)>::setHandler(HandlerFn handler) noexcept
{
   m_handler = handler;
}

template <typename Return, typename... Args>
inline std::function<Return (Args...)> ze::Listener<Return (Args...)>::getHandler() const noexcept
{
   return m_handler;
}

template<typename Return, typename... Args>
void ze::Listener<Return (Args...)>::connect(SignalType& signal) noexcept
{
   disconnect();
   m_signal = &signal;
   m_signal->connect(*this);
}

template<typename Return, typename... Args>
inline ze::Listener<Return (Args...)>::operator bool() const noexcept
{
   return isConnected();
}

template<typename Return, typename... Args>
inline bool ze::Listener<Return (Args...)>::isConnected() const noexcept
{
   return m_signal && m_signal->isConnected(*this);
   //   return m_signal && std::find(m_signal->m_connections.begin(), m_signal->m_connections.end(), this) != m_signal->m_connections.end();
}

template<typename Return, typename... Args>
Return ze::Listener<Return (Args...)>::receive(Args&&... args)
{
   return m_handler(std::forward<Args>(args)...);
}

template<typename Return, typename... Args>
void ze::Listener<Return (Args...)>::disconnect() noexcept
{
   if (m_signal)
      m_signal->disconnect(*this);

   m_signal = nullptr;
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::~Listener() noexcept
{
   disconnect();
}

#include "zengine/Memory/NewOff.hpp"
