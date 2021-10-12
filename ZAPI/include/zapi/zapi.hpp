/**
 * zapi.hpp
 * 27 Nov 2020
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
#ifndef ZAPI_HPP
#define ZAPI_HPP

#include <zapi/defines.hpp>

// Core
//#include <zapi/Core/Core.hpp>
//#include <zapi/Core/Application.hpp>
//#include <zapi/Core/State.hpp>
//#include <zapi/Core/Engine.hpp>

// Logger
#include <zapi/Log/Logger.hpp>
#include <zapi/Log/Writer.hpp>
#include <zapi/Log/ConsoleColors.hpp>
#include <zapi/Log/ConsoleWriter.hpp>
#include <zapi/Log/FileWriter.hpp>
#include <zapi/Log/DebugFileWriter.hpp>

// Debug
//#include <zapi/Exception/Exception.hpp>
#include <zapi/Debug/Assert.hpp>
#include <zapi/Debug/Tee.hpp>
//#include <zapi/Memory/Memory.hpp>

// Event System
//#include <zapi/Event/Event.hpp>
//#include <zapi/Event/EventDispatcher.hpp>
//#include <zapi/Event/EventBus.hpp>
//#include <zapi/Event/EventSubscriber.hpp>
//#include <zapi/Signal/Signal.hpp>
//#include <zapi/Signal/Listener.hpp>

// Misc Managers
//#include <zapi/Resource/ResourceManager.hpp>
//#include <zapi/Memory/MemoryTracker.hpp>

// Time management
//#include <zapi/Time/Chrono.hpp>
//#include <zapi/Time/Date.hpp>
//#include <zapi/Time/Time.hpp>

// Math
#include <zapi/Math/RangedNumeric.hpp>
//#include <zapi/Math/Angle.hpp>

// Utility
#include <zapi/Backtrace/CallStack.hpp>
#include <zapi/Backtrace/StackFrame.hpp>
#include <zapi/Common/Functor.hpp>
#include <zapi/Common/Observer.hpp>
//#include <zapi/Common/Random.hpp>
//#include <zapi/Common/System.hpp>
#include <zapi/Module/SharedObject.hpp>
//#include <zapi/Util/StringUtils.hpp>
//#include <zapi/Util/FileUtils.hpp>

#endif // ZAPI_HPP
