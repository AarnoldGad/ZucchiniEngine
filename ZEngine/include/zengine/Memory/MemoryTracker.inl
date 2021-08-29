#include <zengine/Memory/New.hpp>

template<typename... Args>
inline void ze::MemoryTracker::MemoryLog(char const* format, Args&&... args)
{
   std::array<char, 150> line{0};
   int written = std::snprintf(line.data(), 150, format, std::forward<Args>(args)...);
   if (written < 0)
      return LOG_TRACE("Fail to write memory log !");

   MemoryLog(line.data());
}

#include <zengine/Memory/NewOff.hpp>
