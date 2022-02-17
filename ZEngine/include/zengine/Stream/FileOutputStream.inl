inline bool ze::FileOutputStream::isOpen() const
{
   return m_file.is_open();
}

inline ze::FileOutputStream::operator bool() const
{
   return isOpen() && !m_file.fail();
}

