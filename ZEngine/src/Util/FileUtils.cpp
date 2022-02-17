#include "zepch.hpp"

#include "zengine/Util/FileUtils.hpp"

#include "zengine/Common/Console.hpp"

#include <sstream>
#include <fstream>

namespace ze
{
   std::optional<std::string> FileUtils::GetFileContent(std::filesystem::path const& path)
   {
      std::ifstream file(path);
      if (!file)
      {
         Console::Trace("Fail to open file {}", path);
         return std::nullopt;
      }

      std::stringstream content;
      content << file.rdbuf();
      file.close();
      return content.str();
   }
}
