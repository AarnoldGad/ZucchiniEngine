/**
 * Core.hpp
 * 18 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
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
#ifndef ZE_CORE_HPP
#define ZE_CORE_HPP

#include "zengine/defines.hpp"

#include "zengine/Core/Application.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Log/FileWriter.hpp"
#include "zengine/Event/EventBus.hpp"
#include "zengine/Time/Chrono.hpp"
#include "zengine/Core/Engine.hpp"

#include <set>
#include <string>
#include <iostream>
#include <fstream>

namespace ze
{
   class ZE_API Core final
   {
   public:
      static void Initialise();
      static bool IsInitialised();
      static void Terminate();

      static void ConnectEngine(Engine& engine);
      static void DisconnectEngine(Engine& engine);

      static Application* PlaceApplication(Application& app);
      static Application* GetApplication() noexcept;
      static Application* RemoveApplication();

      static void Run();
      static bool IsRunning() noexcept;
      static void Stop() noexcept;

      static EventBus& UseEventBus() noexcept;
      static Logger& UseCoreLogger() noexcept;
      static Logger& UseAppLogger() noexcept;

      static void SetTickRate(unsigned int rate) noexcept;
      static unsigned int GetTickRate() noexcept;
      static Time GetTime() noexcept;

      static Core& Instance();

      void initialise();
      void run();
      void terminate();

      bool isInitialised();

      void connectEngine(Engine& engine);
      void disconnectEngine(Engine& engine);

      Application* placeApplication(Application* app);

      Core();
      ~Core() = default;

      Core(Core const&) = delete;
      Core(Core&&) = delete;
      Core& operator=(Core const&) = delete;
      Core& operator=(Core&&) = delete;

   private:
      void printRunTimeInformations();

      void tickApplication(Time deltaTime);
      void tickEngines(Time deltaTime);
      void capTickRate(Time loopTime);

   private:
      Application* m_app;
      std::set<Engine*> m_engines;

      bool m_initialised;

      EventBus m_eventBus;

      FileWriter m_coreWriter;
      Logger m_coreLogger;
      FileWriter m_appWriter;
      Logger m_appLogger;

      bool m_running;
      Chrono m_runTime;
      unsigned int m_tickRate;
   };
}

#include "Core.inl"

#endif // ZE_CORE_HPP

