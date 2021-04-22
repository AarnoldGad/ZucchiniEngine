/**
 * zengine.hpp
 * 27 Nov 2020
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
#ifndef ZENGINE
#define ZENGINE

#include <zemacros.hpp>

// Abstract design
#include <zengine/Abstract/Singleton.hpp>

// Core
#include <zengine/Core/Core.hpp>
#include <zengine/Core/State.hpp>

// Debug
#include <zengine/Debug/Assert.hpp>
#include <zengine/Debug/Logger.hpp>
#include <zengine/Debug/Tee.hpp>

// Event System
#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventHandler.hpp>
#include <zengine/Event/EventDispatcher.hpp>
#include <zengine/Event/EventBus.hpp>
#include <zengine/Event/Subscriber.hpp>
#include <zengine/Signal/Signal.hpp>
#include <zengine/Signal/Connection.hpp>

// Misc Managers
#include <zengine/Resource/ResourceManager.hpp>

// Time management
#include <zengine/Time/Chrono.hpp>
#include <zengine/Time/Date.hpp>
#include <zengine/Time/Time.hpp>

// Math
#include <zengine/Math/RangedNumeric.hpp>

// Utility
#include <zengine/Common/Random.hpp>
#include <zengine/Common/System.hpp>
#include <zengine/Common/TypeTraits.hpp>
#include <zengine/Util/StringUtils.hpp>

#endif // ZENGINE