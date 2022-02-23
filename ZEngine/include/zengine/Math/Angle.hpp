/**
 * Angle.hpp
 * 26 Sep 2021
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
#ifndef ZE_ANGLE_HPP
#define ZE_ANGLE_HPP

#include "zengine/defines.hpp"

#include "zengine/Math/Math.hpp"

namespace ze
{
   class Angle;

   Angle degrees(float deg) noexcept;
   Angle radians(float rad) noexcept;
   Angle arcseconds(float seconds) noexcept;
   Angle arcminutes(float minutes) noexcept;

   Angle normalise(Angle angle) noexcept;
   Angle clamp(Angle angle, ze::Angle min, ze::Angle max) noexcept;

   namespace literals
   {
      Angle operator""_deg(long double deg) noexcept;
      Angle operator""_rad(long double rad) noexcept;
      Angle operator""_asec(long double seconds) noexcept;
      Angle operator""_amin(long double seconds) noexcept;
   }

   class ZE_API Angle
   {
   public:
      float asDegrees() const noexcept;
      float asRadians() const noexcept;
      float asArcSeconds() const noexcept;
      float asArcMinutes() const noexcept;

      Angle& normalise() noexcept;
      Angle& clamp(ze::Angle min, ze::Angle max) noexcept;

      Angle operator-() const noexcept;

      Angle& operator+=(Angle const& other) noexcept;
      Angle& operator-=(Angle const& other) noexcept;
      Angle& operator*=(Angle const& other) noexcept;
      Angle& operator*=(float factor) noexcept;
      Angle& operator/=(Angle const& other) noexcept;
      Angle& operator/=(float factor) noexcept;
      Angle& operator%=(Angle const& other) noexcept;
      Angle& operator%=(float factor) noexcept;

      Angle& operator+(Angle const& other) noexcept;
      Angle& operator-(Angle const& other) noexcept;
      Angle& operator*(Angle const& other) noexcept;
      Angle& operator*(float factor) noexcept;
      Angle& operator/(Angle const& other) noexcept;
      Angle& operator/(float factor) noexcept;
      Angle& operator%(Angle const& other) noexcept;
      Angle& operator%(float factor) noexcept;

      bool operator==(Angle const& other) const noexcept;
      bool operator!=(Angle const& other) const noexcept;
      bool operator<=(Angle const& other) const noexcept;
      bool operator>=(Angle const& other) const noexcept;
      bool operator<(Angle const& other) const noexcept;
      bool operator>(Angle const& other) const noexcept;

      Angle();

   private:
      explicit Angle(float deg);

      float m_degrees;

      friend Angle degrees(float) noexcept;
      friend Angle radians(float) noexcept;
      friend Angle arcseconds(float) noexcept;
      friend Angle arcminutes(float) noexcept;
   };
}

#include "Angle.inl"

#endif /* ZE_ANGLE_HPP */
