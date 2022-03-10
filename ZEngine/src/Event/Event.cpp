#include "zepch.hpp"

#include "zengine/Event/Event.hpp"

#include "zengine/Core/Core.hpp"

namespace ze
{
   Event::Event()
      : m_canceled(false), m_timestamp(Core::GetTime()) {}

   void Event::cancel() noexcept
   {
      m_canceled = true;
   }

   void Event::setCanceled(bool cancel) noexcept
   {
      m_canceled = cancel;
   }
}
