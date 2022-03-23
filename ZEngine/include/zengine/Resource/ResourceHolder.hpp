/**
 * ResourceHolder.hpp
 * 22 Mars 2022
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
#ifndef ZE_RESOURCEHOLDER_HPP
#define ZE_RESOURCEHOLDER_HPP

#include "zengine/defines.hpp"

namespace ze
{
   template<typename ResourceType>
   class ResourceLoader;

   template<typename ResourceType>
   class ResourceHolder
   {
      static_assert(std::is_class_v<ResourceType>, "Resource should be class type!");
      static_assert(not std::is_const_v<ResourceType>, "Resource can not be const!");
   public:
      ResourceType* resource() noexcept;
      ResourceLoader<ResourceType>* loader() noexcept;
      
      ResourceHolder();

   private:
      ResourceHolder(ResourceHolder const&) = delete;
      ResourceHolder(ResourceHolder&&) = delete;
      ResourceHolder& operator=(ResourceHolder const&) = delete;
      ResourceHolder& operator=(ResourceHolder&&) = delete;

      ResourceType m_resource;
      ResourceLoader<ResourceType> m_loader;
   };
}

#include "ResourceHolder.inl"

#endif // ZE_RESOURCEHOLDER_HPP

