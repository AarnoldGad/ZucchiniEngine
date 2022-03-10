inline bool ze::Event::isCanceled() const noexcept
{
   return m_canceled;
}

inline ze::Time ze::Event::getTimestamp() const noexcept
{
   return m_timestamp;
}
