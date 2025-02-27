#pragma once
#include"IComponent.h"
#include"Memory/MemoryChunkManager.h"
namespace SerenEngine {
	namespace ECS {
		constexpr size_t MAX_COMPONENT_PER_ARRAY = 500;

		class ComponentManager {

			class IComponentArray {
			public:
				virtual ~IComponentArray() = default;
				virtual bool HasComponent(EntityID) = 0;
				virtual void RemoveComponent(EntityID) = 0;
			protected:
				IComponentArray() = default;
			};
		public:
			template<typename T>
			class ComponentArray : public MemoryChunkManager<T, MAX_COMPONENT_PER_ARRAY>, public IComponentArray {
			public:
				ComponentArray() = default;
				~ComponentArray() {
				};
				template<typename... Args>
				T& AddComponent(EntityID id, class Coordinator* coordinator, Args&&... args) {
					BASE_CLASS_ASSERT(IComponent, T, "Add invalid component");
					T* component = NewObject(std::forward<Args>(args)...);
					component->SetOwnerID(id);
					component->SetID(GetUUID());
					component->SetCoordinator(coordinator);
					mComponentsMap[id] = component;
					return *component;
				}
				T& GetComponent(EntityID id) {
					BASE_CLASS_ASSERT(IComponent, T, "Get invalid component");
					ASSERT(mComponentsMap.count(id) && "Get non-existing component of entity");

					return *StaticCast<T*>(mComponentsMap.at(id));
				}
				virtual bool HasComponent(EntityID id) override {
					BASE_CLASS_ASSERT(IComponent, T, "Check invalid component");
					return mComponentsMap.count(id) != 0;
				}
				virtual void RemoveComponent(EntityID id) override {
					BASE_CLASS_ASSERT(IComponent, T, "Remove invalid component");
					ASSERT(HasComponent(id) && "Remove non-existing component");

					//FreeObject(mComponentsMap.at(id));
					mComponentsMap.erase(id);
				}
			private:
				std::unordered_map<EntityID, IComponent*> mComponentsMap;
			};
			using ComponentTypeMap = std::unordered_map<ComponentTypeID, IComponentArray*>;
		public:
			ComponentManager() : mComponentTypeMap() {}
			~ComponentManager() {
				for (auto& [typeId, componentArray] : mComponentTypeMap) {
					FREE_MEMORY(componentArray);
				}
				mComponentTypeMap.clear();
			}
			template<typename T>
			ComponentArray<T>& GetComponentArray() {
				BASE_CLASS_ASSERT(IComponent, T, "Get invalid component");
				ComponentTypeID typeID = T::GetStaticTypeID();
				ASSERT(mComponentTypeMap.count(typeID) && "Component array is not registered yet");
				return *StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID));
			}
			template<typename T, typename... Args>
			T& AddComponent(EntityID id, class Coordinator* coordinator, Args&&... args) {
				ComponentTypeID typeID = T::GetStaticTypeID();
				if (!mComponentTypeMap.count(typeID)) {
					IComponentArray* componentArray = new ComponentArray<T>(T::RunTimeType.GetTypeName());
					mComponentTypeMap[typeID] = componentArray;
				}
				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->AddComponent(id, coordinator, std::forward<Args>(args)...);
			}
			template<typename T>
			T& GetComponent(EntityID id) {
				ComponentTypeID typeID = T::GetStaticTypeID();
				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->GetComponent(id);
			}
			template<typename T>
			bool HasComponent(EntityID id) {
				ComponentTypeID typeID = T::GetStaticTypeID();
				if (!mComponentTypeMap.count(typeID)) {
					CORE_LOG_WARN("Check non-existing component {0}", T::RunTimeType.GetTypeName());
					return false;
				}
				return StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->HasComponent(id);
			}
			template<typename T>
			void RemoveComponent(EntityID id) {
				if (!HasComponent<T>(id)) return;
				ComponentTypeID typeID = T::GetStaticTypeID();
				StaticCast<ComponentArray<T>*>(mComponentTypeMap.at(typeID))->RemoveComponent(id);
			}
			void RemoveRelatedComponents(EntityID id) {
				for (auto& [_, componentArray] : mComponentTypeMap) {
					if (!componentArray->HasComponent(id)) continue;
					componentArray->RemoveComponent(id);
				}
				mComponentTypeMap.erase(id);
			}
		private:
			ComponentTypeMap mComponentTypeMap;
		};
	} 
} 