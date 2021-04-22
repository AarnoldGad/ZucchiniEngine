template<typename Message>
void ze::Logger::log(Level logLevel, Message const& message)
{
   setLogLevel(logLevel);
   write(message);
}

template<typename... Messages>
void ze::Logger::logLine(Level logLevel, Messages&&... messages)
{
   startNewLineAs(logLevel);
   write(std::forward<Messages>(messages)...);
}

template<typename... Args>
void ze::Logger::logFormatedLine(Level logLevel, std::string const& unformattedLine, Args&&... args)
{
   logLine(logLevel, formatLine(unformattedLine, std::forward<Args>(args)...));
}

inline std::string ze::Logger::getName() const noexcept
{
   return m_name;
}

inline std::ostream& ze::Logger::getOutput() noexcept
{
   return m_output;
}

inline unsigned int ze::Logger::getLogMask() const noexcept
{
   return m_logMask;
}

inline bool ze::Logger::canLog() const noexcept
{
   return m_logLevel & m_logMask && m_output.rdbuf();
}

inline bool ze::Logger::isConsole() const noexcept
{
   return m_output.rdbuf() == std::cout.rdbuf() || m_output.rdbuf() == std::cerr.rdbuf() || m_output.rdbuf() == std::clog.rdbuf();
}

inline bool ze::Logger::canLogToConsole() const noexcept
{
   return m_logLevel & m_logMask && m_outputToConsole;
}

template<typename Message>
ze::Logger& ze::Logger::operator<<(Message const& message)
{
   write(message);
   return *this;
}

template<unsigned int N, typename Head, typename... Tail>
std::string ze::Logger::formatLine(std::string const& unformattedLine, Head const& head, Tail&&... tail)
{
   return formatLine<N + 1>(formatLine<N>(unformattedLine, head), std::forward<Tail>(tail)...);
}

template<unsigned int N, typename Arg>
std::string ze::Logger::formatLine(std::string const& unformattedLine, Arg const& arg)
{
   std::stringstream ss;

   size_t start = 0;
   size_t charPos = unformattedLine.find("{" + std::to_string(N) + "}");
   while (charPos != std::string::npos)
   {
      ss << unformattedLine.substr(start, charPos - start) << arg;

      start = charPos + 3;
      charPos = unformattedLine.find("{" + std::to_string(N) + "}", start);
   }

   ss << unformattedLine.substr(start);
   return ss.str();
}

template<typename Head, typename... Tail>
void ze::Logger::write(Head const& head, Tail&&... tail)
{
   write(head);
   write(std::forward<Tail>(tail)...);
}

template<typename Message>
void ze::Logger::write(Message const& message)
{
   if (canLog())
   {
      if (isConsole())
         setConsoleColor();

      printLineDetails();
      m_output << message;

      if (isConsole())
         resetConsoleColor();
   }

   if (canLogToConsole() && !isConsole()) // Printing to console twice is useless wtf
   {
      setConsoleColor();

      printLineDetails();
      logToConsole(message);

      resetConsoleColor();
   }
}


template<typename Message>
void ze::Logger::logToConsole(Message const& message)
{
   setConsoleColor();

   std::cout << message;

   resetConsoleColor();
}
