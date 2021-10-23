#include <zengine/zengine.hpp>

#include <optional>
#include <filesystem>

std::optional<std::filesystem::path> findAppFile(ze::Arguments const& args)
{
   ze::Arguments::Argument const* appLibArg = args.find("--app-lib"); // Find corresponding argument

   if (appLibArg && appLibArg->next) // Check argument validity
      return appLibArg->next->value;

   return std::nullopt;
}

int main(int argc, char* argv[])
{
   ze::Arguments args(argc, argv);

   ZE_LOG_DEBUG("Hello Engine !");
   auto appLibPath = findAppFile(args); // Get library location

   if (appLibPath)
   {
      ze::SharedObject appLib(appLibPath.value()); // Load app library
      auto appEntryPoint = (void (*)(ze::Arguments const&)) appLib.getSymbol("Main"); // Get application's "Main" entry point function

      if (appLib && appEntryPoint)
      {
         ze::Core::Initialise();

         (*appEntryPoint)(args); // Run application

         ze::Core::Terminate();
      }
      else
         ZE_LOG_ERROR("Fail to catch application entry point !");
   }
   else
      ZE_LOG_ERROR("No application library specified !");

   return 0;
}
