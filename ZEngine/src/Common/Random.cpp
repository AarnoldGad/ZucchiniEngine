#include "zepch.hpp"

#include "zengine/Common/Random.hpp"

#include "zengine/Memory/New.hpp"

namespace ze
{
   std::default_random_engine Random::s_engine;

   void Random::Seed(unsigned int seed)
   {
      s_engine.seed(seed);
   }

   uint64_t Random::GenerateInteger(uint64_t minimum, uint64_t maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      ZE_ASSERT(maximum <= std::default_random_engine::max(), "Maximum value is too high !");
      
      return s_engine() % maximum + minimum;
   }

   double Random::GenerateFloat(double minimum, double maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      return static_cast<double>(s_engine()) / static_cast<double>(std::default_random_engine::max() / (maximum - minimum)) + minimum;
   }
}
