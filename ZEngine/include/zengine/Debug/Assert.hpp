/**
 * Assert.hpp
 * 11 Mar 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_ASSERT_HPP
#define ZE_ASSERT_HPP

#include "zengine/zemacros.hpp"

namespace ze
{
   class AssertHandler
   {
   public:
      #ifdef NDEBUG
         static constexpr const bool enabled = false;
      #else
         static constexpr const bool enabled = true;
      #endif

      [[noreturn]] void handle(SourceLocation const& location, char const* expression, char const* message = nullptr) noexcept;
   };

   // Assert enabled
   template<typename EvaluatorFn, typename HandlerType, typename... Args, std::enable_if_t<HandlerType::enabled, int> = 0>
   void Assert(EvaluatorFn const& evaluator, SourceLocation const& location, char const* expression, HandlerType handler, Args&&... args) noexcept;

   // Assert disabled
   template<typename EvaluatorFn, typename HandlerType, typename... Args, std::enable_if_t<!HandlerType::enabled, int> = 0>
   void Assert(EvaluatorFn const& evaluator, SourceLocation const& location, char const* expression, HandlerType handler, Args&&... args) noexcept;
}

#define ASSERT(expr, ...)  ze::Assert([&](void) -> bool { return (expr); }, CURRENT_SOURCE_LOCATION, #expr, __VA_ARGS__)
#define ZE_ASSERT(expr, message) ze::Assert([&](void) -> bool { return (expr); }, CURRENT_SOURCE_LOCATION, #expr, ze::AssertHandler{}, message)

#include "Assert.inl"

#endif // ZE_ASSERT_HPP
