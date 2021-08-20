#include <zengine/Memory/New.hpp>

inline size_t ze::CallStack::getSize() const noexcept
{
   return m_frames.size();
}

inline ze::StackFrame const& ze::CallStack::getFrame(size_t index) const
{
   return m_frames[index];
}

inline ze::StackFrame const& ze::CallStack::operator[](size_t index) const
{
   return getFrame(index);
}

#include <zengine/Memory/NewOff.hpp>
