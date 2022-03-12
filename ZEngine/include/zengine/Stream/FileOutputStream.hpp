/**
 * FileOutputStream.hpp
 * 15 Feb 2022
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
#ifndef ZE_FILEOUTPUTSTREAM_HPP
#define ZE_FILEOUTPUTSTREAM_HPP

#include "zengine/defines.hpp"

#include "zengine/Stream/OutputStream.hpp"

#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>

namespace ze
{
   class ZE_API FileOutputStream : public OutputStream
   {
   public:
      void open(std::filesystem::path const& file, std::ios_base::openmode mode = std::ios_base::out);
      void close();

      bool isOpen() const;
      explicit operator bool() const override;

      OutputStream& put(char ch) override;
      OutputStream& write(std::string_view str) override;
      OutputStream& operator<<(std::string_view str) override;
      OutputStream& flush() override;

      ptrdiff_t tellp() override;
      OutputStream& seekp(ptrdiff_t pos) override;

      explicit FileOutputStream(std::filesystem::path const& file, std::ios_base::openmode mode = std::ios_base::out);
      FileOutputStream() = default;

   private:
      std::ofstream m_file;
   };
}

#include "FileOutputStream.inl"

#endif // ZE_FILEOUTPUTSTREAM_HPP
