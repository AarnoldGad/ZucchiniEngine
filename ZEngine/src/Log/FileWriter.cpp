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
      FILE* file = openFile("w+");

      if (file)
         fclose(file);
      // TODO Error handling
   }

   void FileWriter::write(std::string_view name, Level level, std::string_view line)
   {
      FILE* file = openFile("a");

      if (!file) return;
      // TODO Error handling

      if (isAtLineBegin())
      {
         Date date = Date::CurrentDate();
         std::tm tm = date.getTm();
         char timeString[9];
         strftime(timeString, 9, "%H:%M:%S", &tm);
         fprintf(file, "[%s] [%s] <%s> ", timeString, LevelToString(level), name.data());

         m_lineStart = false;
      }

      fputs(line.data(), file);

      fclose(file);
   }

   void FileWriter::flush() {}

   void FileWriter::newLine()
   {
      FILE* file = openFile("a");

      if (!file) return;

      fputc('\n', file);
      fclose(file);

      m_lineStart = true;
   }

   [[nodiscard("File should be closed")]]
   FILE* FileWriter::openFile(char const* mode)
   {
      // C Style file opening for performance
      FILE* file;
      fopen_s(&file, m_path.string().c_str(), mode);

      return file;
   }
}
