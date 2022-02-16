// Inspired by https://www.foonathan.net/2016/09/assertions/

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
