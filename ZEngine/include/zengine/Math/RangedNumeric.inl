#include "zengine/Memory/New.hpp"

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue, typename E>
ze::RangedNumeric<NumericType, MinValue, MaxValue, E>::RangedNumeric()
   : m_value(MinValue) {}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue, typename E>
ze::RangedNumeric<NumericType, MinValue, MaxValue, E>::RangedNumeric(NumericType value)
   : m_value(value)
{
   zassert(m_value >= static_cast<NumericType>(MinValue) && m_value <= static_cast<NumericType>(MaxValue), "Value outside of range");
}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue, typename E>
inline ze::RangedNumeric<NumericType, MinValue, MaxValue, E>::operator NumericType() noexcept
{
   return m_value;
}

template<typename NumericType, std::intmax_t MinValue, std::intmax_t MaxValue, typename E>
ze::RangedNumeric<NumericType, MinValue, MaxValue>& ze::RangedNumeric<NumericType, MinValue, MaxValue, E>::operator=(NumericType value)
{
   m_value = value;
   zassert(m_value >= static_cast<NumericType>(MinValue) && m_value <= static_cast<NumericType>(MaxValue), "Value outside of range");
   return *this;
}

#include "zengine/Memory/NewOff.hpp"
