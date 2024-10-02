//
// Created by Scripter36 on 24. 9. 30.
//

#ifndef SKELETON_H
#define SKELETON_H
#include <string>
#include <vector>

#include "glm/glm.hpp"

namespace rayengine {

class Motion;
#define ORDER_XYZ 0
#define ORDER_XZY 1
#define ORDER_YXZ 2
#define ORDER_YZX 3
#define ORDER_ZXY 4
#define ORDER_ZYX 5

class Skeleton {
public:
    std::vector<glm::vec3> offsets;
    std::vector<int> parents;
    std::vector<int> children_indices;
    std::vector<int> children_counts;
    std::vector<int> children;
    std::vector<std::string> names;
    std::vector<char> channel_counts;
    std::vector<char> position_orders;
    std::vector<char> rotation_orders;
    std::vector<unsigned int> depths;
    std::vector<unsigned int> channel_start;

    Skeleton() = default;

    int AddBone(const std::string &name, const glm::vec3 &offset, int parent, unsigned char channel_count,
                unsigned char position_order, unsigned char rotation_order);

    int GetNextBoneIndex(int bone_index, int root) const;

    [[nodiscard]] std::vector<glm::vec3> ForwardKinematics() const;
    [[nodiscard]] std::vector<glm::vec3> ForwardKinematics(const Motion &motion, int frame) const;

    [[nodiscard]] size_t size() const { return parents.size(); }
};

}  // namespace rayengine

#endif  // SKELETON_H
