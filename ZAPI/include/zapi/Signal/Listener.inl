template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener() noexcept
   : m_handler{}, m_signal(nullptr) {}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(Listener const& other) noexcept
   : m_handler(other.m_handler), m_signal(other.m_signal) {}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(Listener&& other) noexcept
   : m_handler(std::move(other.m_handler)), m_signal(other.m_signal)
{
   other.quitListening();
   if (m_signal)
      listen(*m_signal);
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::Listener(HandlerFn handler, SignalType* signal) noexcept
   : m_handler(std::move(handler)), m_signal(signal)
{
   if (m_signal)
      listen(*m_signal);
}

template<typename Return, typename... Args>
template<typename ReceiverType>
ze::Listener<Return (Args...)>::Listener(Return (ReceiverType::*handler)(Args...), ReceiverType* receiver, SignalType* signal)
   : m_handler{}, m_signal(signal)
{
   if (handler && receiver)
      m_handler = [receiver, handler]
         (Args&&... args) -> Return
         {
            return (receiver->*handler)(std::forward<Args>(args)...);
         };
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>& ze::Listener<Return (Args...)>::operator=(Listener const& other) noexcept
{
   m_handler = other.m_handler;
   m_signal = other.m_signal;

   return *this;
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>& ze::Listener<Return (Args...)>::operator=(Listener&& other) noexcept
{
   other.quitListening();
   quitListening();

   m_handler = std::move(other.m_handler);
   m_signal = std::exchange(other.m_signal, nullptr);

   if (m_signal)
      m_signal->connect(*this);

   return *this;
}

template<typename Return, typename... Args>
template<typename ReceiverType>
inline void ze::Listener<Return (Args...)>::setHandler(Return (ReceiverType::*handler)(Args...), ReceiverType* receiver) noexcept
{
   if (!handler || !receiver) return;

   m_handler = [receiver, handler]
      (Args&&... args) -> Return
      {
         return (receiver->*handler)(std::forward<Args>(args)...);
      };
}

template<typename Return, typename... Args>
inline void ze::Listener<Return (Args...)>::setHandler(HandlerFn handler) noexcept
{
   m_handler = handler;
}

template<typename Return, typename... Args>
inline std::function<Return (Args...)> ze::Listener<Return (Args...)>::getHandler() const noexcept
{
   return m_handler;
}

template<typename Return, typename... Args>
inline bool ze::Listener<Return (Args...)>::listen(SignalType& signal)
{
   quitListening();
   m_signal = &signal;
   return m_signal->addListener(*this);
}

template<typename Return, typename... Args>
inline bool ze::Listener<Return (Args...)>::isListening() const noexcept
{
   return m_signal && m_signal->hasListener(*this);
   //   return m_signal && std::find(m_signal->m_connections.begin(), m_signal->m_connections.end(), this) != m_signal->m_connections.end();
}

template<typename Return, typename... Args>
inline bool ze::Listener<Return (Args...)>::quitListening()
{
   bool quit = m_signal ? m_signal->removeListener(*this) : false;
   m_signal = nullptr;
   return quit;
}

template<typename Return, typename... Args>
inline Return ze::Listener<Return (Args...)>::notify(Args&&... args)
{
   return m_handler(std::forward<Args>(args)...);
}

template<typename Return, typename... Args>
ze::Listener<Return (Args...)>::~Listener() noexcept
{
   quitListening();
}
