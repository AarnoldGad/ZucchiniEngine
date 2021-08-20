/**
 * DebugFileWriter.hpp
 * 28 Apr 2021
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
#ifndef ZE_DEBUGFILEWRITER_HPP
#define ZE_DEBUGFILEWRITER_HPP

#include "zengine/zemacros.hpp"

#include "zengine/Log/FileWriter.hpp"
#include "zengine/Log/ConsoleWriter.hpp"

namespace ze
{
   // TODO Rework design to avoid this kind of class combination
   class ZE_API DebugFileWriter : public FileWriter, public ConsoleWriter
   {
   public:
      void write(std::string_view name, Logger::Level level, std::string_view line) override;
      void flush() override;
      void newLine() override;

      DebugFileWriter(std::string_view path);
   };
}

#endif // ZE_DEBUGFILEWRITER_HPP
