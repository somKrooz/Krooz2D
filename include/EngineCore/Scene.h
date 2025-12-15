#pragma once
#include "Utility/Types.h"


struct Container {
	virtual ~Container() = default;
	virtual void erase(u32 id) = 0;
};

template<typename T>
struct Storage : Container {
	std::unordered_map<u32, T> storage;

	template<typename... Args>
	T& add(u32 id, Args&&... args) {
		return storage.emplace(id, T(std::forward<Args>(args)...)).first->second;
	}

	T& get(u32 id) {
		return storage.at(id);
	}

	bool has(u32 id) {
		return storage.find(id) != storage.end();
	}

	void erase(u32 id) override {
		storage.erase(id);
	}

};

class Scene
{
private:
	umap<runtime_index, scope<Container>> tree;
	uset<u32> active;
	uset<u32> dirty;
	inline static u32 next = 0;

	template <typename T>
	Storage<T>& GetStorage() {
		auto typeId = runtime_index(typeid(T));
		auto it = tree.find(typeId);
		if (it == tree.end())
		{
			tree[typeId] = createScope<Storage<T>>();
		}
		return *static_cast<Storage<T> *>(tree[typeId].get());
	}


public:
	ent create()
	{
		auto local = next++;
		active.insert(local);
		return local;
	}

	template <typename T, typename... Args>
	T& add(u32 id, Args &&...args)
	{
		return GetStorage<T>().add(id, std::forward<Args>(args)...);
	}
	
	template <typename T>
	bool has(u32 id){
		return (GetStorage<T>().has(id));
	} 

	template <typename T>
	T& get(u32 id)
	{
		return GetStorage<T>().get(id);
	}

	bool IsEntityActive(u32 id) const
	{
		return active.find(id) != active.end();
	}

	template <typename T>
	auto& all()
	{
		return GetStorage<T>().storage;
	}

	void MarkForDestruction(u32 id)
	{
		if (IsEntityActive(id)) {
			dirty.insert(id);
		}
	}

	void DestroyEntity(u32 id)
	{
		for (auto& [typeIdx, storage] : tree)
		{
			storage->erase(id);
		}
		active.erase(id);
	}

	void ProcessDestroyQueue()
	{
		for (auto id : dirty)
		{
			DestroyEntity(id);
		}
		dirty.clear();
	}
};

