#include "zepch.hpp"

#include "zengine/Backtrace/CallStack.hpp"
#include <backward.hpp>

namespace ze
{
   CallStack::CallStack(RangedInt<0, 32> size, int skip)
   {
      m_stack.load_here(size);
      m_stack.skip_n_firsts(skip);
   }

   void CallStack::print() const
   {
      backward::Printer p;
      p.print(m_stack);
   }

   CallStack Stacktrace(RangedInt<0, 32> size, int skip)
   {
      return CallStack(size, skip + 1);
   }
}
