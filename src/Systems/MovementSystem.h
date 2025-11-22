#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
#include "../ECS/ECS.h"

class MovementSystem : public System {
 public:
  MovementSystem() {
    // What entities is this componenet interested in
    // TODO: RequireComponenet<TransformComponenet>();
  }

  void Update() {
    // TODO:
    // Loop through all the entities
    // Update entity position based on velocity
  }
};

#endif
