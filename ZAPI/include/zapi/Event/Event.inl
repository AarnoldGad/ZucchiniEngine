inline bool ze::Event::isCanceled() const noexcept
{
   return m_canceled;
}

inline ze::Date ze::Event::getTimestamp() const noexcept
{
   return m_timestamp;
}
