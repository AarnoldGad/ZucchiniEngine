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

#include "zengine/Resource/ResourceHolder.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <type_traits>

namespace ze
{
   template<typename ResourceType>
   class ResourceManager
   {
      static_assert((sizeof(ResourceHolder<ResourceType>), true), "Resource can not be held");
   public:
      static void AddSearchPath(std::filesystem::path const& dir);
      static std::unordered_set<std::string> const& GetSearchPaths() noexcept;
      static void RemoveSearchPath(std::filesystem::path const& dir);
      static void ClearSearchPaths() noexcept;

      static ResourceLoader<ResourceType>* Add(std::string const& id);
      static ResourceHolder<ResourceType>* Get(std::string const& id);

      static void Release(std::string const& id);
      static void ReleaseAll() noexcept;

   private:
      ResourceManager() = delete;

      static std::unordered_set<std::string> s_searchPaths;
      static std::unordered_map<std::string, std::unique_ptr<ResourceHolder<ResourceType> > > s_resources;
   };
}

#include "ResourceManager.inl"

#endif // ZE_RESOURCEMANAGER_HPP

