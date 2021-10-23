/**
 * Application.hpp
 * 15 Jul 2021
 * Ga�tan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Ga�tan Jalin
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
#ifndef ZE_APPLICATION_HPP
#define ZE_APPLICATION_HPP

#include "zengine/defines.hpp"

#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Time/Time.hpp"

namespace ze
{
   class ZE_API Application
   {
   public:
      std::string const& getName() const noexcept;

      virtual void onConnection() = 0;
      virtual void onDisconnection() = 0;

      virtual void tick(Time deltaTime) = 0;

      Application(std::string const& name);
      virtual ~Application() = default;

   protected:
      std::string m_name;
   };
}

#include "Application.inl"

#endif // ZE_APPLICATION_HPP
