inline int ze::StackFrame::getNumber() const noexcept
{
   return m_number;
}

inline std::string ze::StackFrame::getFile() const noexcept
{
   return m_file;
}

inline std::string ze::StackFrame::getFunction() const noexcept
{
   return m_function;
}
