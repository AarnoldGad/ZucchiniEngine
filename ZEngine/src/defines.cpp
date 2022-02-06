#include "zepch.hpp"

#include "zengine/defines.hpp"

#include "zengine/Backtrace/CallStack.hpp"

void PrintStacktrace()
{
   ze::Stacktrace(8, 1).print();
}
