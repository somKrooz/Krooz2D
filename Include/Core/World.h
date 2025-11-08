#pragma once

#include "utility/Types.h"
#include "utility/Logs.h"
#include "unordered_map"
#include "unordered_set"
#include "Components/TransformComponent.h"



struct IStorage {
    virtual ~IStorage() = default;
	virtual void erase(uint32_t id) = 0; 
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
	
	void erase(uint32 id) override {
        storage.erase(id);
    }
	
};


class World
{
private:
    std::unordered_map<runtime_index, Scope<IStorage>> _ComponentTree;
    std::unordered_set<uint32_t> _activeEntities;  // Track active entities
    std::vector<uint32_t> _entitiesToDestroy;
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
    Ent CreateEntity() {
        auto local = Ent{nextId++};
        _activeEntities.insert(local.id);  // Track entity
        add<TransformComponent>(local.id, Vec2(0,0), 0);
        if(nextId >= 2000) {
            Error("Exceeding Expected Limit {}", 2000);
        }
        return local;
    }

    template<typename T, typename... Args>
    T& add(uint32_t id, Args&&... args) {
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

    bool IsEntityActive(uint32_t id) const {
        return _activeEntities.find(id) != _activeEntities.end();
    }

        void DestroyEntity(uint32_t id) {
        if (_activeEntities.find(id) == _activeEntities.end()) {
            return;  
        }

        for (auto& [typeIdx, storage] : _ComponentTree) {
            storage->erase(id);   
        }
        _activeEntities.erase(id);
    }

    void MarkForDestruction(uint32_t id) {
        if (IsEntityActive(id)) {
            _entitiesToDestroy.push_back(id);
        } 
    }

    void ProcessDestroyQueue() {
        for (auto id : _entitiesToDestroy) {
            DestroyEntity(id);
        }
        _entitiesToDestroy.clear();
    }
};

