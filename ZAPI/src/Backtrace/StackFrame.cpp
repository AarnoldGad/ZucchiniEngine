#include "zepch.hpp"

#include "zapi/Backtrace/StackFrame.hpp"

namespace ze
{
   StackFrame::StackFrame(int number, std::string const& file, std::string const& function)
      : m_number(number), m_file(file), m_function(function) {}

   std::string StackFrame::toString() const noexcept
   {
      std::stringstream ss;
      ss << "#" << getNumber() << " in \"" << getFile() << "\" at " << getFunction();
      return ss.str();
   }
}
