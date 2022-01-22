ADD_LIBRARY(zengine SHARED)

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

# src/Backtrace
TARGET_SOURCES(zengine PRIVATE
               src/Backtrace/CallStack.cpp
               src/Backtrace/StackFrame.cpp
               )

# src/Common
TARGET_SOURCES(zengine PRIVATE
               src/Common/Arguments.cpp
               src/Common/System.cpp
               src/Common/Random.cpp
               )

# src/Core
TARGET_SOURCES(zengine PRIVATE
               src/Core/Core.cpp
               src/Core/Application.cpp
               )

# src/Event
TARGET_SOURCES(zengine PRIVATE
               src/Event/Event.cpp
               src/Event/EventBus.cpp
               src/Event/EventDispatcher.cpp
               )

# src/Exception
TARGET_SOURCES(zengine PRIVATE
               src/Exception/Exception.cpp
               )

# src/Layers
TARGET_SOURCES(zengine PRIVATE
               src/Layers/Layer.cpp
               )

 # src/Log
TARGET_SOURCES(zengine PRIVATE
               src/Log/Logger.cpp
               src/Log/FileWriter.cpp
               src/Log/DebugFileWriter.cpp
               src/Log/ConsoleWriter.cpp
               src/Log/ConsoleColors.cpp
               )

# src/Math
TARGET_SOURCES(zengine PRIVATE
               src/Math/Angle.cpp
               )

# src/Memory
TARGET_SOURCES(zengine PRIVATE
               src/Memory/New.cpp
               src/Memory/StandardAllocator.cpp
               )

# src/Module
TARGET_SOURCES(zengine PRIVATE
               src/Module/SharedObject.cpp
               )

# src/Time
TARGET_SOURCES(zengine PRIVATE
               src/Time/Chrono.cpp
               src/Time/Date.cpp
               src/Time/Time.cpp
               )

# src/Util
TARGET_SOURCES(zengine PRIVATE
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

