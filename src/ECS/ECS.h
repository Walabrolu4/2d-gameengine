#ifndef ECS_H
#define ECS_H
#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENETS = 32;

///////////////////////////
/// Signature
///////////////////////////
/// We use a bitset to keep track of which components an entity has,
/// and also helps keep track of which entities a system is interested in
///////////////////////////

typedef std::bitset<MAX_COMPONENETS> Signature;

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

class Entity {
 private:
  int id;

 public:
  Entity(int id) : id(id) {};
  int GetId() const;
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

class Registry {};

template <typename TComponent>
void System::RequireComponent() {
  const auto componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

#endif
