/**
 * ResourceManager.hpp
 * 8 Feb 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_RESOURCEMANAGER_HPP
#define ZE_RESOURCEMANAGER_HPP

#include "zengine/defines.hpp"

#include "zengine/Util/FileUtils.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <type_traits>

namespace ze
{
   template<typename ResourceType>
   class ResourceLoader;

   template<typename ResourceType>
   class ResourceDeleter
   {
   public:
      void operator()(ResourceType* resource) const;
   };

   template<typename ResourceType>
   class ResourceManager
   {
      static_assert((sizeof(ResourceLoader<ResourceType>), true), "Resource do not have any loader !");
      static_assert(std::is_class_v<ResourceType>, "Resource should be class type !");
      static_assert(!std::is_const_v<ResourceType>, "Resource can not be const !");

   public:
      static void AddSearchPath(std::filesystem::path const& dir);
      static std::unordered_set<std::string> const& GetSearchPaths() noexcept;
      static void RemoveSearchPath(std::filesystem::path const& dir);
      static void ClearSearchPaths() noexcept;
      static std::optional<std::filesystem::path> FindFile(std::filesystem::path const& file);

      template<typename... Args>
      static ResourceType* Load(std::string const& id, Args&&... args);
      template<typename... Args>
      static ResourceType* Reload(std::string const& id, Args&&... args);
      static ResourceType* Get(std::string const& id);

      static void Unload(std::string const& id);
      static void UnloadAll() noexcept;

   private:
      ResourceManager() = delete;

      static std::unordered_set<std::string> s_searchPaths;
      static std::unordered_map<std::string, std::unique_ptr<ResourceType, ResourceDeleter<ResourceType> > > s_resources;
   };
}

#include "ResourceManager.inl"

#endif // ZE_RESOURCEMANAGER_HPP

