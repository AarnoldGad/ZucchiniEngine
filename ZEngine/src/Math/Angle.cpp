#include "zepch.hpp"

#include "zengine/Math/Angle.hpp"

namespace ze
{
   Angle degrees(float deg) noexcept
   {
      return Angle(deg);
   }

   Angle radians(float rad) noexcept
   {
      return Angle(rad * 180.f / static_cast<float>(std::numbers::pi));
   }

   Angle arcseconds(float seconds) noexcept
   {
      return Angle(seconds / 3600.f);
   }

   Angle arcminutes(float minutes) noexcept
   {
      return Angle(minutes / 60.f);
   }

   Angle normalise(Angle angle) noexcept
   {
      return angle.normalise();
   }

   Angle clamp(Angle angle, ze::Angle min, ze::Angle max) noexcept
   {
      return angle.clamp(min, max);
   }

   namespace literals
   {
      Angle operator""_deg(long double deg) noexcept
      {
         return degrees(static_cast<float>(deg));
      }

      Angle operator""_rad(long double rad) noexcept
      {
         return radians(static_cast<float>(rad));
      }

      Angle operator""_asec(long double seconds) noexcept
      {
         return arcseconds(static_cast<float>(seconds));
      }

      Angle operator""_amin(long double minutes) noexcept
      {
         return arcminutes(static_cast<float>(minutes));
      }
   }

   Angle::Angle()
      : m_degrees{} {}

   Angle::Angle(float deg)
      : m_degrees(deg) {}

   Angle& Angle::normalise() noexcept
   {
      m_degrees = std::fmod(m_degrees, 360.f);
      if (m_degrees < 0.f)
         m_degrees += 360.f;
      return *this;
   }

   Angle& Angle::clamp(ze::Angle min, ze::Angle max) noexcept
   {
      ZE_ASSERT(min < max, "min should be smaller than max !");

      if (m_degrees < min.m_degrees)
         m_degrees = min.m_degrees;
      if (m_degrees > max.m_degrees)
         m_degrees = max.m_degrees;

      return *this;
   }

   Angle Angle::operator-() const noexcept
   {
      return Angle(-m_degrees);
   }

   Angle& Angle::operator+=(Angle const& other) noexcept
   {
      m_degrees += other.m_degrees;
      return *this;
   }

   Angle& Angle::operator-=(Angle const& other) noexcept
   {
      m_degrees -= other.m_degrees;
      return *this;
   }

   Angle& Angle::operator*=(Angle const& other) noexcept
   {
      m_degrees *= other.m_degrees;
      return *this;
   }

   Angle& Angle::operator*=(float factor) noexcept
   {
      m_degrees *= factor;
      return *this;
   }

   Angle& Angle::operator/=(Angle const& other) noexcept
   {
      try
      {
         m_degrees /= other.m_degrees;
      }
      catch (...) {}

      return *this;
   }

   Angle& Angle::operator/=(float factor) noexcept
   {
      try
      {
         m_degrees /= factor;
      }
      catch (...) {}

      return *this;
   }

   Angle& Angle::operator%=(Angle const& other) noexcept
   {
      m_degrees = std::fmod(m_degrees, other.m_degrees);
      return *this;
   }

   Angle& Angle::operator%=(float factor) noexcept
   {
      m_degrees = std::fmod(m_degrees, factor);
      return *this;
   }

   Angle& Angle::operator+(Angle const& other) noexcept
   {
      return operator+=(other);
   }

   Angle& Angle::operator-(Angle const& other) noexcept
   {
      return operator-=(other);
   }

   Angle& Angle::operator*(Angle const& other) noexcept
   {
      return operator*=(other);
   }

   Angle& Angle::operator*(float factor) noexcept
   {
      return operator*=(factor);
   }

   Angle& Angle::operator/(Angle const& other) noexcept
   {
      return operator/=(other);
   }

   Angle& Angle::operator/(float factor) noexcept
   {
      return operator/=(factor);
   }

   Angle& Angle::operator%(Angle const& other) noexcept
   {
      return operator%=(other);
   }

   Angle& Angle::operator%(float factor) noexcept
   {
      return operator%=(factor);
   }

   bool Angle::operator==(Angle const& other) const noexcept
   {
      return m_degrees == other.m_degrees;
   }

   bool Angle::operator!=(Angle const& other) const noexcept
   {
      return !operator==(other);
   }

   bool Angle::operator<=(Angle const& other) const noexcept
   {
      return m_degrees <= other.m_degrees;
   }

   bool Angle::operator>=(Angle const& other) const noexcept
   {
      return m_degrees >= other.m_degrees;
   }

   bool Angle::operator<(Angle const& other) const noexcept
   {
      return m_degrees < other.m_degrees;
   }

   bool Angle::operator>(Angle const& other) const noexcept
   {
      return m_degrees > other.m_degrees;
   }
}
