#include "zengine/zemacros.hpp"

#include "zengine/Common/Backtrace/CallStack.hpp"

#include "zengine/Memory/New.hpp"

void PrintStacktrace()
{
   ze::CallStack stack = ze::Stacktrace(8, 1);
   for (size_t i = 0; i < stack.getSize(); ++i)
      std::cout << "\t at " << (stack[i].toString()) << std::endl;
}
