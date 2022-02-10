template<typename Message>
inline void ze::Logger::log(Message message)
{
   logFormatted("{}", message);
}

template<typename Message>
inline void ze::Logger::log(Level level, Message message)
{
   logFormatted(level, "{}", message);
}

template<typename... Args>
inline void ze::Logger::logFormatted(std::string const& fmt, Args&&... args)
{
   write(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void ze::Logger::logFormatted(Level level, std::string const& fmt, Args&&... args)
{
   setLogLevel(level);
   write(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void ze::Logger::logLine(std::string const& fmt, Args&&... args)
{
   write(fmt, std::forward<Args>(args)...);
   endLine();
}

template<typename... Args>
inline void ze::Logger::logLine(Level level, std::string const& fmt, Args&&... args)
{
   setLogLevel(level);
   write(fmt, std::forward<Args>(args)...);
   endLine();
}

template<typename Message>
inline ze::Logger& ze::Logger::operator<<(Message message)
{
   log(std::forward<Message>(message));
   return *this;
}

template<typename... Args>
inline void ze::Logger::write(std::string_view fmt, Args&&... args)
{
   if (!canLog()) return;

   char lineBuffer[MAX_LOGLINE_LENGTH + 1] = {}; // + Null-terminating character

   auto result = fmt::format_to_n(&lineBuffer, MAX_LOGLINE_LENGTH - 3, fmt, std::forward<Args>(args)...);
   
   // Pretty suspension points when actual line is larger than printed line
   if (result.size > MAX_LOGLINE_LENGTH)
   {
      lineBuffer[MAX_LOGLINE_LENGTH - 2] = '.';
      lineBuffer[MAX_LOGLINE_LENGTH - 1] = '.';
      lineBuffer[MAX_LOGLINE_LENGTH - 0] = '.';
   }

   for (auto& writer : m_writers)
      writer->write(getName(), Date::CurrentDate(), getLogLevel(), std::string_view(lineBuffer, MAX_LOGLINE_LENGTH));
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

