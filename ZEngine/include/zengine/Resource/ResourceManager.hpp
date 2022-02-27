/**
 * ResourceManager.hpp
 * 8 Feb 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
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

#include <unordered_map>
#include <string>
#include <memory>

namespace ze
{
   template<typename ResourceType>
   class ResourceManager
   {
   public:
      // TODO Should use unique+raw pointers or shared+weak pointers ?
      static ResourceType* add(std::string const& id);
      static ResourceType* get(std::string const& id);

      static void release(std::string const& id);
      static void releaseAll() noexcept;

      ResourceManager() = delete;

   private:
      static std::unordered_map<std::string, std::unique_ptr<ResourceType> > m_resources;
   };
}

#include "ResourceManager.inl"

#endif // ZE_RESOURCEMANAGER_HPP
