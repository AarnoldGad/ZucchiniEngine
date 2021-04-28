#include "zepch.hpp"

#include "zengine/Log/FileWriter.hpp"
#include "zengine/Time/Date.hpp"

#include <array>

#include "zengine/Memory/New.hpp"

namespace ze
{
   FileWriter::FileWriter(std::filesystem::path const& path)
      : m_path(path), m_lineStart(true) {}

   void FileWriter::write(std::string_view name, Level level, std::string_view line)
   {
      std::ofstream file;
      file.open(m_path, std::ios::out | std::ios::app);

      if (m_lineStart)
      {
         Date date = Date::CurrentDate();
         file << "[" << std::put_time(&date.getTm(), "%H:%M:%S") << "] [" << LevelToString(level) << "] <" << name << "> ";
         m_lineStart = false;
      }

      file << line;
   }

   void FileWriter::flush()
   {
      m_lineStart = true;
   }

   void FileWriter::setFilePath(std::filesystem::path const& path) noexcept
   {
      m_path = path;
   }
}