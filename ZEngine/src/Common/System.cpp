// Inspired by https://github.com/ThePhD/infoware

#include "zepch.hpp"

#include "zengine/Common/System.hpp"

#include "zengine/Common/Backtrace/CallStack.hpp"

#include <bitset>
#include <csignal>
#include <cstdlib>

#if defined(_WIN32)
   #include <lmcons.h>
#elif defined(__linux__)
   #include <unistd.h>
#elif defined(__MACH__) || defined(__APPLE__)
   #include <unistd.h>
   #include <sys/utsname.h>
   #include <sys/sysctl.h>
   #include <sys/types.h>
   #include <mach/vm_statistics.h>
   #include <mach/mach.h>
#endif

#include "zengine/Memory/New.hpp"

namespace ze
{
   namespace
   {
      std::string GetSystemName()
      {
         std::string name;

         #if defined(_WIN32)

            name.resize(MAX_COMPUTERNAME_LENGTH + 1); // TODO Not sure about this +1
            DWORD x = MAX_COMPUTERNAME_LENGTH;
            GetComputerNameA(&name[0], &x);

         #else

            const size_t hostNameSize = static_cast<size_t>(sysconf(_SC_HOST_NAME_MAX)) + 1;
            name.resize(hostNameSize);

            if (gethostname(&name[0], hostNameSize)) return "";

         #endif

         return name;
      }

      std::string GetSystemUserName()
      {
         #if defined(_WIN32)

            std::string name;
            name.resize(UNLEN + 1); // TODO Not sure about this +1
            DWORD x = UNLEN;
            GetUserNameA(&name[0], &x);

            return name;

         #else

            std::string name;
            size_t loginNameSize = static_cast<size_t>(sysconf(_SC_LOGIN_NAME_MAX)) + 1;
            name.resize(loginNameSize);
            if (getlogin_r(&name[0], loginNameSize)) return "";

            return name;

         #endif
      }

      std::string GetKernelName()
      {

         #if defined(_WIN32)

            return "Windows";

         #else

            utsname sysInfo;
            uname(&sysInfo);

            return sysInfo.sysname;

         #endif
      }

      System::OS::Version GetKernelVersion()
      {

         #if defined(_WIN32)

            // return "\"Windows is a mess to get the version (and you don't even care), gfy\"";

            std::string path;
            path.resize(GetSystemDirectoryA(nullptr, 0) - 1);
            GetSystemDirectoryA(&path[0], static_cast<uint32_t>(path.size() + 1));
            path += "\\kernel32.dll";

            uint32_t const verBufSize = GetFileVersionInfoSizeA(path.c_str(), nullptr);
            auto verBuf = std::make_unique<uint8_t[]>(verBufSize);
            GetFileVersionInfoA(path.c_str(), 0, verBufSize, verBuf.get());

            VS_FIXEDFILEINFO* version;
            uint32_t verSize;
            VerQueryValueA(verBuf.get(), "", reinterpret_cast<void**>(&version), &verSize);

            return { HIWORD(version->dwProductVersionMS), LOWORD(version->dwProductVersionMS), HIWORD(version->dwProductVersionLS), LOWORD(version->dwProductVersionLS) };

         #else

            utsname sysInfo;
            uname(&sysInfo);

            System::OS::Version version;
            char* cursor = sysInfo.release;
            version.major = static_cast<uint32_t>(std::strtoul(cursor, &cursor, 10));
            version.minor = static_cast<uint32_t>(std::strtoul(cursor + 1, &cursor, 10));
            version.patch = static_cast<uint32_t>(std::strtoul(cursor + 1, &cursor, 10));
            version.rev = static_cast<uint32_t>(std::strtoul(cursor + 1, nullptr, 10));

            return version;

         #endif
      }

      std::string GetSystemVersionName([[maybe_unused]] System::OS::Version version)
      {

         #if defined(_WIN32)

            std::stringstream ss;
            ss << "v" << version.major << "." << version.minor << "." << version.patch << " rev" << version.rev;
            return ss.str();

         #else

            utsname sysInfo;
            uname(&sysInfo);

            return sysInfo.release;

         #endif
      }

      Architecture GetSystemArchitecture()
      {
         #if defined(_WIN32)

            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);

            switch (sysInfo.wProcessorArchitecture)
            {
               case PROCESSOR_ARCHITECTURE_INTEL:
                  return Architecture::x86;
               case PROCESSOR_ARCHITECTURE_AMD64:
                  return Architecture::x64;
               case PROCESSOR_ARCHITECTURE_ARM:
                  return Architecture::ARM;
               case PROCESSOR_ARCHITECTURE_ARM64:
                  return Architecture::ARM64;
               case PROCESSOR_ARCHITECTURE_IA64:
                  return Architecture::IA64;
               default:
                  return Architecture::Unknown;
            }

         #else

            utsname sysInfo;
            uname(&sysInfo);

            if (!strcmp(sysInfo.machine, "i686") ||
                !strcmp(sysInfo.machine, "i386"))
               return Architecture::x86;
            else if (!strcmp(sysInfo.machine, "x86_64"))
               return Architecture::x64;
            else if (!strcmp(sysInfo.machine, "arm") ||
                     !strcmp(sysInfo.machine, "armv7l"))
               return Architecture::ARM;
            else if (!strcmp(sysInfo.machine, "aarch64") ||
                     !strcmp(sysInfo.machine, "armv8l") ||
                     !strcmp(sysInfo.machine, "arm64"))
               return Architecture::ARM64;
            else if (!strcmp(sysInfo.machine, "ia64"))
               return Architecture::IA64;
            else
               return Architecture::Unknown;

         #endif
      }

      Endianess GetSystemEndianess()
      {
         union
         {
            uint32_t a;
            char b[4];
         } c = { 0x01020304 }; // I have absolutely no idea what names I could give to these things

         return c.b[0] == 1 ? Endianess::Big : Endianess::Little;
      }

      Processor::Cores GetCPUCores()
      {
         #if defined(_WIN32)

            std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> infoList;
            DWORD size = 0;
            GetLogicalProcessorInformation(nullptr, &size);
            infoList.resize(size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
            GetLogicalProcessorInformation(infoList.data(), &size);

            uint32_t physic = 0;
            uint32_t logic = 0;

            for (auto&& info : infoList)
            {
               switch (info.Relationship)
               {
                  case RelationProcessorCore:
                     ++physic;
                     logic += static_cast<uint32_t>(std::bitset<sizeof(uint64_t) * 8>(info.ProcessorMask).count());
                     break;
                  default:
                     break;
               }
            }

            return { physic, logic };

         #elif defined(__linux__)

            std::ifstream cpuinfo("/proc/cpuinfo");
            if (!cpuinfo) return {};

            uint32_t physic = 0;
            uint32_t logic = static_cast<uint32_t>(sysconf(_SC_NPROCESSORS_ONLN));

            for (std::string line; std::getline(cpuinfo, line);)
            {
               if (line.find("cpu cores") != std::string::npos) // TODO Test on other unix platforms
               {
                  physic = static_cast<uint32_t>(std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10));
                  break;
               }
            }

            return { physic, logic };

         #elif defined(__MACH__) || defined(__APPLE__)

            int physic = 0, logic = 0;
            size_t length = sizeof(int);
         
            sysctlbyname("machdep.cpu.core_count", &physic, &length, nullptr, 0);
            sysctlbyname("machdep.cpu.thread_count", &logic, &length, nullptr, 0);

            return { static_cast<uint32_t>(physic), static_cast<uint32_t>(logic) };

         #endif
      }

      std::string GetCPUModel()
      {
         #if defined(_WIN32)

            HKEY hkey;
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)", 0, KEY_READ, &hkey))
               return {};

            char model[64];
            DWORD size = sizeof(model);
            if (RegQueryValueExA(hkey, "ProcessorNameString", nullptr, nullptr, static_cast<LPBYTE>(static_cast<void*>(&model[0])), &size))
               return {};

            return model;

         #elif defined(__linux__)

            std::ifstream cpuinfo("/proc/cpuinfo");
            if (!cpuinfo) return {};

            std::string model;
            for (std::string line; std::getline(cpuinfo, line);)
            {
               if (line.find("model name") != std::string::npos)
               {
                  model = line.substr(line.find(":") + 1); // TODO Test on other unix platforms
                  break;
               }
            }

            return model;

         #elif defined(__APPLE__) || defined(__MACH__)

            char name[64];
            size_t namelen = sizeof(name);

            sysctlbyname("machdep.cpu.brand_string", &name, &namelen, nullptr, 0);

            return name;

         #endif
      }
   }

   void (*SetSignalHandler(StdSignal signal, void (*handler)(int)))(int)
   {
      return std::signal(static_cast<int>(signal), handler);
   }

   int CallAtExit(void (*fn)(void))
   {
      return std::atexit(fn);
   }

   [[noreturn]] void RaiseCritical(int code, char const* description) noexcept
   {
      LOG_TRACE(description);
      std::exit(code);
   }

   System GetSystemInfo()
   {
      System sysInfo{};

      sysInfo.systemName = GetSystemName();
      sysInfo.userName = GetSystemUserName();
      sysInfo.os.name = GetKernelName();
      sysInfo.os.version = GetKernelVersion();
      sysInfo.os.versionString = GetSystemVersionName(sysInfo.os.version);

      return sysInfo;
   }

   Processor GetProcessorInfo()
   {
      Processor cpuInfo{};

      cpuInfo.arch = GetSystemArchitecture();
      cpuInfo.endian = GetSystemEndianess();
      cpuInfo.cores = GetCPUCores();
      cpuInfo.model = GetCPUModel();

      return cpuInfo;
   }

   Memory GetMemoryInfo()
   {
      #if defined(_WIN32)

         Memory memoryInfo{};

         MEMORYSTATUSEX memStat;
         memStat.dwLength = sizeof(memStat);
         GlobalMemoryStatusEx(&memStat);

         memoryInfo.total = memStat.ullTotalPhys;
         memoryInfo.available = memStat.ullAvailPhys;
         memoryInfo.used = memStat.ullTotalPhys - memStat.ullAvailPhys;

         return memoryInfo;

      #elif defined(__linux__)

         Memory memoryInfo{};

         std::ifstream meminfo("/proc/meminfo");
         if (!meminfo) return {};

         for (std::string line; std::getline(meminfo, line);)
         {
            if (line.find("MemTotal") != std::string::npos)
               memoryInfo.total = std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10);
            if (line.find("MemAvailable") != std::string::npos)
               memoryInfo.available= std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10);
         }

         memoryInfo.used = memoryInfo.total - memoryInfo.available;

         return memoryInfo;

      #elif defined(__MACH__) || defined(__APPLE__)

         uint64_t total = 0, available = 0;
         size_t length = sizeof(uint64_t);

         vm_statistics64 stats;
         natural_t count = HOST_VM_INFO64_COUNT;
         mach_port_t host = mach_host_self();

         sysctlbyname("hw.memsize", &total, &length, nullptr, 0);
         host_statistics64(host, HOST_VM_INFO64, reinterpret_cast<host_info64_t>(&stats), &count);
         available = stats.free_count * static_cast<unsigned>(getpagesize());

         return { total, available, total - available };

      #endif
   }

   std::string ArchToString(Architecture arch)
   {
      switch (arch)
      {
         case Architecture::x64:
            return "x64";
         case Architecture::x86:
            return "x86";
         case Architecture::ARM:
            return "ARM";
         case Architecture::ARM64:
            return "ARM64";
         case Architecture::IA64:
            return "IA64";
         case Architecture::Unknown:
         default:
            return "UNKNOWN";
      }
   }
}
