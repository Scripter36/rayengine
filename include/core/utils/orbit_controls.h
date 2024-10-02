//
// Created by ikjun on 24. 10. 2.
//

#ifndef ORBIT_CONTROLS_H
#define ORBIT_CONTROLS_H
#include "core/node3d.h"

namespace rayengine {

class OrbitControls : public Node3D {
public:
    OrbitControls(const float distance, NODE_CREATE_ARGS) : Node3D(), distance(distance) {}
    NODE_CREATE_METHOD(OrbitControls)

    void Init() override;
    void Process(float dt) override;

protected:
    float distance;
    float yaw = 0;
    float pitch = 0;
};

}  // namespace rayengine

#endif  // ORBIT_CONTROLS_H
