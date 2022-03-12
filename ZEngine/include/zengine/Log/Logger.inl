#include "fmt/core.h"
template<typename Message>
inline ze::Logger& ze::Logger::log(Message message)
{
   logFormatted("{}", message);
   return *this;
}

template<typename Message>
inline ze::Logger& ze::Logger::log(Level level, Message message)
{
   logFormatted(level, "{}", message);
   return *this;
}

template<typename... Args>
inline ze::Logger& ze::Logger::logFormatted(fmt::format_string<Args...> fmt, Args&&... args)
{
   write(fmt, std::forward<Args>(args)...);
   return *this;
}

template<typename... Args>
inline ze::Logger& ze::Logger::logFormatted(Level level, fmt::format_string<Args...> fmt, Args&&... args)
{
   setLogLevel(level);
   write(fmt, std::forward<Args>(args)...);
   return *this;
}

template<typename... Args>
inline ze::Logger& ze::Logger::logLine(fmt::format_string<Args...> fmt, Args&&... args)
{
   write(fmt, std::forward<Args>(args)...);
   endLine();
   return *this;
}

template<typename... Args>
inline ze::Logger& ze::Logger::logLine(Level level, fmt::format_string<Args...> fmt, Args&&... args)
{
   setLogLevel(level);
   write(fmt, std::forward<Args>(args)...);
   endLine();
   return *this;
}

template<typename Message>
inline ze::Logger& ze::Logger::operator<<(Message message)
{
   log(std::forward<Message>(message));
   return *this;
}

template<typename... Args>
inline void ze::Logger::write(fmt::format_string<Args...> fmt, Args&&... args)
{
   if (!canLog()) return;

   char lineBuffer[MAX_LOGLINE_LENGTH + 1] = {}; // + Null-terminating character

   auto result = fmt::format_to_n(std::begin(lineBuffer), MAX_LOGLINE_LENGTH - 3, fmt, std::forward<Args>(args)...);
   
   // Pretty suspension points when actual line is larger than printed line
   if (result.size > MAX_LOGLINE_LENGTH)
   {
      lineBuffer[MAX_LOGLINE_LENGTH - 3] = '.';
      lineBuffer[MAX_LOGLINE_LENGTH - 2] = '.';
      lineBuffer[MAX_LOGLINE_LENGTH - 1] = '.';
      lineBuffer[MAX_LOGLINE_LENGTH - 0] = '\n';
   }

   write(std::string_view(lineBuffer, result.size > MAX_LOGLINE_LENGTH ? MAX_LOGLINE_LENGTH + 1 : result.size));
}

inline std::string ze::Logger::getName() const noexcept
{
   return m_name;
}

inline uint8_t ze::Logger::getLogMask() const noexcept
{
   return m_logMask;
}

inline ze::Logger::Level ze::Logger::getLogLevel() const noexcept
{
   return m_logLevel;
}

inline bool ze::Logger::canLog() const noexcept
{
   return (static_cast<unsigned int>(m_logLevel) & m_logMask) && m_writers.size();
}

