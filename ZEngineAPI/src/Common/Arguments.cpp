#include "zepch.hpp"

#include "zengine/Common/Arguments.hpp"

namespace ze
{
   std::vector<std::string> Arguments::s_arguments;

   void Arguments::Set(int argc, char* argv[])
   {
      for (int i = 0; i < argc; ++i)
         s_arguments.push_back(argv[i]);
   }

   size_t Arguments::GetCount() noexcept
   {
      return s_arguments.size();
   }

   std::string Arguments::Get(size_t index)
   {
      return s_arguments[index];
   }

   std::optional<std::string> Arguments::Find(std::string const& value)
   {
      auto found = std::find(s_arguments.begin(), s_arguments.end(), value);

      if (found != s_arguments.end())
         return *found;

      return std::nullopt;
   }
}
