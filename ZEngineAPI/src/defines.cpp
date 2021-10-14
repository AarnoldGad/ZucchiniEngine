#include "zepch.hpp"

#include "zengine/defines.hpp"

#include "zengine/Backtrace/CallStack.hpp"

void PrintStacktrace()
{
   ze::CallStack stack = ze::Stacktrace(8, 1);
   for (size_t i = 0; i < stack.getSize(); ++i)
      std::cout << "\t at " << (stack[i].toString()) << std::endl;
}
