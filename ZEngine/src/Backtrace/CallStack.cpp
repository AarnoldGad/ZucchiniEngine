#include "zepch.hpp"

#include "zengine/Backtrace/CallStack.hpp"
#include <backward.hpp>
#include <ostream>
#include <sstream>

namespace ze
{
   CallStack::CallStack(RangedInt<0, 32> size, int skip)
   {
      m_stack.load_here(size);
      m_stack.skip_n_firsts(skip);
   }

   void CallStack::print(std::ostream& os) const
   {
      backward::Printer p;
      p.print(m_stack, os);
   }

   CallStack Stacktrace(RangedInt<0, 32> size, int skip)
   {
      return CallStack(size, skip + 1);
   }
}
