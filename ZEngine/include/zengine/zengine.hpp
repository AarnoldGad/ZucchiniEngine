/**
 * zengine.hpp
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
#ifndef ZENGINE_HPP
#define ZENGINE_HPP

#include <zengine/zemacros.hpp>

// Core
#include <zengine/Core/Core.hpp>
#include <zengine/Core/Application.hpp>
#include <zengine/Core/State.hpp>
#include <zengine/Core/Engine.hpp>

// Logger
#include <zengine/Log/Logger.hpp>
#include <zengine/Log/Writer.hpp>
#include <zengine/Log/ConsoleColors.hpp>
#include <zengine/Log/ConsoleWriter.hpp>
#include <zengine/Log/FileWriter.hpp>
#include <zengine/Log/DebugFileWriter.hpp>

// Debug
//#include <zengine/Exception/Exception.hpp>
#include <zengine/Debug/Assert.hpp>
#include <zengine/Debug/Tee.hpp>
#include <zengine/Memory/Memory.hpp>

// Event System
#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventDispatcher.hpp>
#include <zengine/Event/EventBus.hpp>
#include <zengine/Event/EventSubscriber.hpp>
#include <zengine/Signal/Signal.hpp>
#include <zengine/Signal/Listener.hpp>

// Misc Managers
#include <zengine/Resource/ResourceManager.hpp>
#include <zengine/Memory/MemoryTracker.hpp>

// Time management
#include <zengine/Time/Chrono.hpp>
#include <zengine/Time/Date.hpp>
#include <zengine/Time/Time.hpp>

// Math
#include <zengine/Math/RangedNumeric.hpp>

// Utility
#include <zengine/Common/Backtrace/CallStack.hpp>
#include <zengine/Common/Backtrace/StackFrame.hpp>
#include <zengine/Common/Functor.hpp>
#include <zengine/Common/Observer.hpp>
#include <zengine/Common/Random.hpp>
#include <zengine/Common/System.hpp>
#include <zengine/Common/TypeTraits.hpp>
#include <zengine/Util/StringUtils.hpp>

#endif // ZENGINE_HPP
