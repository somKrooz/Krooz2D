#pragma once

#include "Types.h"
#include "unordered_map"

class Entity{
    private:
    
    inline static uint32 _nextid = 0;
    Ent _localEnt;
    std::unordered_map<runtime_index , std::unordered_map<uint32 , Ref<void>>> _components;

    public:
    Entity(): _localEnt( Ent{_nextid++} ) {}

    uint32 Get(){
        return _localEnt._ID;
    }

    template<typename T ,typename... Args>
    bool AddComponent(uint32 id , Args&& ... args){
        auto local_comp = CreateRef<T>(std::forward<Args>(args)...);
        _components[typeid(T)][_localEnt._ID] = local_comp;
        return true;
    }

    template<typename T>
    T& GetComponent(uint32 id){
        auto outerIt = _components.find(typeid(T));
        if (outerIt == _components.end()) {
            throw std::runtime_error("Component type not found!");
        }

        auto& inner = outerIt->second;
        auto innerIt = inner.find(id);
        if(innerIt == inner.end()){
            throw std::runtime_error("Entity does not have this component!");
        }
        auto comp = std::static_pointer_cast<T>(innerIt->second);
        return *comp;
    }

};
