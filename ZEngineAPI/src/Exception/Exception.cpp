#include "zepch.hpp"

#include "zengine/Exception/Exception.hpp"

#include <sstream>

namespace ze
{
   Exception::Exception(SourceLocation const& location, std::string&& message) noexcept
      : m_what(std::move(message)), m_where(location), m_backtrace(Stacktrace(32, 1))
   {
      std::stringstream desc;
      desc << "An exception occured : " << m_what << "\n\t"
           << "at " << m_where.file << "::" << m_where.function << ":" << m_where.line << std::endl;
      m_description = desc.str();
   }
}
