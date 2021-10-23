#include "zepch.hpp"

#include "zengine/Log/FileWriter.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{
   FileWriter::FileWriter(std::filesystem::path const& path)
      : m_path(path), m_lineStart(true)
   {
      // Empty potential existing file before use
      FILE* file = openFile("w+");

      if (file)
         fclose(file);
      else
         LOG_TRACE("Unable to initialise log file ", m_path, " : ", std::strerror(errno));
   }

   void FileWriter::write(std::string_view name, Logger::Level level, std::string_view line)
   {
      FILE* file = openFile("a");
      if (!file) return LOG_TRACE("Unable to open log file ", m_path, " : ", std::strerror(errno));

      if (isAtLineBegin())
      {
         printDate(file, name, level);

         m_lineStart = false;
      }

      fputs(line.data(), file);

      fclose(file);
   }

   void FileWriter::flush() {}

   void FileWriter::newLine()
   {
      FILE* file = openFile("a");
      if (!file) return LOG_TRACE("Unable to open log file ", m_path, " : ", std::strerror(errno));

      fputc('\n', file);
      fclose(file);

      m_lineStart = true;
   }

   [[nodiscard]]
   FILE* FileWriter::openFile(char const* mode)
   {
      FILE* file = fopen(m_path.string().c_str(), mode);

      return file;
   }

   void FileWriter::printDate(FILE* file, std::string_view name, Logger::Level level)
   {
      Date date = Date::CurrentDate();
      std::tm tm = date.getTm();
      char timeString[9];
      strftime(timeString, 9, "%H:%M:%S", &tm);
      fprintf(file, "[%s] [%s] <%s> ", timeString, Logger::LevelToString(level), name.data());
   }
}
