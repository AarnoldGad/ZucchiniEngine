inline float ze::Angle::asDegrees() const noexcept
{
   return m_degrees;
}

inline float ze::Angle::asRadians() const noexcept
{
   return m_degrees * static_cast<float>(ze::pi()) / 180.f;
}

inline float ze::Angle::asArcSeconds() const noexcept
{
   return m_degrees * 3600.f;
}

inline float ze::Angle::asArcMinutes() const noexcept
{
   return m_degrees * 60.f;
}
