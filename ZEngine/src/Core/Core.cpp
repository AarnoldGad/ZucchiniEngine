#include "zepch.hpp"

#include "zengine/Core/Core.hpp"
#include "zengine/Common/System.hpp"
#include "zengine/Event/EventDispatcher.hpp"

#include <cstdlib>

#include "zengine/Memory/New.hpp"

#define CORELOGGER_NAME "Core"
#define CORELOGGER_FILENAME "zengine.log"

namespace ze
{
   namespace
   {
      void PrintRunTimeInformations()
      {
         System sysInfo = ::ze::GetSystemInfo();
         Processor cpuInfo = ::ze::GetProcessorInfo();
         Memory memInfo = ::ze::GetMemoryInfo();

         double totalMemory = static_cast<double>(memInfo.total);
         int memoryOrder = 0;
         while (totalMemory > 1024.0)
         {
            totalMemory /= 1024.0;
            ++memoryOrder;
         }

         ZE_LOG_INFO("------  * ZEngine version %u-%u.%u%s (%u/%u/%u)", ZE_VERSION_MAJOR, ZE_VERSION_MINOR, ZE_VERSION_REV, ZE_VERSION_SPEC, ZE_VERSION_MONTH, ZE_VERSION_DAY, ZE_VERSION_YEAR);
         ZE_LOG_INFO("------  * Running on %s %s", sysInfo.os.name.c_str(), sysInfo.os.versionString.c_str());
         ZE_LOG_INFO("------      * %s", cpuInfo.model.c_str());
         ZE_LOG_INFO("------      * %s, %u cores %u thread", ::ze::ArchToString(cpuInfo.arch).c_str(), cpuInfo.cores.physical, cpuInfo.cores.logical);
         ZE_LOG_INFO("------      * %.1f%s physical memory installed", totalMemory, (memoryOrder == 0 ? "B" : (memoryOrder == 1 ? "KB" : "GB")));
      }
   }

   bool Core::s_initialised = false;

   DebugFileWriter Core::s_coreWriter(CORELOGGER_FILENAME);
   Logger Core::s_coreLogger(CORELOGGER_NAME, &s_coreWriter);

   bool Core::s_running = false;
   unsigned int Core::s_tickRate{};

   Application* Core::s_app = nullptr;
   std::set<Engine*> Core::s_engines{};

   void Core::Initialise()
   {
      if (Core::IsInitialised()) return ZE_LOG_ERROR("Core engine already initialised !");

      ze::Chrono initTime;

      ZE_LOG_INFO("------ Initialising ZEngine ------");
      PrintRunTimeInformations();

      // There's not much to initialise yet

      Core::SetInitialised();
      s_runTime.restart();

      ZE_LOG_INFO("------ Initialised in %d ms !", initTime.elapsed().asMilliseconds());
   }

   void Core::PlaceApplication(Application* app)
   {
      s_app = app;
   }

   void Core::ConnectEngine(Engine& engine)
   {
      bool engineConnected = s_engines.insert(&engine).second;

      if (engineConnected)
         engine.initialise();
      else
         ZE_LOG_ERROR("Trying to connect same engine multiple times !");
   }

   void Core::DisconnectEngine(Engine& engine)
   {
      bool engineDisconnected = s_engines.erase(&engine);

      if (engineDisconnected)
         engine.terminate();
      else
         ZE_LOG_ERROR("Trying to disconnect unknown engine !");
   }

   void Core::SetTickRate(unsigned int rate) noexcept
   {
      s_tickRate = rate;
   }

   void Core::Run()
   {
      if (IsRunning()) return ZE_LOG_ERROR("Engine is already running !");

      s_running = true;

      try
      {
         MainLoop();
      }
      catch (std::exception const& e)
      {
         ZE_LOG_CRITICAL("Unhandled exception : %s", e.what());
         std::exit(-1);
      }
   }

   void Core::MainLoop()
   {
      Time deltaTime;
      Chrono loopTime;

      while (deltaTime = loopTime.restart(), IsRunning())
      {
         TickApplication(deltaTime);
         TickEngines(deltaTime);

         CapTickRate(loopTime.elapsed());
      }
   }

   void Core::TickApplication(Time deltaTime)
   {
      if (GetApplication() != nullptr)
         GetApplication()->tick(deltaTime);
   }

   void Core::TickEngines(Time deltaTime)
   {
      for (Engine* engine : s_engines)
         engine->tick(deltaTime);
   }

   void Core::CapTickRate(Time loopTime)
   {
      if (GetTickRate() > 0)
      {
         Time loopPeriod = ze::Seconds(1.0 / static_cast<double>(GetTickRate()));
         if (loopTime < loopPeriod)
            ze::Sleep(loopPeriod - loopTime);
      }
   }

   void Core::Stop() noexcept
   {
      s_running = false;
   }

   void Core::Terminate()
   {
      if (IsRunning()) return; // TODO Error handling
      
      Core::SetInitialised(false);

      ZE_LOG_INFO("------ Terminating ZEngine ------");
   }

   bool Core::IsInitialised() noexcept
   {
      return s_initialised;
   }

   void Core::SetInitialised(bool value) noexcept
   {
      s_initialised = value;
   }
}
