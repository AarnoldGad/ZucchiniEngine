#include "zepch.hpp"

#include "zapi/Log/DebugFileWriter.hpp"
#include "zapi/Log/ConsoleColors.hpp"
#include "zapi/Time/Date.hpp"

namespace ze
{
   DebugFileWriter::DebugFileWriter(std::string_view path)
      : FileWriter(path) {}

   void DebugFileWriter::write(std::string_view name, Logger::Level level, std::string_view line)
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
