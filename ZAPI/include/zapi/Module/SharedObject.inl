inline bool ze::SharedObject::isLoaded() const noexcept
{
   return static_cast<bool>(m_handle);
}

inline ze::SharedObject::operator bool() const noexcept
{
   return isLoaded();
}

inline void* ze::SharedObject::getHandle() const noexcept
{
   return m_handle;
}
