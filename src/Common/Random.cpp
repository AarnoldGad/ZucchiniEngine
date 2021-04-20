#include "zepch.hpp"

#include "zengine/Common/Random.hpp"

namespace ze
{
   std::default_random_engine Random::s_engine;

   void Random::Seed(unsigned int seed)
   {
      s_engine.seed(seed);
   }

   uint32_t Random::Generate(uint32_t minimum, uint32_t maximum)
   {
      return static_cast<uint32_t>(GenerateLong(minimum, maximum));
   }

   uint64_t Random::GenerateLong(uint64_t minimum, uint64_t maximum)
   {
      zassert(minimum < maximum, "Minimum value is greater than maximum !");
      zassert(maximum <= std::default_random_engine::max(), "Maximum value is too high !");
      return s_engine() % maximum + minimum;
   }

   float Random::GenerateFloat(float minimum, float maximum)
   {
      return static_cast<float>(GenerateDouble(minimum, maximum));
   }

   double Random::GenerateDouble(double minimum, double maximum)
   {
      zassert(minimum < maximum, "Minimum value is greater than maximum !");
      return static_cast<double>(s_engine()) / static_cast<double>(std::default_random_engine::max() / (maximum - minimum)) + minimum;
   }
}
