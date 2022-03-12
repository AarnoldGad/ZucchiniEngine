/**
 * StreamWriter.hpp
 * 9 Feb 2022
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
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
#ifndef ZE_STREAMWRITER_HPP
#define ZE_STREAMWRITER_HPP

#include "zengine/defines.hpp"

#include "zengine/Log/Logger.hpp"
#include "zengine/Log/Writer.hpp"
#include "zengine/Time/Date.hpp"

namespace ze
{
   class OutputStream;

   class ZE_API StreamWriter : virtual public Writer
   {
   public:
      void write(std::string_view name, Date date, Logger::Level level, std::string_view message) override;
      void flush() override;
      void endLine() override;

      void setStream(OutputStream* stream);
      OutputStream const* getStream() const noexcept;

      explicit StreamWriter(OutputStream* stream = nullptr);

   private:
      OutputStream* m_stream;
      bool m_atLineStart;
   };
}

#include "StreamWriter.inl"

#endif // ZE_STREAMWRITER_HPP
