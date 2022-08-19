#ifndef ZE_LAYER_HPP
#define ZE_LAYER_HPP

#include "zengine/defines.hpp"

#include <zucchini/zucchini.hpp>
#include <string>

namespace ze
{
   class ZE_API Layer
   {
   public:
      virtual void onConnection() = 0;
      virtual void onDisconnection() = 0;

      virtual void tick(Time deltaTime) = 0;

      std::string const& getId() const noexcept;

      Layer(std::string const& id);
      virtual ~Layer() = default;

   protected:
      std::string const m_id;
   };
}

#include "Layer.inl"

#endif // ZE_LAYER_HPP
/**
 * Layer.hpp
 * 17 Nov 2021
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

