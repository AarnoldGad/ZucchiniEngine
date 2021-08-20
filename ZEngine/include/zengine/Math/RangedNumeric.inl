#include "zengine/Memory/New.hpp"

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue>
ze::RangedNumeric<NumericType, MinValue, MaxValue>::RangedNumeric()
   : m_value(MinValue) {}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue>
ze::RangedNumeric<NumericType, MinValue, MaxValue>::RangedNumeric(NumericType value)
   : m_value(value)
{
   ZE_ASSERT(m_value >= static_cast<NumericType>(MinValue) && m_value <= static_cast<NumericType>(MaxValue), "Value out of interval");
}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue>
inline ze::RangedNumeric<NumericType, MinValue, MaxValue>::operator NumericType() noexcept
{
   return m_value;
}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue>
ze::RangedNumeric<NumericType, MinValue, MaxValue>& ze::RangedNumeric<NumericType, MinValue, MaxValue>::operator=(NumericType value)
{
   m_value = value;
   ZE_ASSERT(m_value >= static_cast<NumericType>(MinValue) && m_value <= static_cast<NumericType>(MaxValue), "Value out of interval");
   return *this;
}

#include "zengine/Memory/NewOff.hpp"
