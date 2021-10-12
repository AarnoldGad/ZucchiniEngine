#include <iostream>
#include <zengine/zengine.hpp>

int main(int argc, char* argv[])
{
   ze::DebugFileWriter coreWriter("zengine.log");
   ze::Logger coreLogger("Core", &coreWriter);

   coreLogger.debug().logLine("Hello Engine");
   return 0;
}
