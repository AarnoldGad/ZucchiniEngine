ADD_LIBRARY(zengine SHARED)

TARGET_PRECOMPILE_HEADERS(zengine PRIVATE
                          "$<$<COMPILE_LANGUAGE:CXX>:zepch.hpp>"
                          )

# Precompiled Header Source
TARGET_SOURCES(zengine PRIVATE
               include/zepch.cpp
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

# Properties
SET_TARGET_PROPERTIES(zengine PROPERTIES
                      OUTPUT_NAME zengine
                      POSITION_INDEPENDENT_CODE True
                      )

# Defines
ADD_COMPILE_DEFINITIONS($<$<CONFIG:Debug>:_DEBUG> $<$<CONFIG:Release>:NDEBUG>)

# Include Dirs
TARGET_INCLUDE_DIRECTORIES(zengine
                           PUBLIC "${PROJECT_SOURCE_DIR}/ZEngine/include" "${PROJECT_BINARY_DIR}"
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
TARGET_LINK_LIBRARIES(zengine
                      -ldl
                      $<$<PLATFORM_ID:Windows>:version>
                      $<$<PLATFORM_ID:Linux>:pthread>
                      )

