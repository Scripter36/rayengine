//
// Created by ikjun on 24. 9. 30.
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
        glm::vec3 getPosition() const {
            return position;
        }

        void setPosition(const glm::vec3 &position) {
            Node3D::position = position;
        }

        glm::quat getRotation() const {
            return rotation;
        }

        void setRotation(const glm::quat &rotation) {
            Node3D::rotation = rotation;
        }

        glm::vec3 getScale() const {
            return scale;
        }

        void setScale(const glm::vec3 &scale) {
            Node3D::scale = scale;
        }

        glm::mat4 getLocalTransform() const;

        glm::mat4 getGlobalTransform() const;

        glm::vec3 getGlobalPosition() const {
            return glm::vec3(getGlobalTransform()[3]);
        }

        glm::quat getGlobalRotation() const {
            return glm::quat_cast(getGlobalTransform());
        }
    };
}

#endif //NODE3D_H
