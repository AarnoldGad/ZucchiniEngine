/**
 * CallStack.hpp
 * 18 Aug 2021
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
#ifndef ZE_CALLSTACK_HPP
#define ZE_CALLSTACK_HPP

#include "zengine/defines.hpp"

#include "zengine/Backtrace/StackFrame.hpp"
#include "zengine/Math/RangedNumeric.hpp"

#include <vector>

namespace ze
{
   class ZE_API CallStack
   {
   public:
      size_t getSize() const noexcept;
      StackFrame const& getFrame(size_t index) const;
      StackFrame const& operator[](size_t index) const;

      CallStack(RangedInt<0, 32> size, int skip = 0);

   private:
      std::vector<StackFrame> m_frames;
   };

   ZE_API CallStack Stacktrace(RangedInt<0, 32> size = 32, int skip = 0);
}

#include "CallStack.inl"

#endif /* ZE_CALLSTACK_HPP */
