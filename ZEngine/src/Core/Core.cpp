#include "zengine/Core/Core.hpp"

#define CORELOGGER_NAME "Core"
#define COREWRITER_FILENAME "zengine.log"

namespace ze
{
   ze::Core& ze::Core::Instance()
   {
      static Core instance;
      return instance;
   }

   void Core::Initialise()
   {
      if (!IsInitialised())
      {
         Instance().initialise();
         Instance().m_initialised = true;
      }
      else
         ZE_LOG_ERROR("Core engine already initialised !");
   }

   void Core::Terminate()
   {
      if (IsInitialised() && !IsRunning())
      {
         Instance().terminate();
         Instance().m_initialised = false;
      }
      else
         ZE_LOG_ERROR("Unable to terminate engine ! Is it even initialised or running ?");
   }

   void Core::ConnectEngine(Engine& engine)
   {
      Instance().connectEngine(engine);
   }

   void Core::DisconnectEngine(Engine& engine)
   {
      Instance().disconnectEngine(engine);
   }

   Application* Core::PlaceApplication(Application& app)
   {
      return Instance().placeApplication(&app);
   }

   Application* Core::RemoveApplication()
   {
      return Instance().placeApplication(nullptr);
   }

   Application* Core::GetApplication() noexcept
   {
      return Instance().m_app;
   }

   void Core::Run()
   {
      if (!IsInitialised()) return (void) ZE_LOG_ERROR("Unable to run terminated engine !");
      if (IsRunning()) return (void) ZE_LOG_ERROR("Engine is already running !");

      Instance().m_running = true;

      try
      {
        Instance().run();
      }
      catch (std::exception const& e)
      {
         ZE_LOG_CRITICAL("Unhandled exception : {}", e.what());
         std::exit(-1);
      }
   }

   bool Core::IsRunning() noexcept
   {
      return Instance().m_running;
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
      : m_app(nullptr), m_initialised(false),
        m_coreWriter(COREWRITER_FILENAME), m_coreLogger(CORELOGGER_NAME, { &m_coreWriter, &ConsoleWriter::Get() }),
        m_appWriter("app.log"), m_appLogger("App", { &m_appWriter, &ConsoleWriter::Get() }),
        m_running(false), m_tickRate{} {}

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

   Application* Core::placeApplication(Application* app)
   {
      Application* oldApp = m_app;
      m_app = app;
      if (oldApp) oldApp->onDisconnection();
      if (m_app) m_app->onConnection();
      return oldApp;
   }

   void Core::initialise()
   {
      ze::Chrono initTime;

      ZE_LOG_INFO("------ Initialising ZEngine ------");
      printRunTimeInformations();

      // There's not much to initialise yet

      m_runTime.restart();

      ZE_LOG_INFO("------ Initialised in {} us !", initTime.elapsed().asMicroseconds());
   }

   void Core::run()
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

   void Core::terminate()
   {
      ZE_LOG_INFO("------ Terminating ZEngine ------");
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

      ZE_LOG_DEBUG("------  * ZEngine version {}-{}.{}{} ({}/{}/{})", ZE_VERSION_MAJOR, ZE_VERSION_MINOR, ZE_VERSION_REV, ZE_VERSION_STAGE, ZE_VERSION_MONTH, ZE_VERSION_DAY, ZE_VERSION_YEAR);
      ZE_LOG_DEBUG("------  * Running on {} {}", sysInfo.os.name, sysInfo.os.versionString);
      ZE_LOG_DEBUG("------      * {}", cpuInfo.model);
      ZE_LOG_DEBUG("------      * {}, {} cores {} thread, {} endian", ::ze::ArchToString(cpuInfo.arch), cpuInfo.cores.physical, cpuInfo.cores.logical, cpuInfo.endian == Endianess::Little ? "little" : "big");
      ZE_LOG_DEBUG("------      * {:.1f}{} physical memory installed", totalMemory, (memoryOrder == 0 ? "B" : (memoryOrder == 1 ? "KB" : "GB")));
   }
}
