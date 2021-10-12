template<typename Return, typename... Args>
inline bool ze::Signal<Return (Args...)>::addListener(ListenerType& listener)
{
   return m_listeners.insert(&listener).second;
}

template<typename Return, typename... Args>
inline bool ze::Signal<Return (Args...)>::hasListener(ListenerType& listener)
{
   return m_listeners.find(&listener) =! m_listeners.end();
}

template<typename Return, typename... Args>
inline bool ze::Signal<Return (Args...)>::removeListener(ListenerType& listener)
{
   return m_listeners.erase(&listener);
}

template<typename Return, typename... Args>
inline void ze::Signal<Return (Args...)>::emit(Args&&... args)
{
   for (auto& listener : m_listeners)
      listener->notify(std::forward<Args>(args)...);
}

template<typename Return, typename... Args>
ze::Signal<Return (Args...)>::~Signal() noexcept
{
   m_listeners.clear();
}
