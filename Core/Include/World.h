#pragma once

#include "Types.h"
#include "unordered_map"

namespace Krooz2D{

	class World {
	private:

		inline static uint32 _nextid = 0;
		Ent _localEnt;
		std::unordered_map<runtime_index , std::unordered_map<uint32 , Ref<void>>> _components;

	public:
		World() = default;
		
		Ent CreateEntity() {
			Ent entity{ _nextid++ };
			return entity;
		}

		template<typename T ,typename... Args>
		bool AddComponent(uint32 id , Args&& ... args){
			auto local_comp = CreateRef<T>(std::forward<Args>(args)...);
			_components[typeid(T)][id] = local_comp;
			return true;
		}
		template<typename T>
		bool HasComponentId(uint32 id){
			auto outerIt = _components.find(typeid(T));
			if(outerIt == _components.end())
			{
				return false;
			}
			auto& inner = outerIt->second;
			auto innerIt = inner.find(id);
			if(innerIt == inner.end()){
				return false;
			}
			return true;
		}


		template<typename T>
		bool HasComponent(){
			auto outerIt = _components.find(typeid(T));
			if (outerIt == _components.end()) {
				return false;
				throw std::runtime_error("Component type not found!");
			}
			
			return true;
		}

		template<typename T>
		Ref<T> GetComponent(uint32 id){
			auto outerIt = _components.find(typeid(T));
			if (outerIt == _components.end()) {
				throw std::runtime_error("Component type not found!");
			}

			auto& inner = outerIt->second;
			auto innerIt = inner.find(id);
			if(innerIt == inner.end()){
				throw std::runtime_error("does not have this component!");
			}
			auto comp = std::static_pointer_cast<T>(innerIt->second);
			return comp;
		}

		template<typename T>
		std::vector<uint32> GetAllComponentsOfTypeID() {
				std::vector<uint32> result;

				auto outerIt = _components.find(typeid(T));
				if (outerIt != _components.end()) {
					for (auto& [id, comp] : outerIt->second) {
						result.push_back(id);
					}
				}
				return result;
		}

		template<typename T>
		std::vector<Ref<T>> GetAllComponentsOfType() {
			std::vector<Ref<T>> result;
			auto outerIt = _components.find(typeid(T));
			if (outerIt != _components.end()) {
				for (auto& [id, comp] : outerIt->second) {
					result.push_back(std::static_pointer_cast<T>(comp));
				}
			}
			return result;
		}
	};
}


