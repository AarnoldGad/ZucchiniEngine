template<typename Message>
inline void ze::Console::Trace(Message message)
{
   Trace("{}", message);
}

template<typename... Args>
inline void ze::Console::Trace(std::string const& fmt, Args&&... args)
{
   SetColor(Color::Red);
   
   std::cout << fmt::format(fmt, std::forward<Args>(args)...) << std::endl;
   
   ze::CallStack stack = ze::Stacktrace(8, 1);
   for (size_t i = 0; i < stack.getSize(); ++i)
      std::cout << "\t at " << (stack[i].toString()) << std::endl;
   
   ResetColor();
}

