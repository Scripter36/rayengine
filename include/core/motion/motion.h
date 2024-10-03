//
// Created by Scripter36 on 24. 9. 30.
//

#ifndef MOTION_H
#define MOTION_H

#include <vector>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace rayengine {

class Motion {
public:
    int frame_count = 0;
    float frame_time = 0;
    std::vector<float> data;
    int channel_count = 0;

    Motion() = default;

    [[nodiscard]] glm::vec3 GetPosition(int frame, int channel_index, char order) const;
    [[nodiscard]] glm::quat GetRotation(int frame, int channel_index, char order) const;
    void SetPosition(int frame, int channel_index, char order, const glm::vec3& position);
    void SetRotation(int frame, int channel_index, char order, const glm::quat& rotation);
};

}  // namespace rayengine

#endif  // MOTION_H
