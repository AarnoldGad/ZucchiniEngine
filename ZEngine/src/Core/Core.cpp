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
   Core* Core::s_app = nullptr;

   Core& Core::GetApplication()
   {
      zassert(s_app != nullptr, "No application !");
      return *s_app;
   }

   Core::Core(std::string const& appName)
       : m_appName(appName), m_isInitialised(false), m_coreWriter(CORELOGGER_FILENAME),
        m_clientWriter(getApplicationName() + ".log"), m_coreLogger(CORELOGGER_NAME), m_clientLogger(getApplicationName()),
        m_shouldPop(false), m_running(false), m_tickRate{}
   {
      s_app = this;
   }

   void Core::initialise()
   {
      // Debug guard
      zassert(m_isInitialised == false, "Engine has already been initialised !");

      ze::Chrono initTime;

      // Init loggers
      m_coreLogger.setWriter(&m_coreWriter);
      m_clientLogger.setWriter(&m_clientWriter);

      // Print system informations
      System sysInfo = ::ze::GetSystemInfo();
      Processor cpuInfo = ::ze::GetProcessorInfo();
      Memory memInfo = ::ze::GetMemoryInfo();

      double totalMemory = static_cast<double>(memInfo.total);
      int memoryOrder = 0;
      while (totalMemory > 1024.)
      {
         totalMemory /= 1024.;
         ++memoryOrder;
      }

      ZE_LOG_INFO("------ Initialising ZEngine ------");
      ZE_LOG_INFO("------  * ZEngine version %u-%u.%u.%u", ZE_VERSION_MAJOR, ZE_VERSION_MINOR, ZE_VERSION_PATCH, ZE_VERSION_REV);
      ZE_LOG_INFO("------  * Running on %s %s", sysInfo.os.name.c_str(), sysInfo.os.versionString.c_str());
      ZE_LOG_INFO("------      * %s", cpuInfo.model.c_str());
      ZE_LOG_INFO("------      * %s, %u cores %u thread", ::ze::ArchToString(cpuInfo.arch).c_str(), cpuInfo.cores.physical, cpuInfo.cores.logical);
      ZE_LOG_INFO("------      * %.1f%s physical memory installed", totalMemory, (memoryOrder == 0 ? "B" : (memoryOrder == 1 ? "KB" : "GB")));
      ZE_LOG_INFO("------  * Creating new application %s", getApplicationName().c_str());

      m_eventSubscriber = useEventBusTo().subscribe(&Core::handleEvent, this);

      m_isInitialised = true;

      ZE_LOG_INFO("------ Initialised in %d ms !", initTime.elapsed().asMilliseconds());
   }

   void Core::connectEngine(Engine& engine)
   {
      bool wasInserted = m_engines.insert(&engine).second;

      if (wasInserted)
         engine.initialise();
      else
         LOG_TRACE("Trying to connect same engine multiple times !");
   }

   void Core::disconnectEngine(Engine& engine)
   {
      bool wasErased = m_engines.erase(&engine);

      if (wasErased)
         engine.terminate();
      else
         LOG_TRACE("Trying to disconnect unknown engine !");
   }

   void Core::setTickRate(unsigned int rate) noexcept
   {
      m_tickRate = rate;
   }

   void Core::popState()
   {
      m_shouldPop = true;
   }

   void Core::run()
   {
      if (isRunning()) return;

      m_running = true;
      m_shouldPop = false;
      m_runTime.restart();

      try
      {
         mainLoop();
      }
      catch (std::exception const& e)
      {
         ZE_LOG_CRITICAL("Unhandled exception : %s", e.what());
         std::exit(-1);
      }
   }

   void Core::mainLoop()
   {
      Time deltaTime;
      Chrono loopTime;

      while (m_running)
      {
         deltaTime = loopTime.restart();

         popRegisteredState();

         tickEngines(deltaTime);

         if (hasState())
         {
            State& state = *(m_states.back());
            state.tick(deltaTime);
         }

         useEventBusTo().dispatchEvents();

         capTickRate(loopTime);
      }
   }

   void Core::popRegisteredState()
   {
      if (m_shouldPop && hasState())
      {
         State* state = m_states.back();
         m_states.pop_back();

         state->onDisconnection();
         delete state;
      }

      m_shouldPop = false;
   }

   void Core::tickEngines(Time deltaTime)
   {
      for (Engine* engine : m_engines)
         engine->tick(deltaTime);
   }

   void Core::handleEvent(Event& event)
   {
      EventDispatcher dispatcher(event);

      if (hasState())
         dispatcher.dispatch(&State::handleEvent, m_states.back());
   }

   void Core::capTickRate(Chrono loopTime)
   {
      if (m_tickRate)
      {
         Time loopPeriod = ze::Seconds(1.0 / static_cast<double>(m_tickRate));
         if (loopTime.elapsed() < loopPeriod)
            ze::Sleep(loopPeriod - loopTime.elapsed());
      }
   }

   void Core::clearStates()
   {
      for (State* state : m_states)
      {
         state->onDisconnection();
         delete state;
      }

      m_states.clear();
   }

   void Core::stop() noexcept
   {
      m_running = false;
      clearStates();
      ZE_LOG_INFO("------ Application %s ran for %d ms !", getApplicationName().c_str(), getRunTime().asMilliseconds());
   }

   void Core::terminate()
   {
      ZE_LOG_INFO("------ Terminating ZEngine ------");
   }

   Core::~Core() noexcept
   {
      if (isRunning())
         stop();

      clearStates();
   }
}
