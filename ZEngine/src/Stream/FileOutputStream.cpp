#include "zepch.hpp"

#include "zengine/Stream/FileOutputStream.hpp"

#include "zengine/Common/Console.hpp"

namespace ze
{
   FileOutputStream::FileOutputStream(std::filesystem::path const& file, std::ios_base::openmode mode)
   {
      open(file, mode);
   }

   void FileOutputStream::open(std::filesystem::path const& file, std::ios_base::openmode mode)
   {
      m_file.open(file, mode);

      if (!m_file)
         Console::Trace("Failed to open file stream {} !", file);
   }

   void FileOutputStream::close()
   {
      m_file.close();
   }

   OutputStream& FileOutputStream::put(char ch)
   {
      m_file.put(ch);
      return *this;
   }

   OutputStream& FileOutputStream::write(std::string_view str)
   {
      m_file.write(str.data(), str.size());
      return *this;
   }

   OutputStream& FileOutputStream::operator<<(std::string_view str)
   {
      write(str);
      return *this;
   }

   OutputStream& FileOutputStream::flush()
   {
      m_file.flush();
      return *this;
   }

   ptrdiff_t FileOutputStream::tellp()
   {
      return m_file.tellp();
   }

   OutputStream& FileOutputStream::seekp(ptrdiff_t pos)
   {
      m_file.seekp(pos);

      return *this;
   }
}
