template<typename ResourceType>
std::unordered_map<std::string, std::shared_ptr<ResourceType> > ze::ResourceManager<ResourceType>::m_resources{};

template<typename ResourceType>
std::shared_ptr<ResourceType> ze::ResourceManager<ResourceType>::add(std::string const& id)
{
   auto result = ResourceManager<ResourceType>::m_resources.try_emplace(id, std::make_shared<ResourceType>());
   return result.first->second;
}

template<typename ResourceType>
std::shared_ptr<ResourceType> ze::ResourceManager<ResourceType>::get(std::string const& id)
{
   auto resource = m_resources.find(id);
   return resource != m_resources.end() ? resource->second : nullptr;
}

template<typename ResourceType>
void ze::ResourceManager<ResourceType>::release(std::string const& id)
{
   m_resources.erase(id);
}

template<typename ResourceType>
void ze::ResourceManager<ResourceType>::releaseAll() noexcept
{
   m_resources.clear();
}
