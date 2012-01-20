#ifndef UTILITIES_REGISTRY_HPP
#define UTILITIES_REGISTRY_HPP

#include <map>

namespace Utilities {

template <class TKey, class TValue>
struct Registry
{
	 static std::map<TKey,TValue>& registry()
	 {
		 static std::map<TKey,TValue> s;
		 return s;
	 }

	 static const TValue& query(const TKey &key, const TValue &defaultValue)
	 {
		 auto it = registry().find(key);
		 if (it == registry().end())
			 return defaultValue;
		 else
			 return it->second;
	 }

	 static const TValue& get(const TKey &key)
	 {
		 return registry()[key];
	 }

	 static void registerItem(const TKey &key, const TValue &value)
	 {
		 registry().insert(std::make_pair(key,value));
	 }
};

} // namespace Utilities

#define REGISTER_ITEM(type,id,item) \
	static int _reg_item_##item() { \
	Utilities::Registry<std::string,type>::registerItem(id,item); \
	return 0; } \
	static int _var_reg_item_##item = _reg_item_##item(); 

#endif // UTILITIES_REGISTRY_HPP