#include "zepch.hpp"

#include "zengine/Log/FileWriter.hpp"
#include "zengine/Time/Date.hpp"

#include <array>

#include "zengine/Memory/New.hpp"

namespace ze
{
   FileWriter::FileWriter(std::filesystem::path const& path)
      : m_path(path), m_lineStart(true)
   {
      // Empty potential existing file before use
      FILE* file = std::fopen(m_path.c_str(), "w+");

      // TODO Error handling

      std::fclose(file);
   }

   void FileWriter::write(std::string_view name, Level level, std::string_view line)
   {
      // C Style file opening for performance
      FILE* file = std::fopen(m_path.c_str(), "a");

      if (isAtLineBegin())
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         char timeString[9];
         std::strftime(timeString, 9, "%H:%M:%S", &tm);
         std::fprintf(file, "[%s] [%s] <%s>", timeString, LevelToString(level), name.data());

         m_lineStart = false;
      }

      std::fputs(line.data(), file);

      std::fclose(file);
   }

   void FileWriter::flush()
   {
      m_lineStart = true;
   }
}
