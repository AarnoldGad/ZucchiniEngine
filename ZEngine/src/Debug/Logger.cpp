#include "zepch.hpp"

#include "zengine/Debug/Logger.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{
   ze::Logger::Logger(std::string_view name, std::streambuf* output, bool outputToConsole, unsigned int logMask)
      : m_name{0}, m_output(output), m_outputToConsole(outputToConsole), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::INFO)
   {
      name.copy(m_name, std::min<size_t>(LOGGERNAME_MAXSIZE - 1, name.length()));
   }

   ze::Logger::Logger(std::string_view name, std::ostream& output, bool outputToConsole, unsigned int logMask)
      : m_name{0}, m_output(output.rdbuf()), m_outputToConsole(outputToConsole), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::INFO)
   {
      name.copy(m_name, std::min<size_t>(LOGGERNAME_MAXSIZE - 1, name.length()));
   }

   void ze::Logger::setOutput(std::ostream& output)
   {
      m_output.rdbuf(output.rdbuf());
   }

   void ze::Logger::setOutput(std::streambuf* output)
   {
      m_output.rdbuf(output);
   }

   void ze::Logger::setLogToConsole(bool logToConsole) noexcept
   {
      m_outputToConsole = logToConsole;
   }

   void ze::Logger::setLogMask(unsigned int mask) noexcept
   {
      m_logMask = mask;
   }

   ze::Logger& ze::Logger::operator<<(std::ostream& (*manip)(std::ostream&))
   {
      write(manip);
      return *this;
   }

   ze::Logger& ze::Logger::operator<<(Logger& (*manip)(Logger&))
   {
      return manip(*this);
   }

   ze::Logger& ze::Logger::info()
   {
      if (m_logLevel == Level::INFO)
         return *this;

      return startNewLineAs(Level::INFO);
   }

   ze::Logger& ze::Logger::info(Logger& logger)
   {
      return logger.info();
   }

   ze::Logger& ze::Logger::debug()
   {
      if (m_logLevel == Level::DEBUG)
         return *this;

      return startNewLineAs(Level::DEBUG);
   }

   ze::Logger& ze::Logger::debug(Logger& logger)
   {
      return logger.debug();
   }

   ze::Logger& ze::Logger::warn()
   {
      if (m_logLevel == Level::WARN)
         return *this;

      return startNewLineAs(Level::WARN);
   }

   ze::Logger& ze::Logger::warn(Logger& logger)
   {
      return logger.warn();
   }

   ze::Logger& ze::Logger::error()
   {
      if (m_logLevel == Level::ERR)
         return *this;

      return startNewLineAs(Level::ERR);
   }

   ze::Logger& ze::Logger::error(Logger& logger)
   {
      return logger.error();
   }

   ze::Logger& ze::Logger::critical()
   {
      if (m_logLevel == Level::CRITICAL)
         return *this;

      return startNewLineAs(Level::CRITICAL);
   }

   ze::Logger& ze::Logger::critical(Logger& logger)
   {
      return logger.critical();
   }

   ze::Logger& ze::Logger::newLine()
   {
      if (!m_lineStart)
      {
         *this << std::endl;
         m_lineStart = true;
      }

      return *this;
   }

   ze::Logger& ze::Logger::newLine(Logger& logger)
   {
      return logger.newLine();
   }

   void ze::Logger::printLineDetails()
   {
      if (m_lineStart)
      {
         Date date = Date::CurrentDate();

         if (canLog())
            m_output << "[" << std::put_time(&date.getTm(), "%H:%M:%S") << "] [" << levelToString(m_logLevel) << "] <" << m_name << "> ";

         if (canLogToConsole() && !isConsole())
            std::cout << "[" << std::put_time(&date.getTm(), "%H:%M:%S") << "] [" << levelToString(m_logLevel) << "] <" << m_name << "> ";

         m_lineStart = false;
      }
   }

   void ze::Logger::setConsoleColor() const
   {
      #if defined(ZE_BUILD_WINDOWS)
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(console, static_cast<unsigned short>(getCorrespondingTextColor()));
      #elif defined(ZE_BUILD_LINUX)
      unsigned short color = static_cast<unsigned short>(getCorrespondingTextColor());
      std::cout << "\033[" << (color >> 4) << ";" << (color & 0b1111) + 30 << "m";
      #endif
   }

   void ze::Logger::resetConsoleColor() const
   {
      #if defined(ZE_BUILD_WINDOWS)
      HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(console, static_cast<unsigned short>(TextColor::White));
      #elif defined(ZE_BUILD_LINUX)
      std::cout << "\033[0m";
      #endif
   }

   ze::Logger::TextColor ze::Logger::getCorrespondingTextColor() const noexcept
   {
      switch (m_logLevel)
      {
         case Level::INFO:
            return TextColor::White;
         case Level::DEBUG:
            return TextColor::LightGreen;
         case Level::WARN:
            return TextColor::LightYellow;
         case Level::ERR:
            return TextColor::Red;
         case Level::CRITICAL:
            return TextColor::LightRed;
         default:
            return TextColor::White;
      }
   }

   void ze::Logger::setLogLevel(Level logLevel) noexcept
   {
      m_logLevel = logLevel;
   }

   ze::Logger& ze::Logger::startNewLineAs(Level logLevel)
   {
      setLogLevel(logLevel);
      newLine();
      return *this;
   }

   char const* ze::Logger::levelToString(Level logLevel) noexcept
   {
      switch (logLevel)
      {
         case Level::INFO:
            return "Info";
         case Level::DEBUG:
            return "Debug";
         case Level::WARN:
            return "Warn";
         case Level::ERR:
            return "Error";
         case Level::CRITICAL:
            return "Critical";
         default:
            return "None";
      }
   }

   ze::Logger::~Logger()
   {
      newLine(); // Insert new line at end of stream
   }
}
