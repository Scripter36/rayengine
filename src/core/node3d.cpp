//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/node3d.h"

using namespace rayengine;

glm::mat4 Node3D::GetLocalTransform() const {
    const auto translationMatrix = glm::translate(glm::mat4(1.0f), position);
    const auto rotationMatrix = glm::mat4_cast(rotation);
    const auto scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Node3D::GetGlobalTransform() const {
    if (const auto p = parent.lock()) {
        if (const auto parent = dynamic_cast<Node3D *>(p.get())) {
            return parent->GetGlobalTransform() * GetLocalTransform();
        }
    }
    return GetLocalTransform();
}
