template<typename ResourceType>
ze::ResourceHolder<ResourceType>::ResourceHolder()
   : m_resource(), m_loader(&m_resource) {}

template<typename ResourceType>
inline ResourceType* ze::ResourceHolder<ResourceType>::resource() noexcept
{
   return &m_resource;
}

template<typename ResourceType>
inline ze::ResourceLoader<ResourceType>* ze::ResourceHolder<ResourceType>::loader() noexcept
{
   return &m_loader;
}

