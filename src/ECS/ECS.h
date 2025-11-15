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

class Component {
 private:
  int id;

 public:
  int GetId() const;
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
  Signature& GetComponentSignature() const;
};

class Registry {};

#endif
