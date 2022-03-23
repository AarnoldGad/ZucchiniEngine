template<typename ResourceType>
std::unordered_set<std::string> ze::ResourceManager<ResourceType>::s_searchPaths =
   { std::filesystem::current_path().lexically_normal().string() };

template<typename ResourceType>
std::unordered_map<std::string, std::unique_ptr<ze::ResourceHolder<ResourceType> > > ze::ResourceManager<ResourceType>::s_resources{};

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::AddSearchPath(std::filesystem::path const& dir)
{
   if (!std::filesystem::is_directory(dir)) return (void) ZE_LOG_ERROR("Resource search path is not a directory : {}", dir);

   s_searchPaths.insert(dir.lexically_normal().string());
}

template<typename ResourceType>
inline std::unordered_set<std::string> const& ze::ResourceManager<ResourceType>::GetSearchPaths() noexcept
{
   return s_searchPaths;
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::RemoveSearchPath(std::filesystem::path const& dir)
{
   s_searchPaths.erase(dir.lexically_normal().string());
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::ClearSearchPaths()
{
   s_searchPaths.clear();
}

template<typename ResourceType>
inline ze::ResourceLoader<ResourceType>* ze::ResourceManager<ResourceType>::Add(std::string const& id)
{
   auto result = ResourceManager<ResourceType>::s_resources.try_emplace(id, std::make_unique<ResourceHolder<ResourceType> >());
   return result.first->second->loader();
}

template<typename ResourceType>
inline ze::ResourceHolder<ResourceType>* ze::ResourceManager<ResourceType>::Get(std::string const& id)
{
   auto resource = s_resources.find(id);
   return resource != s_resources.end() ? resource->second.get() : nullptr;
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::Release(std::string const& id)
{
   s_resources.erase(id);
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::ReleaseAll() noexcept
{
   s_resources.clear();
}

