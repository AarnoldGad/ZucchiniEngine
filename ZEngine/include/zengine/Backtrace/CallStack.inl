inline ze::StackFrame const& ze::CallStack::getFrame(size_t index) const
{
   return m_frames.at(index);
}

inline ze::StackFrame const& ze::CallStack::operator[](size_t index) const
{
   return getFrame(index);
}

inline size_t ze::CallStack::getSize() const noexcept
{
   return m_frames.size();
}

inline size_t ze::CallStack::getThreadID() const noexcept
{
   return m_threadID;
}

