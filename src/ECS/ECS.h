#ifndef ECS_H
#define ECS_H
#include <bitset>
#include <set>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

const unsigned int MAX_COMPONENETS = 32;

///////////////////////////
/// Signature
///////////////////////////
/// We use a bitset to keep track of which components an entity has,
/// and also helps keep track of which entities a system is interested in
///////////////////////////

typedef std::bitset<MAX_COMPONENETS> Signature;

class Entity {
 private:
  int id;

 public:
  Entity(int id) : id(id) {};
  Entity(const Entity& entity) = default;
  int GetId() const;

  Entity& operator=(const Entity& other) = default;
  bool operator==(const Entity& other) const { return id == other.GetId(); };
  bool operator!=(const Entity& other) const { return id != other.GetId(); };
};

class System {
 private:
  Signature componentSignature;
  std::vector<Entity> entities;

 public:
  System() = default;
  ~System() = default;
  void AddEntityToSystem(Entity entity);
  void RemoveEntityFromSystem(Entity entity);
  std::vector<Entity> GetSystemEntites() const;
  const Signature& GetComponentSignature() const;

  // Defines the componenet type that enteties must have to considered by the
  // system.
  template <typename TComponent>
  void RequireComponent();
};

struct IComponent {
 protected:
  static int nextId;
};
// Used to assign a uniqe id to a component type
template <typename T>
class Component : public IComponent {
  static int GetId() {
    static auto id = nextId++;
    return id;
  }
};

template <typename TComponent>
void System::RequireComponent() {
  const auto componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

class IPool {
 public:
  virtual ~IPool() {}
};

template <typename T>
class Pool : IPool {
 private:
  std::vector<T> data;

 public:
  Pool(int size = 100) { data.resize(size); }
  virtual ~Pool() = default;

  bool isEmpty() const { return data.empty(); }
  int GetSize() const { return data.size(); }
  void Resize(int n) { data.resize(n); }
  void Clear() { data.clear(); }
  void Add(T object) { data.push_back(object); }
  void Set(int index, T object) { data[index] = object; }
  T& Get(int index) { return static_cast<T>(data[index]); }
  T& operator[](unsigned int index) { return data[index]; }
};

// It is a world manager.
class Registry {
 private:
  int numEntities = 0;
  //[Vector index = component type id]
  // [Pool index = entity id]
  std::vector<IPool*> componentPools;
  //[vector index = entity id]
  std::vector<Signature> entityComponentSignatures;
  std::unordered_map<std::type_index, System*> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;

 public:
  Registry() = default;
  Entity CreateEntity();
  void KillEntity(Entity entity);
  void Update();

  // Component Management
  template <typename TComponent, typename... TArgs>
  void AddComponent(Entity entity, TArgs&&... args);

  template <typename TComponent>
  void RemoveComponent(Entity entity);

  template <typename TComponent>
  bool HasComponent(Entity entity) const;

  template <typename TComponent>
  TComponent& GetComponent(Entity entity) const;

  // System Management
  template <typename TSystem, typename... TArgs>
  void AddSystem(TArgs&&... args);

  template <typename TSystem>
  void RemoveSystem();

  template <typename TSystem>
  bool HasSystem() const;

  template <typename TSystem>
  TSystem& GetSystem() const;

  void AddEntityToSystems(Entity entity);

  //  Entity Management
  //  CreateEntity()
  //  DestroyEntity()
};

// Component Implementations
template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args) {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  // If the component pool isn't big enough resize.
  if (componentId > componentPools.size()) {
    componentPools.resize(componentId + 1, nullptr);
  }

  // If the compoent Pool is empty add a new Pool
  if (!componentPools[componentId]) {
    Pool<TComponent>* newComponentPool = new Pool<TComponent>();
    componentPools[componentId] = newComponentPool;
  }

  Pool<TComponent>* componentPool =
      Pool<TComponent>(componentPools[componentId]);

  // If that specific componentPool is too small then resize it to have the
  // current numEntities
  if (entityId >= componentPool->GetSize()) {
    componentPool->Resize(numEntities);
  }

  // create a new component and "forward" the arguments to it.
  TComponent newComponent(std::forward<TArgs>(args)...);

  // Finally set that component to "On" in the entities Component signatures
  entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();
  return entityComponentSignatures[entityId].test(componentId);
}

// System Implementations
template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args) {
  TSystem* newSystem(new TSystem(std::forward<TArgs>(args)...));
  systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem() {
  TSystem system = systems.find(std::type_index(typeid(TSystem)));
  systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const {
  return false;
  TSystem system = system.find(std::type_index(typeid(TSystem)));

  // If we didn't find the system them it should return the end pointer.
  return system != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const {
  TSystem system = systems.find(std::type_index(typeid(TSystem)));
  return *(std::static_pointer_cast<TSystem>(system->second));
}

#endif
