#pragma once

#include "utility/Types.h"
#include "utility/Logs.h"
#include "unordered_map"
#include "Components/TransformComponent.h"


struct IStorage {
    virtual ~IStorage() = default;
};

template<typename T>
struct Storage : IStorage {
    std::unordered_map<uint32_t, T> storage;

    template<typename... Args>
    T& add(uint32 id, Args&&... args) {
        return storage.emplace(id, T(std::forward<Args>(args)...)).first->second;
    }

    T& get(uint32 id) {
        return storage.at(id);
    }

    bool has(uint32 id) {
        return storage.find(id) != storage.end();
    }
};


class World
{
	private:
	std::unordered_map<runtime_index , Scope<IStorage>> _ComponentTree;
	size_t nextId = 0;

	template<typename T>
    Storage<T>& GetStorage() {
		auto typeId = runtime_index(typeid(T));
		auto it = _ComponentTree.find(typeId);
		if (it == _ComponentTree.end()) {
            _ComponentTree[typeId] = createScope<Storage<T>>();
        }
		
		return *static_cast<Storage<T>*>(_ComponentTree[typeId].get());  
	}

	public:
	Ent CreateEntity(){
		auto local = Ent{nextId++};
		add<TransformComponent>(local.id, Vec2(0,0), 0);
		if(nextId >= 2000){
			Error("Exceeding Expected Limit {}", 2000);
		}
		return local;
	}

	template<typename T , typename... Args>
    T& add(uint32_t id , Args&&... args) {
        return GetStorage<T>().add(id, std::forward<Args>(args)...);
    }

	template<typename T>
    T& get(uint32_t id) {
        return GetStorage<T>().get(id);
    }

	template<typename T>
    bool has(uint32_t id) const {
        auto typeId = runtime_index(typeid(T));
        auto it = _ComponentTree.find(typeId);
        if (it == _ComponentTree.end()) return false;
        auto* store = static_cast<Storage<T>*>(it->second.get());
        return store->has(id);
    }

	template<typename T>
	auto& all() {
    	return GetStorage<T>().storage; 
	}
};
