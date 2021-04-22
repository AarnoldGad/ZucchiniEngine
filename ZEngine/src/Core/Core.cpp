#include "zepch.hpp"

#include "zengine/Core/Core.hpp"
#include "zengine/Common/System.hpp"

#include <cstdlib>

namespace ze
{
   Core* Core::s_app = nullptr;

   Core& Core::GetApplication()
   {
      zassert(s_app != nullptr, "No application !");
      return *s_app;
   }

   Core::Core(std::string const& appName)
      : m_appName(appName), m_isInitialised(false), m_coreLogger("CORE"), m_clientLogger(getApplicationName()), m_running(false), m_tickRate{}
   {
      s_app = this;
   }

   void Core::initialise()
   {
      ze::Chrono initTime;
      // Debug guard
      zassert(m_isInitialised == false, "Engine has already been initialised !");

      // Init loggers
      m_coreLogger.setLogToConsole(true);
      m_clientLogger.setLogToConsole(true);

      m_coreLog.open("zengine.log");
      if (m_coreLog)
         m_coreLogger.setOutput(m_coreLog);
      else
         LOG_TRACE("Unable to open core log file !");

      m_clientLog.open(getApplicationName() + ".log");
      if (m_clientLog)
         m_clientLogger.setOutput(m_clientLog);
      else
         LOG_TRACE("Unable to open client log file !");

      // Print system informations
      System sysInfo = ::ze::GetSystemInfo();
      Processor cpuInfo = ::ze::GetProcessorInfo();
      Memory memInfo = ::ze::GetMemoryInfo();

      ZE_LOG_INFO("------ Initialising ZEngine ------");
      ZE_LOG_INFO("------  * ZEngine version ", ZE_VERSION_MAJOR, "-", ZE_VERSION_MINOR, ".", ZE_VERSION_PATCH, ".", ZE_VERSION_REV);
      ZE_LOG_INFO("------  * Running on ", sysInfo.os.name, " v", sysInfo.os.versionString);
      ZE_LOG_INFO("------      * ", cpuInfo.model);
      ZE_LOG_INFO("------      * ", ::ze::ArchToString(cpuInfo.arch), ", ", cpuInfo.cores.physical, " cores ", cpuInfo.cores.logical, " threads");
      ZE_LOG_INFO("------      * ", memInfo.total, "kB physical memory");
      ZE_LOG_INFO("------  * Creating new application ", getApplicationName());

      // Init Sub-Systems
      m_eventSubscriber = useEventBusTo().subscribe<Event>(&Core::handleEvent, this, Priority::VERY_HIGH);

      m_isInitialised = true;

      ZE_LOG_INFO("------ Initialised in ", initTime.elapsed().asMilliseconds(), "ms !");
      ZE_LOG_INFO("");
   }

   void Core::connectEngine(Engine& engine)
   {
      zassert(&engine == static_cast<Engine*>(this), "Can't connect Core engine to itself !");

      bool hasBeenInserted = m_engines.insert(&engine).second;

      if (hasBeenInserted)
         engine.initialise();
      else
         LOG_TRACE("Trying to connect engine multiple times !");
   }

   void Core::disconnectEngine(Engine& engine)
   {
      bool hasBeenErased = m_engines.erase(&engine);

      if (hasBeenErased)
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
      if (m_states.size() == 0) return;

      m_states.back()->onDisconnection();
      m_states.pop_back();
   }

   void Core::run()
   {
      m_running = true;
      m_runTime.restart();

      try
      {
         mainLoop();
      }
      catch (std::exception const& e)
      {
         useCoreLogger().critical() << "Unhandled exception : " << e.what();
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

         auto states = m_states;
         tick(states, deltaTime);

         tickEngines(deltaTime);
         tickStates(deltaTime);

         useEventBusTo().dispatchEvents();

         capTickRate(loopTime);
      }
   }

   void Core::tickEngines(Time deltaTime)
   {
      auto states = m_states;

      for (Engine* engine : m_engines)
         engine->tick(states, deltaTime);
   }

   void Core::tickStates(Time deltaTime)
   {
      auto states = m_states;

      // Tick states in reverse order (top state first)
      for (auto stateIt = states.rbegin(); stateIt != states.rend(); ++stateIt)
         if ((*stateIt)->tick(deltaTime) != State::SPREAD)
            break;
   }

   void Core::handleEvent(Event& event)
   {
      auto states = m_states;

      // Handle event in reverse order (top state first)
      for (auto stateIt = states.rbegin(); stateIt != states.rend(); ++stateIt)
         if ((*stateIt)->handleEvent(event) != State::SPREAD)
            break;
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
         delete state;

      m_states.clear();
   }

   void Core::stop() noexcept
   {
      m_runTime.pause();
      m_running = false;
      clearStates();
      ZE_LOG_INFO("------ Application ", getApplicationName(), " ran for ", getRunTime().asMilliseconds(), "ms !");
   }

   void Core::terminate()
   {
      ZE_LOG_INFO("------ Terminating ZEngine ------");
   }

   Core::~Core() noexcept
   {
      if (isRunning())
         stop();
   }
}
