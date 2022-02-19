#include "fmt/core.h"
template<typename Message>
inline void ze::Console::Trace(Message message)
{
   Trace("{}", message);
}

template<typename... Args>
inline void ze::Console::Trace(std::string const& fmt, Args&&... args)
{
   SetColor(Color::Red);
   
   std::cout << fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)) << std::endl;
   ze::Stacktrace().print(std::cout);

   ResetColor();
}

