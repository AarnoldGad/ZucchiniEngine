ADD_LIBRARY(zengine)

IF(WIN32)
	SET(BUILD_SHARED_LIBS OFF)
ELSE()
	SET(BUILD_SHARED_LIBS ON)
ENDIF()

# Properties
SET_TARGET_PROPERTIES(zengine PROPERTIES
                      OUTPUT_NAME zengine
                      VERSION ${ZucchiniEngine_VERSION_MAJOR}.${ZucchiniEngine_VERSION_MINOR}.${ZucchiniEngine_VERSION_PATCH}
                      SOVERSION ${ZucchiniEngine_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "ZEngine"
                      )

# Precompiled Header
TARGET_PRECOMPILE_HEADERS(zengine PRIVATE
                          "$<$<COMPILE_LANGUAGE:CXX>:zepch.hpp>"
                          )

# include
TARGET_SOURCES(zengine PRIVATE
               include/zepch.hpp
               include/zengine/defines.hpp
               include/zengine/platform.hpp
               include/zengine/zengine.hpp
               )

# src/Backtrace
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Backtrace/CallStack.hpp
               include/zengine/Backtrace/CallStack.inl
               include/zengine/Backtrace/StackFrame.hpp
               include/zengine/Backtrace/StackFrame.inl
               src/Backtrace/CallStack.cpp
               src/Backtrace/StackFrame.cpp
               )

# src/Common
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Common/Arguments.hpp
               include/zengine/Common/Console.hpp
               include/zengine/Common/Console.inl
               include/zengine/Common/Functor.hpp
               include/zengine/Common/Observer.hpp
               include/zengine/Common/Priority.hpp
               include/zengine/Common/Random.hpp
               include/zengine/Common/System.hpp
               src/Common/Arguments.cpp
               src/Common/Console.cpp
               src/Common/System.cpp
               src/Common/Random.cpp
               )

# src/Core
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Core/Application.hpp
               include/zengine/Core/Application.inl
               include/zengine/Core/Core.hpp
               include/zengine/Core/Core.inl
               include/zengine/Core/Engine.hpp
               src/Core/Core.cpp
               src/Core/Application.cpp
               )

# include/zengine/Debug
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Debug/Assert.hpp
               include/zengine/Debug/Assert.inl
               include/zengine/Debug/Tee.hpp
               include/zengine/Debug/Tee.inl
               )

# src/Event
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Event/Event.hpp
               include/zengine/Event/Event.inl
               include/zengine/Event/EventBus.hpp
               include/zengine/Event/EventBus.inl
               include/zengine/Event/EventDispatcher.hpp
               include/zengine/Event/EventDispatcher.inl
               include/zengine/Event/EventSubscriber.hpp
               include/zengine/Event/EventSubscriber.inl
               src/Event/Event.cpp
               src/Event/EventBus.cpp
               src/Event/EventDispatcher.cpp
               )

# src/Exception
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Exception/Exception.hpp
               include/zengine/Exception/Exception.inl
               src/Exception/Exception.cpp
               )

# src/Layers
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Layer/Layer.hpp
               include/zengine/Layer/Layer.inl
               src/Layer/Layer.cpp
               )

 # src/Log
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Log/Logger.hpp
               include/zengine/Log/Logger.inl
               include/zengine/Log/ConsoleWriter.hpp
               include/zengine/Log/ConsoleWriter.inl
               include/zengine/Log/Writer.hpp
               src/Log/Logger.cpp
               src/Log/ConsoleWriter.cpp
               )

# src/Math
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Math/Angle.hpp
               include/zengine/Math/Angle.inl
               include/zengine/Math/RangedNumeric.hpp
               include/zengine/Math/RangedNumeric.inl
               src/Math/Angle.cpp
               )

# src/Memory
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Memory/Allocator.hpp
               include/zengine/Memory/New.hpp
               include/zengine/Memory/New.inl
               include/zengine/Memory/StandardAllocator.hpp
               include/zengine/Memory/StandardAllocator.inl
               src/Memory/New.cpp
               src/Memory/StandardAllocator.cpp
               )

# src/Module
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Module/SharedObject.hpp
               include/zengine/Module/SharedObject.inl
               src/Module/SharedObject.cpp
               )

# include/zengine/Resource
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Resource/ResourceManager.hpp
               include/zengine/Resource/ResourceManager.inl
               )

# include/zengine/Signal
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Signal/Listener.hpp
               include/zengine/Signal/Listener.inl
               include/zengine/Signal/Signal.hpp
               include/zengine/Signal/Signal.inl
               )

# src/Time
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Time/Chrono.hpp
               include/zengine/Time/Chrono.inl
               include/zengine/Time/Date.hpp
               include/zengine/Time/Date.inl
               include/zengine/Time/Time.hpp
               include/zengine/Time/Time.inl
               src/Time/Chrono.cpp
               src/Time/Date.cpp
               src/Time/Time.cpp
               )

# src/Util
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Util/FileUtils.hpp
               include/zengine/Util/StringUtils.hpp
               include/zengine/Util/StringUtils.inl
               src/Util/FileUtils.cpp
               src/defines.cpp
               )

# Defines
TARGET_COMPILE_DEFINITIONS(zengine PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

# Include Dirs
TARGET_INCLUDE_DIRECTORIES(zengine PUBLIC
                           "${PROJECT_SOURCE_DIR}/ZEngine/include"
                           "${PROJECT_SOURCE_DIR}/ZEngine/deps/fmt/include"
                           "${PROJECT_BINARY_DIR}"
                           )

# System Include Dirs
TARGET_INCLUDE_DIRECTORIES(zengine SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

# System Lib Dirs
TARGET_LINK_DIRECTORIES(zengine PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

# Linking
TARGET_LINK_LIBRARIES(zengine PRIVATE
                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      $<$<PLATFORM_ID:Windows>:version>
                      )

