inline void ze::CallbackList::subscribe(Callback<Event&>& callback, Priority priority)
{
   m_callbacks[priority].insert(&callback);
}

inline void ze::CallbackList::unsubscribe(Callback<Event&>& callback, Priority priority)
{
   m_callbacks[priority].erase(&callback);
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::iterator ze::CallbackList::begin() noexcept
{
   return m_callbacks.begin();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::iterator ze::CallbackList::end() noexcept
{
   return m_callbacks.end();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::reverse_iterator ze::CallbackList::rbegin() noexcept
{
   return m_callbacks.rbegin();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::reverse_iterator ze::CallbackList::rend() noexcept
{
   return m_callbacks.rend();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::const_iterator ze::CallbackList::begin() const noexcept
{
   return m_callbacks.begin();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::const_iterator ze::CallbackList::end() const noexcept
{
   return m_callbacks.end();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::const_reverse_iterator ze::CallbackList::rbegin() const noexcept
{
   return m_callbacks.rbegin();
}

inline std::map<ze::Priority, std::set<ze::Callback<ze::Event&>*>, std::greater<ze::Priority> >::const_reverse_iterator ze::CallbackList::rend() const noexcept
{
   return m_callbacks.rend();
}
