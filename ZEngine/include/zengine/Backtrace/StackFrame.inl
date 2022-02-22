inline size_t ze::StackFrame::getIndex() const noexcept
{
   return m_index;
}

inline std::string const& ze::StackFrame::getFile() const noexcept
{
   return m_file;
}

inline std::string const& ze::StackFrame::getFunction() const noexcept
{
   return m_function;
}

inline size_t ze::StackFrame::getLine() const noexcept
{
   return m_line;
}

inline size_t ze::StackFrame::getColumn() const noexcept
{
   return m_column;
}

