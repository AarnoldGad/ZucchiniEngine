#include "zepch.hpp"

#include "zengine/Backtrace/CallStack.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Log/Writer.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{

   Logger::Logger(std::string const& name, Writer* writer, uint8_t logMask)
      : m_name{}, m_writer(writer), m_logMask(logMask), m_logLevel(Level::Info), m_lineStart(true)
   {
      setName(name);
   }

   void Logger::setName(std::string const& name)
   {
      m_name = name;
      std::transform(m_name.begin(), m_name.end(), m_name.begin(),
                     [](unsigned char c) { return std::toupper(c); });
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
      return getLogLevel() != Level::Info && !m_lineStart ? startNewLineAs(Level::Info) : *this;
   }

   Logger& Logger::info(Logger& logger)
   {
      return logger.info();
   }

   Logger& Logger::debug()
   {
      return getLogLevel() != Level::Debug && !m_lineStart ? startNewLineAs(Level::Debug) : *this;
   }

   Logger& Logger::debug(Logger& logger)
   {
      return logger.debug();
   }

   Logger& Logger::warn()
   {
      return getLogLevel() != Level::Warn && !m_lineStart ? startNewLineAs(Level::Warn) : *this;
   }

   Logger& Logger::warn(Logger& logger)
   {
      return logger.warn();
   }

   Logger& Logger::error()
   {
      return getLogLevel() != Level::Error && !m_lineStart ? startNewLineAs(Level::Error) : *this;
   }

   Logger& Logger::error(Logger& logger)
   {
      return logger.error();
   }

   Logger& Logger::critical()
   {
      return getLogLevel() != Level::Critical && !m_lineStart ? startNewLineAs(Level::Critical) : *this;
   }

   Logger& Logger::critical(Logger& logger)
   {
      return logger.critical();
   }

   Logger& Logger::newLine()
   {
      if (canLog())
      {
         m_lineStart = true;
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
      {
         // TODO Treat \n and \r as newLine()
         m_lineStart = false;
         getWriter()->write(getName(), getLogLevel(), message);
      }
   }

   Logger& Logger::stacktrace()
   {
      CallStack stack = Stacktrace(32, 1);
      for (size_t i = 0; i < stack.getSize(); ++i)
         logLine("\t%s", stack[i].toString().c_str());

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
