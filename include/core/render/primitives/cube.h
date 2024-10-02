//
// Created by Scripter36 on 2024-09-28.
//

#ifndef CUBE_H
#define CUBE_H
#include "core/node3d.h"

namespace rayengine {

class Cube : public Node3D {
public:
    NODE_CREATE_METHOD(Cube)

    void Draw() override;

    Cube(const glm::vec3 color) : Node3D(), color(color) {}

protected:
    glm::vec3 color = {1, 1, 1};
};

}  // namespace rayengine

#endif  // CUBE_H
