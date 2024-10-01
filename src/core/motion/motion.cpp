//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/motion/motion.h"

#include <stdexcept>

#include "core/motion/skeleton.h"

glm::vec3 rayengine::Motion::GetPosition(const int frame, const int channel_index, const char order) const {
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

glm::quat rayengine::Motion::GetRotation(const int frame, const int channel_index, const char order) const {
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
