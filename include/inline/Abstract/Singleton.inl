template<typename ObjectType>
ObjectType* ze::Singleton<ObjectType>::s_instance = nullptr;

template<typename ObjectType>
ObjectType& ze::Singleton<ObjectType>::Instance()
{
   if (!s_instance)
      s_instance = new ObjectType;

   return *s_instance;
}

template<typename ObjectType>
void ze::Singleton<ObjectType>::Reset()
{
   if (s_instance)
      delete s_instance;

   s_instance = nullptr;
}
