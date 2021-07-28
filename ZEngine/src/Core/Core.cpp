#include "zepch.hpp"

#include "zengine/Core/Core.hpp"
#include "zengine/Common/System.hpp"

#include <cstdlib>

#include "zengine/Memory/New.hpp"

#define CORELOGGER_NAME "Core"
#define CORELOGGER_FILENAME "zengine.log"

namespace ze
{
   Core& Core::Instance()
   {
      static Core instance;
      return instance;
   }

   void Core::Run()
   {
      if (IsRunning()) return ZE_LOG_ERROR("Engine is already running !");

      Instance().m_running = true;

      try
      {
         Instance().mainLoop();
      }
      catch (std::exception const& e)
      {
         ZE_LOG_CRITICAL("Unhandled exception : %s", e.what());
         std::exit(-1);
      }
   }

   void Core::Stop() noexcept
   {
      Instance().m_running = false;
   }

   void Core::SetTickRate(unsigned int rate) noexcept
   {
      Instance().m_tickRate = rate;
   }

   Core::Core()
      : m_initialised(false), m_coreWriter(CORELOGGER_FILENAME), m_coreLogger(CORELOGGER_NAME, &m_coreWriter),
        m_running(false), m_tickRate{}, m_app(nullptr) {}

   void Core::initialise()
   {
      if (isInitialised()) return ZE_LOG_ERROR("Core engine already initialised !");

      ze::Chrono initTime;

      ZE_LOG_INFO("------ Initialising ZEngine ------");
      printRunTimeInformations();

      // There's not much to initialise yet

      setInitialised();
      m_runTime.restart();

      ZE_LOG_INFO("------ Initialised in %d ms !", initTime.elapsed().asMilliseconds());
   }

   Application* Core::placeApplication(Application& app)
   {
      Application* oldApp = m_app;
      m_app = &app;
      m_app->onConnection();
      return oldApp;
   }

   Application* Core::removeApplication()
   {
      Application* oldApp = m_app;
      m_app = nullptr;
      oldApp->onDisconnection();
      return oldApp;
   }

   void Core::connectEngine(Engine& engine)
   {
      bool engineConnected = m_engines.insert(&engine).second;

      if (engineConnected)
         engine.initialise();
      else
         ZE_LOG_ERROR("Trying to connect same engine multiple times !");
   }

   void Core::disconnectEngine(Engine& engine)
   {
      bool engineDisconnected = m_engines.erase(&engine);

      if (engineDisconnected)
         engine.terminate();
      else
         ZE_LOG_ERROR("Trying to disconnect unknown engine !");
   }

   void Core::mainLoop()
   {
      Time deltaTime;
      Chrono loopTime;

      while (void(deltaTime = loopTime.restart()), IsRunning())
      {
         tickEngines(deltaTime);
         tickApplication(deltaTime);

         UseEventBus().dispatchEvents();

         capTickRate(loopTime.elapsed());
      }
   }

   void Core::tickApplication(Time deltaTime)
   {
      if (m_app != nullptr)
         m_app->tick(deltaTime);
   }

   void Core::tickEngines(Time deltaTime)
   {
      for (Engine* engine : m_engines)
         engine->tick(deltaTime);
   }

   void Core::capTickRate(Time loopTime)
   {
      if (m_tickRate > 0)
      {
         Time loopPeriod = ze::Seconds(1.0 / static_cast<double>(m_tickRate));
         if (loopTime < loopPeriod)
            ze::Sleep(loopPeriod - loopTime);
      }
   }

   void Core::terminate()
   {
      if (m_running) return; // TODO Error handling
      
      setInitialised(false);
      
      ZE_LOG_INFO("------ Terminating ZEngine ------");
   }

   bool Core::isInitialised() noexcept
   {
      return m_initialised;
   }

   void Core::setInitialised(bool value) noexcept
   {
      m_initialised = value;
   }

   void Core::printRunTimeInformations()
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

      ZE_LOG_DEBUG("------  * ZEngine version %u-%u.%u%s (%u/%u/%u)", ZE_VERSION_MAJOR, ZE_VERSION_MINOR, ZE_VERSION_REV, ZE_VERSION_SPEC, ZE_VERSION_MONTH, ZE_VERSION_DAY, ZE_VERSION_YEAR);
      ZE_LOG_DEBUG("------  * Running on %s %s", sysInfo.os.name.c_str(), sysInfo.os.versionString.c_str());
      ZE_LOG_DEBUG("------      * %s", cpuInfo.model.c_str());
      ZE_LOG_DEBUG("------      * %s, %u cores %u thread, %s endian", ::ze::ArchToString(cpuInfo.arch).c_str(), cpuInfo.cores.physical, cpuInfo.cores.logical, cpuInfo.endian == Endianess::Little ? "little" : "big");
      ZE_LOG_DEBUG("------      * %.1f%s physical memory installed", totalMemory, (memoryOrder == 0 ? "B" : (memoryOrder == 1 ? "KB" : "GB")));
   }
}
