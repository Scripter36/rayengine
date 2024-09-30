//
// Created by Scripter36 on 24. 9. 30.
//

#ifndef NODE3D_H
#define NODE3D_H

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "core/node.h"
#include "glm/gtx/quaternion.hpp"

namespace rayengine {
    class Node3D : public Node {
        // Transform
    private:
        glm::vec3 position = {0, 0, 0};
        glm::quat rotation = {1, 0, 0, 0};
        glm::vec3 scale = {1, 1, 1};

    public:
        glm::vec3 GetPosition() const {
            return position;
        }

        void SetPosition(const glm::vec3 &position) {
            Node3D::position = position;
        }

        glm::quat GetRotation() const {
            return rotation;
        }

        void SetRotation(const glm::quat &rotation) {
            Node3D::rotation = rotation;
        }

        glm::vec3 GetScale() const {
            return scale;
        }

        void SetScale(const glm::vec3 &scale) {
            Node3D::scale = scale;
        }

        glm::mat4 GetLocalTransform() const;

        glm::mat4 GetGlobalTransform() const;

        glm::vec3 GetGlobalPosition() const {
            return glm::vec3(GetGlobalTransform()[3]);
        }

        glm::quat GetGlobalRotation() const {
            return glm::quat_cast(GetGlobalTransform());
        }
    };
}

#endif //NODE3D_H
