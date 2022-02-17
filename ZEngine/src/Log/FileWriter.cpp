#include "zepch.hpp"

#include "zengine/Log/FileWriter.hpp"

namespace ze
{
   FileWriter::FileWriter(std::filesystem::path const& filepath)
      : m_filepath(filepath)
   {
      setStream(&m_file);

      // Clear any existent file
      m_file.open(m_filepath, std::ios_base::out | std::ios_base::trunc);
      m_file.close();
   }

   void FileWriter::write(std::string_view name, Date date, Logger::Level level, std::string_view message)
   {
      m_file.open(m_filepath, std::ios_base::app);

      StreamWriter::write(name, date, level, message);
      
      m_file.close();
   }

   void FileWriter::flush()
   {
      StreamWriter::flush();
   }

   void FileWriter::endLine()
   {
      m_file.open(m_filepath, std::ios_base::app);
      
      StreamWriter::endLine();

      m_file.close();
   }
}

