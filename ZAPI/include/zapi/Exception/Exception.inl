inline char const* ze::Exception::description() const noexcept
{
   return m_description.c_str();
}

inline char const* ze::Exception::what() const noexcept
{
   return m_what.c_str();
}

inline SourceLocation ze::Exception::where() const noexcept
{
   return m_where;
}
