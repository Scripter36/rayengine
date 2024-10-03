//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/motion/motion.h"

#include <stdexcept>

#include "core/motion/skeleton.h"
#include "glm/gtx/euler_angles.hpp"

using namespace rayengine;

glm::vec3 Motion::GetPosition(const int frame, const int channel_index, const char order) const {
    const int index = frame * channel_count + 3 * channel_index;
    switch (order) {
        case ORDER_XYZ:
            return {data[index], data[index + 1], data[index + 2]};
        case ORDER_XZY:
            return {data[index], data[index + 2], data[index + 1]};
        case ORDER_YXZ:
            return {data[index + 1], data[index], data[index + 2]};
        case ORDER_YZX:
            return {data[index + 1], data[index + 2], data[index]};
        case ORDER_ZXY:
            return {data[index + 2], data[index], data[index + 1]};
        case ORDER_ZYX:
            return {data[index + 2], data[index + 1], data[index]};
        default:
            throw std::runtime_error("Invalid position order");
    }
}

glm::quat Motion::GetRotation(const int frame, const int channel_index, const char order) const {
    const int index = frame * channel_count + 3 * channel_index;
    constexpr float DEG2RAD = 3.14159265358979323846 / 180.0;
    switch (order) {
        case ORDER_XYZ:
            return glm::quat(glm::vec3(data[index] * DEG2RAD, 0, 0)) *
                   glm::quat(glm::vec3(0, data[index + 1] * DEG2RAD, 0)) *
                   glm::quat(glm::vec3(0, 0, data[index + 2] * DEG2RAD));
        case ORDER_XZY:
            return glm::quat(glm::vec3(data[index] * DEG2RAD, 0, 0)) *
                   glm::quat(glm::vec3(0, 0, data[index + 1] * DEG2RAD)) *
                   glm::quat(glm::vec3(0, data[index + 2] * DEG2RAD, 0));
        case ORDER_YXZ:
            return glm::quat(glm::vec3(0, data[index] * DEG2RAD, 0)) *
                   glm::quat(glm::vec3(data[index + 1] * DEG2RAD, 0, 0)) *
                   glm::quat(glm::vec3(0, 0, data[index + 2] * DEG2RAD));
        case ORDER_YZX:
            return glm::quat(glm::vec3(0, data[index] * DEG2RAD, 0)) *
                   glm::quat(glm::vec3(0, 0, data[index + 1] * DEG2RAD)) *
                   glm::quat(glm::vec3(data[index + 2] * DEG2RAD, 0, 0));
        case ORDER_ZXY:
            return glm::quat(glm::vec3(0, 0, data[index] * DEG2RAD)) *
                   glm::quat(glm::vec3(data[index + 1] * DEG2RAD, 0, 0)) *
                   glm::quat(glm::vec3(0, data[index + 2] * DEG2RAD, 0));
        case ORDER_ZYX:
            return glm::quat(glm::vec3(0, 0, data[index] * DEG2RAD)) *
                   glm::quat(glm::vec3(0, data[index + 1] * DEG2RAD, 0)) *
                   glm::quat(glm::vec3(data[index + 2] * DEG2RAD, 0, 0));
        default:
            throw std::runtime_error("Invalid rotation order");
    }
}

void Motion::SetPosition(int frame, int channel_index, char order, const glm::vec3& position) {
    const int index = frame * channel_count + 3 * channel_index;
    switch (order) {
        case ORDER_XYZ:
            data[index] = position.x;
            data[index + 1] = position.y;
            data[index + 2] = position.z;
            break;
        case ORDER_XZY:
            data[index] = position.x;
            data[index + 2] = position.y;
            data[index + 1] = position.z;
            break;
        case ORDER_YXZ:
            data[index + 1] = position.x;
            data[index] = position.y;
            data[index + 2] = position.z;
            break;
        case ORDER_YZX:
            data[index + 1] = position.x;
            data[index + 2] = position.y;
            data[index] = position.z;
            break;
        case ORDER_ZXY:
            data[index + 2] = position.x;
            data[index] = position.y;
            data[index + 1] = position.z;
            break;
        case ORDER_ZYX:
            data[index + 2] = position.x;
            data[index + 1] = position.y;
            data[index] = position.z;
            break;
        default:
            throw std::runtime_error("Invalid position order");
    }
}

void Motion::SetRotation(int frame, int channel_index, char order, const glm::quat& rotation) {
    const int index = frame * channel_count + 3 * channel_index;
    constexpr float RAD2DEG = 180.0 / 3.14159265358979323846;
    float pitch, yaw, roll;
    switch (order) {
        case ORDER_XYZ:
            glm::extractEulerAngleXYZ(glm::mat4_cast(rotation), pitch, yaw, roll);
            data[index] = pitch * RAD2DEG;
            data[index + 1] = yaw * RAD2DEG;
            data[index + 2] = roll * RAD2DEG;
            break;
        case ORDER_XZY:
            glm::extractEulerAngleXZY(glm::mat4_cast(rotation), pitch, yaw, roll);
            data[index] = pitch * RAD2DEG;
            data[index + 2] = yaw * RAD2DEG;
            data[index + 1] = roll * RAD2DEG;
            break;
        case ORDER_YXZ:
            glm::extractEulerAngleYXZ(glm::mat4_cast(rotation), pitch, yaw, roll);
            data[index + 1] = pitch * RAD2DEG;
            data[index] = yaw * RAD2DEG;
            data[index + 2] = roll * RAD2DEG;
            break;
        case ORDER_YZX:
            glm::extractEulerAngleYZX(glm::mat4_cast(rotation), pitch, yaw, roll);
            data[index + 1] = pitch * RAD2DEG;
            data[index + 2] = yaw * RAD2DEG;
            data[index] = roll * RAD2DEG;
            break;
        case ORDER_ZXY:
            glm::extractEulerAngleZXY(glm::mat4_cast(rotation), pitch, yaw, roll);
            data[index + 2] = pitch * RAD2DEG;
            data[index] = yaw * RAD2DEG;
            data[index + 1] = roll * RAD2DEG;
            break;
        case ORDER_ZYX:
            glm::extractEulerAngleZYX(glm::mat4_cast(rotation), roll, yaw, pitch);
            data[index + 2] = pitch * RAD2DEG;
            data[index + 1] = yaw * RAD2DEG;
            data[index] = roll * RAD2DEG;
            break;
        default:
            throw std::runtime_error("Invalid rotation order");
    }
}
