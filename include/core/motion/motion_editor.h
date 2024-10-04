//
// Created by 1350a on 2024-10-03.
//

#ifndef MOTION_EDITOR_H
#define MOTION_EDITOR_H

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace rayengine {
class Skeleton;
class Motion;
}  // namespace rayengine

using namespace rayengine;

namespace rayengine {

class MotionEditor {
public:
    static void Translate(Motion& motion, const Skeleton& skeleton, const glm::vec3& translation);
    static void Rotate(Motion& motion, const Skeleton& skeleton, const glm::quat& rotation);
    static void Scale(Motion& motion, Skeleton& skeleton, const glm::vec3& scale);
    static void Mirror(Motion& motion, const Skeleton& skeleton, const glm::vec3& axis);

protected:
    static glm::vec3 MirrorVector(const glm::vec3& vec, const glm::vec3& axis) {
        return vec - 2.0f * glm::dot(vec, axis) * axis;
    }
    static glm::quat MirrorQuaternion(const glm::quat& quat, const glm::vec3& axis) {
        return glm::angleAxis(-glm::angle(quat), MirrorVector(glm::axis(quat), axis));
    }
};

}  // namespace rayengine

#endif  // MOTION_EDITOR_H
