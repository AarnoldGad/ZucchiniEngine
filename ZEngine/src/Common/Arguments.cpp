#include "zepch.hpp"

#include "zengine/Common/Arguments.hpp"

namespace ze
{
   Arguments::Arguments(int argc, char* argv[])
      : m_arguments(argc)
   {
      for (int i = 0; i < argc; ++i)
      {
         auto next = m_arguments.begin() + i + 1;
         if (next < m_arguments.end())
            m_arguments[i] = { argv[i], &*next };
         else
            m_arguments[i] = { argv[i], nullptr };
      }
   }

   size_t Arguments::getCount() const noexcept
   {
      return m_arguments.size();
   }

   Arguments::Argument const* Arguments::getArgument(size_t index) const
   {
      return &m_arguments.at(index);
   }

   Arguments::Argument const* Arguments::find(std::string const& value) const
   {
      auto found = std::find_if(m_arguments.begin(), m_arguments.end(),
                                [&value](Argument const& argument) { return argument.value == value; });
      return found != m_arguments.end() ? &*found : nullptr;
   }
}
