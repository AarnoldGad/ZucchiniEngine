#include "zepch.hpp"

#include "zengine/Backtrace/StackFrame.hpp"

namespace ze
{
   StackFrame::StackFrame(size_t index, std::string const& file, std::string const& function, size_t line, size_t col)
      : m_index(index), m_file(file), m_function(function), m_line(line), m_column(col) {}
}

