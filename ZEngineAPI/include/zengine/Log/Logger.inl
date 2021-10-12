template<typename Message>
inline void ze::Logger::log(Message&& message)
{
   log(getLogLevel(), std::forward<Message>(message));
}

template<typename Message, typename std::enable_if_t<std::is_arithmetic_v<Message>, int> >
inline void ze::Logger::log(Level logLevel, Message message)
{
   std::stringstream ss;
   ss << message;
   log(logLevel, ss.str());
}

template<typename Message, typename std::enable_if_t<std::is_convertible_v<Message, std::string_view>, int> >
inline void ze::Logger::log(Level logLevel, Message message)
{
   setLogLevel(logLevel);
   write(std::string_view(message));
}

template<typename... Args>
inline void ze::Logger::logLine(std::string_view format, Args&&... args)
{
   logLine(getLogLevel(), format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void ze::Logger::logLine(Level logLevel, std::string_view format, Args&&... args)
{
   setLogLevel(logLevel);
   write(format, std::forward<Args>(args)...);
   newLine();
}

template<typename Message>
inline ze::Logger& ze::Logger::operator<<(Message&& message)
{
   log(std::forward<Message>(message));
   return *this;
}

template<typename... Args>
inline void ze::Logger::write(std::string_view format, Args&&... args)
{
   int lineSize = std::snprintf(nullptr, 0, format.data(), std::forward<Args>(args)...);
   std::string line;
   line.reserve(static_cast<size_t>(lineSize) + 1);
   
   int written = std::snprintf(line.data(), line.capacity(), format.data(), std::forward<Args>(args)...);
   if (written < 0)
      return LOG_TRACE("An error occured whilst logging");

   write(std::string_view(line.data(), static_cast<size_t>(written)));
}

inline bool ze::Logger::canLog() const noexcept
{
   return (static_cast<unsigned int>(m_logLevel) & m_logMask) && m_writer;
}

inline std::string ze::Logger::getName() const noexcept
{
   return m_name;
}

inline ze::Writer* ze::Logger::getWriter() noexcept
{
   return m_writer;
}

inline uint8_t ze::Logger::getLogMask() const noexcept
{
   return m_logMask;
}

inline ze::Logger::Level ze::Logger::getLogLevel() const noexcept
{
   return m_logLevel;
}
