//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/node3d.h"

#include "core/render/camera_node.h"
#include "core/scene_tree.h"
#include "gtc/type_ptr.hpp"
#include "rlgl.h"

using namespace rayengine;

void Node3D::Draw() {
    if (!SceneTree::bIs3DMode) {
        if (const auto camera = Camera3D::GetMainCamera()) {
            SceneTree::bIs3DMode = true;
            BeginMode3D(*camera);
        } else {
            return;
        }
    }
    rlPushMatrix();
    rlMultMatrixf(glm::value_ptr(GetGlobalTransform()));
}
void Node3D::PostDraw() {
    rlPopMatrix();
}

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
