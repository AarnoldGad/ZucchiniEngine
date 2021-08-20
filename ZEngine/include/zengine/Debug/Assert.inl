#include <zengine/Memory/New.hpp>

// Inspired by https://www.foonathan.net/2016/09/assertions/

[[noreturn]] inline void ze::AssertHandler::handle(SourceLocation const& location, char const* expression, char const* message) noexcept
{
   LOG_TRACE(location.file, "::", location.function, " (", location.line, ") : Assertion failed \"", expression, "\"", (message ? " : " : ""), (message ? message : ""));
   std::abort();
}

template<typename EvaluatorFn, typename HandlerType, typename... Args, std::enable_if_t<HandlerType::enabled, int> >
inline void ze::Assert(EvaluatorFn const& evaluator, SourceLocation const& location, char const* expression, HandlerType handler, Args&&... args) noexcept
{
   if (!evaluator())
   {
      handler.handle(location, expression, std::forward<Args>(args)...);
      std::abort();
   }
}

template<typename EvaluatorFn, typename HandlerType, typename... Args, std::enable_if_t<!HandlerType::enabled, int> >
inline void ze::Assert([[maybe_unused]] EvaluatorFn const& evaluator, [[maybe_unused]] SourceLocation const& location,
                       [[maybe_unused]] char const* expression, [[maybe_unused]] HandlerType handler, [[maybe_unused]] Args&&... args) noexcept
{}

#include <zengine/Memory/NewOff.hpp>
