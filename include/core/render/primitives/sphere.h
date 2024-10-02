//
// Created by 1350a on 2024-10-01.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "core/node3d.h"

namespace rayengine {

class Sphere : public Node3D {
public:
    NODE_CREATE_METHOD(Sphere)

    void Draw() override;

    Sphere(const glm::vec3 color) : Node3D(), color(color) {}
protected:
    glm::vec3 color = {1, 1, 1};
};

}  // namespace rayengine

#endif  // SPHERE_H
