#include "zepch.hpp"

#include "zengine/Backtrace/CallStack.hpp"
#include "zengine/Log/Logger.hpp"
#include "zengine/Log/Writer.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{
   Logger::Logger(std::string const& name, uint8_t logMask)
      : m_name{}, m_logMask(logMask), m_logLevel(Level::Info)
   {
      setName(name);
   }

   Logger::Logger(std::string const& name, Writer* writer, uint8_t logMask)
      : Logger(name, {writer}, logMask) {}

   Logger::Logger(std::string const& name, std::initializer_list<Writer*> writers, uint8_t logMask)
      : m_name{}, m_writers(writers.begin(), writers.end()), m_logMask(logMask), m_logLevel(Level::Info)
   {
      setName(name);
   }

   void Logger::setName(std::string const& name)
   {
      m_name = name;
      // Uppercase name
      std::transform(m_name.begin(), m_name.end(), m_name.begin(),
                     [](unsigned char c) { return std::toupper(c); });
   }

   void Logger::addWriter(Writer* writer)
   {
      if (!writer) return;

      auto writerExists = (std::find(m_writers.begin(), m_writers.end(), writer) != m_writers.end());
      if (!writerExists)
         m_writers.push_back(writer);
   }

   void Logger::removeWriter(Writer* writer)
   {
      if (!writer) return;

      auto writerFound = std::find(m_writers.begin(), m_writers.end(), writer);
      if (writerFound != m_writers.end())
         m_writers.erase(writerFound);
   }

   void Logger::removeWriters()
   {
      m_writers.clear();
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
      return getLogLevel() != Level::Warning ? startNewLineAs(Level::Warning) : *this;
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

   Logger& Logger::endLine()
   {
      if (canLog())
      {
         for (auto& writer : m_writers)
            writer->endLine();
      }
 
      return *this;
   }

   Logger& Logger::endLine(Logger& logger)
   {
      return logger.endLine();
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

   void Logger::write(std::string_view line)
   {
      for (auto& writer : m_writers)
         writer->write(getName(), Date::CurrentDate(), getLogLevel(), line);
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
      return endLine();
   }

   char const* Logger::LevelToString(Logger::Level level) noexcept
   {
      switch (level)
      {
         case Logger::Level::Info:
            return "Info";
         case Logger::Level::Debug:
            return "Debug";
         case Logger::Level::Warning:
            return "Warn";
         case Logger::Level::Error:
            return "Error";
         case Logger::Level::Critical:
            return "Critical";
         default:
            return "None";
      }
   }

   Console::Color Logger::GetLevelColor(Logger::Level level) noexcept
   {
      switch (level)
      {
         case Logger::Level::Info:
            return Console::Color::White;
         case Logger::Level::Debug:
            return Console::Color::Aqua;
         case Logger::Level::Warning:
            return Console::Color::Yellow;
         case Logger::Level::Error:
            return Console::Color::Red;
         case Logger::Level::Critical:
            return Console::Color::LightRed;
         default:
            return Console::Color::White;
      }
   }
}

