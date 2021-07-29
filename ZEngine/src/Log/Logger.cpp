#include "zepch.hpp"

#include "zengine/Log/Logger.hpp"
#include "zengine/Time/Date.hpp"
#include "zengine/Log/Writer.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{

   Logger::Logger(std::string_view name, Writer* writer, unsigned int logMask)
      : m_name{0}, m_writer(writer), m_logMask(logMask), m_logLevel(Level::Info)
   {
      setName(name);
   }

   void Logger::setName(std::string_view name)
   {
      name.copy(m_name, std::min<size_t>(LOGGERNAME_MAXLENGTH, name.length()));
      // Make the name upper case
      for (size_t i = 0; i < LOGGERNAME_MAXLENGTH; ++i)
         m_name[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(m_name[i]))); // TODO String utils
   }

   void Logger::setWriter(Writer* writer) noexcept
   {
      m_writer = writer;
   }

   Logger& Logger::operator<<(Logger& (*manip)(Logger&))
   {
      return manip(*this);
   }

   Logger& Logger::info()
   {
      return getLogLevel() != Level::Info ? startNewLineAs(Level::Info) : *this;
   }

   Logger& Logger::info(Logger& logger)
   {
      return logger.info();
   }

   Logger& Logger::debug()
   {
      return getLogLevel() != Level::Debug ? startNewLineAs(Level::Debug) : *this;
   }

   Logger& Logger::debug(Logger& logger)
   {
      return logger.debug();
   }

   Logger& Logger::warn()
   {
      return getLogLevel() != Level::Warn ? startNewLineAs(Level::Warn) : *this;
   }

   Logger& Logger::warn(Logger& logger)
   {
      return logger.warn();
   }

   Logger& Logger::error()
   {
      return getLogLevel() != Level::Error ? startNewLineAs(Level::Error) : *this;
   }

   Logger& Logger::error(Logger& logger)
   {
      return logger.error();
   }

   Logger& Logger::critical()
   {
      return getLogLevel() != Level::Critical ? startNewLineAs(Level::Critical) : *this;
   }

   Logger& Logger::critical(Logger& logger)
   {
      return logger.critical();
   }

   Logger& Logger::newLine()
   {
      if (canLog())
      {
         getWriter()->newLine();
         getWriter()->flush();
      }

      return *this;
   }

   Logger& Logger::newLine(Logger& logger)
   {
      return logger.newLine();
   }

   void Logger::write(std::string_view message)
   {
      if (canLog())
         getWriter()->write(getName(), getLogLevel(), message);
   }

   Logger& Logger::stacktrace()
   {
      // TODO

      return *this;
   }

   Logger& Logger::stacktrace(Logger& logger)
   {
      return logger.stacktrace();
   }

   void Logger::setLogLevel(Level logLevel) noexcept
   {
      m_logLevel = logLevel;
   }

   void Logger::setLogMask(uint8_t mask) noexcept
   {
      m_logMask = mask;
   }

   Logger& Logger::startNewLineAs(Level logLevel)
   {
      setLogLevel(logLevel);

      return newLine();
   }

   char const* Logger::LevelToString(Level level) noexcept
   {
      switch (level)
      {
         case Level::Info:
            return "Info";
         case Level::Debug:
            return "Debug";
         case Level::Warn:
            return "Warn";
         case Level::Error:
            return "Error";
         case Level::Critical:
            return "Critical";
         default:
            return "None";
      }
   }
}
