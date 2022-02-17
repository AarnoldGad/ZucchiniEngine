#include "zepch.hpp"

#include "zengine/Log/StreamWriter.hpp"

#include "zengine/Stream/OutputStream.hpp"

#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>

namespace ze
{
   StreamWriter::StreamWriter(OutputStream* stream)
      : m_stream(stream), m_atLineStart(true) {}

   void StreamWriter::setStream(OutputStream* stream)
   {
      m_stream = stream;
   }

   void StreamWriter::write(std::string_view name, Date date, Logger::Level level, std::string_view message)
   {
      if (!m_stream) return;

      if (m_atLineStart)
      {
         char dateBuffer[9] = {};
         fmt::format_to_n(std::begin(dateBuffer), 8, "{:%H:%M:%S}", date.getTm());
         (*m_stream) << "[" << dateBuffer << "] [" << Logger::LevelToString(level) << "] <" << name << "> ";
         m_atLineStart = false;
      }

      m_stream->write(message);
   }

   void StreamWriter::flush()
   {
      if (!m_stream) return;

      m_stream->flush();
   }

   void StreamWriter::endLine()
   {
      if (!m_stream || m_atLineStart) return;

      m_stream->put('\n');
      m_stream->flush();

      m_atLineStart = true;
   }
}

