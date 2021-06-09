#include "zepch.hpp"

#include "zengine/Common/System.hpp"

#include <bitset>

#ifdef _WIN32
   #include <lmcons.h>
#else
   #include <unistd.h>
#endif

#include "zengine/Memory/New.hpp"

namespace ze
{
   std::string GetSystemName()
   {
      #if defined(__unix__)

      const size_t hostNameSize = sysconf(_SC_HOST_NAME_MAX) + 1;
      std::string name;
      name.resize(hostNameSize);

      if (gethostname(&name[0], hostNameSize)) return "";

      return name;

      #elif defined(_WIN32)

      std::string name;
      name.resize(MAX_COMPUTERNAME_LENGTH + 1); // TODO Not sure about this +1
      DWORD x = MAX_COMPUTERNAME_LENGTH;
      GetComputerNameA(&name[0], &x);

      return name;

      #endif
   }

   std::string GetSystemUserName()
   {
      #if defined(__unix__)

      size_t loginNameSize = sysconf(_SC_LOGIN_NAME_MAX) + 1;
      std::string name;
      name.resize(loginNameSize);
      if (getlogin_r(&name[0], loginNameSize)) return "";

      return name; 

      #elif defined(_WIN32)

      std::string name;
      name.resize(UNLEN + 1); // TODO Not sure about this +1
      DWORD x = UNLEN;
      GetUserNameA(&name[0], &x);

      return name;

      #endif
   }

   std::string GetKernelName()
   {
      #if defined(__unix__)

      utsname sysInfo;
      uname(&sysInfo);

      return sysInfo.sysname;

      #elif defined(_WIN32)

      return "Windows";

      #endif
   }

   System::OS::Version GetKernelVersion()
   {
      #if defined(__unix__)

      utsname sysInfo;
      uname(&sysInfo);

      System::OS::Version version;
      char* cursor = sysInfo.release;
      version.major = static_cast<uint32_t>(std::strtoul(cursor    , &cursor, 10));
      version.minor = static_cast<uint32_t>(std::strtoul(cursor + 1, &cursor, 10));
      version.patch = static_cast<uint32_t>(std::strtoul(cursor + 1, &cursor, 10));
      version.rev   = static_cast<uint32_t>(std::strtoul(cursor + 1, nullptr, 10));

      return version;

      #elif defined(_WIN32)

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

      #endif
   }

   std::string GetSystemVersionName([[maybe_unused]] System::OS::Version version)
   {
      #if defined(__unix__)

      utsname sysInfo;
      uname(&sysInfo);

      return sysInfo.release;

      #elif defined(_WIN32)

      std::stringstream ss;
      ss << "v" << version.major << "." << version.minor << "." << version.patch << " rev" << version.rev;
      return ss.str();

      #endif
   }

   Architecture GetSystemArchitecture()
   {
      #if defined(__unix__)

      utsname sysInfo;
      uname(&sysInfo);

      if (!strcmp(sysInfo.machine, "i686") || !strcmp(sysInfo.machine, "i386"))
         return Architecture::x86;
      else if (!strcmp(sysInfo.machine, "x86_64"))
         return Architecture::x64;
      else if (!strcmp(sysInfo.machine, "arm") || !strcmp(sysInfo.machine, "armv7l"))
         return Architecture::ARM;
      else if (!strcmp(sysInfo.machine, "aarch64") || !strcmp(sysInfo.machine, "armv8l"))
         return Architecture::ARM64;
      else if (!strcmp(sysInfo.machine, "ia64"))
         return Architecture::IA64;
      else
         return Architecture::Unknown;

      #elif defined(_WIN32)

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
      #if defined(__unix__)

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

      #elif defined(_WIN32)

      std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> infoList;
      DWORD size = 0;
      GetLogicalProcessorInformation(nullptr, &size);
      infoList.resize(size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
      GetLogicalProcessorInformation(infoList.data(), &size);

      uint32_t physic = 0, logic = 0;

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

      #endif
   }

   std::string GetCPUModel()
   {
      #if defined(__unix__)

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

      #elif defined(_WIN32)

      HKEY hkey;
      if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)", 0, KEY_READ, &hkey))
         return {};

      char model[64];
      DWORD size = sizeof(model);
      if (RegQueryValueExA(hkey, "ProcessorNameString", nullptr, nullptr, static_cast<LPBYTE>(static_cast<void*>(&model[0])), &size))
         return {};

      return model;

      #endif
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
      Memory memoryInfo{};

      #if defined(__unix__)

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

      #elif defined(_WIN32)

      MEMORYSTATUSEX memStat;
      memStat.dwLength = sizeof(memStat);
      GlobalMemoryStatusEx(&memStat);

      memoryInfo.total = memStat.ullTotalPhys;
      memoryInfo.available = memStat.ullAvailPhys;
      memoryInfo.used = memStat.ullTotalPhys - memStat.ullAvailPhys;

      #endif

      return memoryInfo;
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
