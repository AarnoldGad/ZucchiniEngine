#include "zengine/Util/FileUtils.hpp"

#include <sstream>
#include <fstream>

#include "zengine/Memory/New.hpp"

namespace ze
{
   namespace FileUtils
   {
      std::optional<std::string> GetFileContent(std::filesystem::path const& path)
      {
         std::ifstream file(path);
         if (!file)
         {
            LOG_TRACE("Fail to open file ", path.string());
            return std::nullopt;
         }

         std::stringstream content;
         content << file.rdbuf();
         file.close();
         return content.str();
      }
   }
}
