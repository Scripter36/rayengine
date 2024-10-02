//
// Created by 1350a on 2024-10-01.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "core/node3d.h"

namespace rayengine {

class Sphere : public Node3D {
public:
    static shared_ptr<Sphere> Create(const glm::vec3 color = {1, 1, 1}, NODE_CREATE_ARGS) {
        NODE_CREATE(node, Sphere);
        node->color = color;
        return node;
    }

    void Draw() override;

protected:
    glm::vec3 color = {1, 1, 1};
};

}  // namespace rayengine

#endif  // SPHERE_H
