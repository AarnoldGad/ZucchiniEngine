#include "zengine/Memory/New.hpp"

template<typename Message, typename std::enable_if_t<std::is_convertible_v<Message, std::string_view>, int> >
void ze::Logger::log(Message message)
{
   log(getLogLevel(), std::string_view(message));
}

template<typename Message, typename std::enable_if_t<std::is_arithmetic_v<Message>, int>>
void ze::Logger::log(Message message)
{
   // Cast arithmetic type to char array to avoid heap allocation
   std::array<char, 25> buf{0};
   auto [end, err] = std::to_chars(buf.data(), buf.data() + buf.size(), message);

   log(getLogLevel(), std::string_view(buf.data(), end - buf.data()));
}

template<typename Message>
void ze::Logger::log(Level logLevel, Message&& message)
{
   setLogLevel(logLevel);
   write(std::forward<Message>(message));
}

template<typename... Args>
void ze::Logger::logLine(std::string_view format, Args&&... args)
{
   logLine(getLogLevel(), format, std::forward<Args>(args)...);
}

template<typename... Args>
void ze::Logger::logLine(Level logLevel, std::string_view format, Args&&... args)
{
   startNewLineAs(logLevel);
   write(format, std::forward<Args>(args)...);
}

template<typename Message>
ze::Logger& ze::Logger::operator<<(Message&& message)
{
   log(std::forward<Message>(message));
   return *this;
}

template<typename... Args>
void ze::Logger::write(std::string_view format, Args&&... args)
{
   std::array<char, LOGGERLINE_MAXLENGTH> line{0};
   int written = std::snprintf(line.data(), line.size(), format.data(), std::forward<Args>(args)...);
   if (written < 0)
   {
      LOG_TRACE("An error occured whilst logging");
      return; // TODO Error handling
   }
   else if (static_cast<size_t>(written) >= line.size())
      LOG_TRACE("Warning : Insufficient buffer size"); // TODO Too

   write(std::string_view(line.data(), written));
}

inline bool ze::Logger::canLog() const noexcept
{
   return (static_cast<unsigned int>(getLogLevel()) & getLogMask()) && getWriter();
}

inline char const* ze::Logger::getName() const noexcept
{
   return m_name;
}

inline ze::Writer* ze::Logger::getWriter() const noexcept
{
   return m_writer;
}

inline unsigned int ze::Logger::getLogMask() const noexcept
{
   return m_logMask;
}

inline ze::Level ze::Logger::getLogLevel() const noexcept
{
   return m_logLevel;
}

#include "zengine/Memory/NewOff.hpp"
