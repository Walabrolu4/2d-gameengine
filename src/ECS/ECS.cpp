#include "ECS.h"

#include <string>

#include "../Logger/Logger.h"

int IComponent::nextId = 0;

// ENTITY//
int Entity::GetId() const { return id; }

// SYSTEM//
void System::AddEntityToSystem(Entity entity) {
  // add entity to entities vector
  entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
  entities.erase(
      std::remove_if(entities.begin(), entities.end(),
                     [&entity](Entity other) { return entity == other; }),
      entities.end());
}

std::vector<Entity> System::GetSystemEntites() const { return entities; }

const Signature& System::GetComponentSignature() const {
  return componentSignature;
}

// REGISTERY//
Entity Registry::CreateEntity() {
  int entityId = numEntities++;
  if (entityId >= entityComponentSignatures.size()) {
    entityComponentSignatures.resize(entityId + 1);
  }
  Entity entity(entityId);
  Logger::Log("Entity created with Id" + std::to_string(numEntities));
  entitiesToBeAdded.insert(entity);
  return entity;
}

void Registry::Update() {
  // Add entites that are watiting to be created
  // Remove entites that are waiting to be destroyed
}

void Registry::AddEntityToSystems(Entity entity) {
  const int entityId = entity.GetId();
  Signature entityComponentSignature = entityComponentSignatures[entityId];

  for (auto& system : systems) {
    const auto& systemComponentSignature =
        system.second->GetComponentSignature();

    // Match entity.ComponentSignature <--> systemComponenetSignature;
    bool isInterested = (entityComponentSignature & systemComponentSignature) ==
                        systemComponentSignature;

    if (isInterested) {
      // Add entity to system
      system.second->AddEntityToSystem(entity);
    }
  }
}

// COMPONENT//
