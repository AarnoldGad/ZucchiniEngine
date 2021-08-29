#include <zengine/Memory/New.hpp>

template<typename... Args>
inline void ze::MemoryTracker::MemoryLog(char const* format, Args&&... args)
{
   FILE* file = fopen("memtrack.log", "a");

   if (!file)
      return LOG_TRACE("Fail to open memory log file");

   char timeBuf[9];
   time_t date = std::time(nullptr);
   std::strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", std::localtime(&date));

   std::array<char, 150> line{0};
   int written = std::snprintf(line.data(), 150, format, std::forward<Args>(args)...);
   if (written < 0)
   {
      LOG_TRACE("Fail to write memory log !");
      fclose(file);
      return;
   }

   fprintf(file, "[%s] ", timeBuf);
   fputs(line.data(), file);
   fprintf(file, "\n");

   std::cout << "[" << timeBuf << "] " << line.data() << std::endl;

   fclose(file);
}

#include <zengine/Memory/NewOff.hpp>
