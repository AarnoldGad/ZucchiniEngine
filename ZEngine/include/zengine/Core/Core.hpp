/**
 * Core.hpp
 * 18 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_CORE
#define ZE_CORE

#include "zengine/zemacros.hpp"

#include "zengine/Abstract/Singleton.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Event/EventBus.hpp"
#include "zengine/Event/Subscriber.hpp"
#include "zengine/Time/Chrono.hpp"
#include "zengine/Core/Engine.hpp"

#include <unordered_set>
#include <string>
#include <iostream>
#include <fstream>

namespace ze
{
   class ZE_API Core : public Engine
   {
   public:
      static Core& GetApplication();

      void initialise();

      void connectEngine(Engine& engine);
      void disconnectEngine(Engine& engine);

      std::string getApplicationName() const noexcept;

      void run();
      bool isRunning() const noexcept;
      void stop() noexcept;

      template<typename StateType, typename... Args>
      void pushState(Args&&... args);
      void popState();

      Logger& useCoreLogger() noexcept;
      Logger& useClientLogger() noexcept;
      EventBus& useEventBusTo() noexcept;

      void setTickRate(unsigned int rate) noexcept;

      Time getRunTime() const noexcept;
      unsigned int getTickRate() const noexcept;

      void terminate();

   protected:
      Core(std::string const& appName = "Zucchini Sprout");
      virtual ~Core() noexcept;

      static Core* s_app;

   private:
      void mainLoop();

      void tickEngines(Time deltaTime);
      void tickStates(Time deltaTime);
      void handleEvent(Event& event);

      void capTickRate(Chrono loopTime);

      void clearStates();

      std::string m_appName;
      bool m_isInitialised;

      Logger m_coreLogger;
      std::ofstream m_coreLog; // TODO File System
      Logger m_clientLogger;
      std::ofstream m_clientLog; // TODO File System

      EventBus m_eventBus;
      std::vector<State*> m_states;

      bool m_running;
      Chrono m_runTime; // Starts when application is constructed and run till its destruction
      unsigned int m_tickRate;

      Subscriber<Event> m_eventSubscriber;
      std::unordered_set<Engine*> m_engines;
   };
}

#include "Core.inl"

#endif // ZE_CORE
