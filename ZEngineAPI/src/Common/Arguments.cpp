#include "zepch.hpp"

#include "zengine/Common/Arguments.hpp"

namespace ze
{
   std::vector<Arguments::Argument> Arguments::s_arguments;

   void Arguments::Set(int argc, char* argv[])
   {
      s_arguments.reserve(argc);

      for (int i = 0; i < argc; ++i)
      {
         auto next = s_arguments.begin() + i + 1;
         if (next == s_arguments.end())
            s_arguments.push_back({ argv[i], nullptr });
         s_arguments.push_back({ argv[i], &*next });
      }
   }

   size_t Arguments::GetCount() noexcept
   {
      return s_arguments.size();
   }

   Arguments::Argument const* Arguments::Get(size_t index)
   {
      return &s_arguments.at(index);
   }

   Arguments::Argument const* Arguments::Find(std::string const& value)
   {
      auto found = std::find_if(s_arguments.begin(), s_arguments.end(),
                                [&value](Argument const& argument) { return argument.value == value; });
      return found != s_arguments.end() ? &*found : nullptr;
   }
}
