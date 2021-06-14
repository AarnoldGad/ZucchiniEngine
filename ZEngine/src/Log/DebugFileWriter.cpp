#include "zepch.hpp"

#include "zengine/Log/DebugFileWriter.hpp"
#include "zengine/Log/ConsoleColors.hpp"
#include "zengine/Time/Date.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   DebugFileWriter::DebugFileWriter(std::string_view path, std::ostream& console)
      : FileWriter(path), ConsoleWriter(console) {}

   void DebugFileWriter::write(std::string_view name, Level level, std::string_view line)
   {
      FileWriter::write(name, level, line);
      ConsoleWriter::write(name, level, line);
   }

   void DebugFileWriter::flush()
   {
      FileWriter::flush();
      ConsoleWriter::flush();
   }

   void DebugFileWriter::newLine()
   {
      FileWriter::newLine();
      ConsoleWriter::newLine();
   }
}
