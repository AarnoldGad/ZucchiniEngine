#include "zepch.hpp"

#include "zengine/Common/Random.hpp"

namespace ze
{
   std::default_random_engine Random::s_engine;

   void Random::Seed(unsigned int seed)
   {
      s_engine.seed(seed);
   }

   uint32_t Random::GenerateInteger(uint32_t minimum, uint32_t maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      ZE_ASSERT(maximum <= std::default_random_engine::max(), "Maximum value is too high !");

      return static_cast<unsigned int>(s_engine()) % maximum + minimum;
   }

   double Random::GenerateFloat(double minimum, double maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      return static_cast<double>(s_engine()) / static_cast<double>(std::default_random_engine::max() / (maximum - minimum)) + minimum;
   }
}
