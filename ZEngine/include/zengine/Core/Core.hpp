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
#ifndef ZE_CORE_HPP
#define ZE_CORE_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Core/Application.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/FileWriter.hpp"
#include "zengine/Event/EventBus.hpp"
#include "zengine/Event/Subscriber.hpp"
#include "zengine/Time/Chrono.hpp"
#include "zengine/Core/Engine.hpp"

#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace ze
{
   class ZE_API Core final
   {
   public:
      static void Initialise();

      static void ConnectEngine(Engine& engine);
      static void DisconnectEngine(Engine& engine);

      static void PlaceApplication(Application* app);
      static Application* GetApplication() noexcept;

      static void Run();
      static bool IsRunning() noexcept;
      static void Stop() noexcept;

      static Logger& UseCoreLogger() noexcept;

      static void SetTickRate(unsigned int rate) noexcept;

      static Time GetRunTime() noexcept;
      static unsigned int GetTickRate() noexcept;

      static void Terminate();

   private:
      Core() = delete;
      Core(Core const&) = delete;
      Core(Core&&) = delete;
      Core& operator=(Core const&) = delete;
      Core& operator=(Core&&) = delete;
      ~Core() = delete;

      static void MainLoop();

      static void TickApplication(Time deltaTime);
      static void TickEngines(Time deltaTime);
      static void CapTickRate(Time loopTime);

      static bool IsInitialised() noexcept;
      static void SetInitialised(bool value = true) noexcept;

      static bool s_initialised;

      static DebugFileWriter s_coreWriter;
      static Logger s_coreLogger;

      static bool s_running;
      static Chrono s_runTime; // Run from Initialisation to Termination
      static unsigned int s_tickRate;

      static Application* s_app;
      static std::set<Engine*> s_engines;
   };
}

#include "Core.inl"

#endif // ZE_CORE_HPP
