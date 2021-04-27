#include "zepch.hpp"

#include "zengine/Debug/Assert.hpp"

#include "zengine/Memory/New.hpp"

#ifdef ZE_DEBUG
   namespace ze
   {
      void Assert(bool const condition, std::string const& file, std::string const& function, unsigned int line, std::string const& conditionAsString, std::string const& message)
      {
         if (!condition)
         {
            std::stringstream finalMessage;
            finalMessage << "Assertion failed \"" << conditionAsString << "\"\n\t\t at " << file << "::" << function << ":" << line << "\n\t" << message << std::endl;
            LOG_TRACE(finalMessage.str());
            throw finalMessage.str(); // TODO Exception system (this is really shit)
         }
      }
   }
#endif
