#include <zengine/zengine.hpp>

int main(int argc, char* argv[])
{
   ze::Arguments args(argc, argv);

   ZE_LOG_DEBUG("Hello Engine");

   ze::Core::Initialise();

   ze::SharedObject app("../../App/bin/app-d.dll");
   auto mainFn = (void (*)(ze::Arguments const&)) app.getSymbol("Main");
   (*mainFn)(args);

   ze::Core::Terminate();
   return 0;
}
