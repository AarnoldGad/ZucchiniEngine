#include "zepch.hpp"

#include "zengine/Util/FileUtils.hpp"

#include "zengine/Common/Console.hpp"

#include <sstream>
#include <fstream>

namespace ze
{
   [[nodiscard]]
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

   [[nodiscard]]
   std::optional<std::filesystem::path> FileUtils::Search(std::unordered_set<std::string> const& inDirectories,
                                                          std::filesystem::path const& forFile)
   {
      for (auto& dir : inDirectories)
      {
         std::filesystem::path hypotheticFile = std::filesystem::absolute(dir);
         hypotheticFile /= std::filesystem::relative(forFile);

         if (std::filesystem::exists(hypotheticFile))
            return hypotheticFile;
      }

      return std::nullopt;
   }
}
