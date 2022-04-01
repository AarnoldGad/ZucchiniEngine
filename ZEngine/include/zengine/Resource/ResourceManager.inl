template<typename ResourceType>
std::unordered_set<std::string> ze::ResourceManager<ResourceType>::s_searchPaths =
   { std::filesystem::current_path().lexically_normal().string() };

template<typename ResourceType>
inline void ze::ResourceDeleter<ResourceType>::operator()(ResourceType* resource) const
{
   ResourceLoader<ResourceType>::Unload(resource);
   delete resource;
}

template<typename ResourceType>
std::unordered_map<std::string, std::unique_ptr<ResourceType, ze::ResourceDeleter<ResourceType> > >
ze::ResourceManager<ResourceType>::s_resources{};

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
inline void ze::ResourceManager<ResourceType>::ClearSearchPaths() noexcept
{
   s_searchPaths.clear();
}

template<typename ResourceType>
inline std::optional<std::filesystem::path> ze::ResourceManager<ResourceType>::FindFile(std::filesystem::path const& file)
{
   auto const& searchPaths = GetSearchPaths();
   return ze::FileUtils::Search(searchPaths, file);
}

template<typename ResourceType>
template<typename... Args>
inline ResourceType* ze::ResourceManager<ResourceType>::Load(std::string const& id, Args&&... args)
{
   auto result = ResourceManager<ResourceType>::s_resources.try_emplace(id, nullptr);
   result.first->second.reset(ResourceLoader<ResourceType>::Load(std::forward<Args>(args)...));

   return result.first->second.get();
}

template<typename ResourceType>
template<typename... Args>
inline ResourceType* ze::ResourceManager<ResourceType>::Reload(std::string const& id, Args&&... args)
{
   ResourceType* resource = Get(id);
   if (!resource) return nullptr;

   ResourceLoader<ResourceType>::Reload(resource, std::forward<Args>(args)...);
   return resource;
}

template<typename ResourceType>
inline ResourceType* ze::ResourceManager<ResourceType>::Get(std::string const& id)
{
   auto resource = s_resources.find(id);
   return resource != s_resources.end() ? resource->second.get() : nullptr;
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::Unload(std::string const& id)
{
   s_resources.erase(id);
}

template<typename ResourceType>
inline void ze::ResourceManager<ResourceType>::UnloadAll() noexcept
{
   s_resources.clear();
}

