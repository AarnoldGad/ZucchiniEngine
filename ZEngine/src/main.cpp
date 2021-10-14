#include <iostream>
#include <zengine/zengine.hpp>

int main(int argc, char* argv[])
{
   ze::DebugFileWriter coreWriter("zengine.log");
   ze::Logger coreLogger("Core", &coreWriter);

   coreLogger.debug().logLine("Hello Engine");

   ze::SharedObject app("../../App/bin/app-d.dll");
   auto mainFn = (void (*)(void)) app.getSymbol("Main");
   (*mainFn)();
   return 0;
}
