IF(WIN32)
   SET(BUILD_SHARED_LIBS OFF)
ELSE()
   SET(BUILD_SHARED_LIBS ON)
ENDIF()

ADD_LIBRARY(zengine)

# Properties
SET_TARGET_PROPERTIES(zengine PROPERTIES
                      OUTPUT_NAME zengine
                      VERSION ${ZucchiniEngine_VERSION_MAJOR}.${ZucchiniEngine_VERSION_MINOR}.${ZucchiniEngine_VERSION_PATCH}
                      SOVERSION ${ZucchiniEngine_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "ZEngine"
                      )

SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/zengine")
SET(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

# Precompiled Header
TARGET_PRECOMPILE_HEADERS(zengine PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:zepch.hpp>")

# Defines
TARGET_COMPILE_DEFINITIONS(zengine PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

# Include Dirs
TARGET_INCLUDE_DIRECTORIES(zengine PUBLIC
                           ${INCLUDE_DIR}
                           "${DEPS_DIR}/ZucchiniLib/Zucchini/include"
                           "${PROJECT_BINARY_DIR}"
                           )

# System Include Dirs
TARGET_INCLUDE_DIRECTORIES(zengine SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

# include
TARGET_SOURCES(zengine PRIVATE
               include/zepch.hpp
               include/zengine/defines.hpp
               include/zengine/platform.hpp
               include/zengine/zengine.hpp
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

# src/Layers
TARGET_SOURCES(zengine PRIVATE
               include/zengine/Layer/Layer.hpp
               include/zengine/Layer/Layer.inl
               src/Layer/Layer.cpp
               )

# System Lib Dirs
TARGET_LINK_DIRECTORIES(zengine PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

# Linking
TARGET_LINK_LIBRARIES(zengine PRIVATE
                      zucchini
                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      $<$<PLATFORM_ID:Windows>:version>
                      )

