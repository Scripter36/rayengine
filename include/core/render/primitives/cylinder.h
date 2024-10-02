//
// Created by ikjun on 24. 10. 2.
//

#ifndef CYLINDER_H
#define CYLINDER_H
#include "core/node3d.h"

namespace rayengine {

class Cylinder : public Node3D {
public:
    NODE_CREATE_METHOD(Cylinder)

    void Draw() override;

    Cylinder(const glm::vec3 color) : Node3D(), color(color) {}

protected:
    glm::vec3 color;
};

}  // namespace rayengine

#endif  // CYLINDER_H
