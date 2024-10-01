//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/motion/skeleton.h"

#include <iostream>
#include <stdexcept>

#include "core/motion/motion.h"
#include "glm/gtx/quaternion.hpp"
#include "gtx/string_cast.hpp"

using namespace rayengine;

int Skeleton::AddBone(const std::string &name, const glm::vec3 &offset, int parent,
                      unsigned char channel_count, unsigned char position_order,
                      unsigned char rotation_order) {
    if (parent >= 0 && parent >= parents.size()) {
        throw std::runtime_error("Parent bone index out of range");
    }
    parents.push_back(parent);
    names.push_back(name);
    offsets.push_back(offset);
    position_orders.push_back(position_order);
    rotation_orders.push_back(rotation_order);
    children_indices.push_back(children.size());
    children_counts.push_back(0);
    depths.push_back(parent >= 0 ? depths[parent] + 1 : 0);
    if (channel_start.empty()) {
        channel_start.push_back(0);
    } else {
        channel_start.push_back(channel_start.back() + channel_counts.back());
    }
    channel_counts.push_back(channel_count);

    int bone_index = parents.size() - 1;

    // append to children
    if (parent >= 0 && parent < parents.size()) {
        children_counts[parent]++;
        for (int i = parent + 1; i < parents.size(); i++) {
            children_indices[i]++;
        }
        children.push_back(0);
        // shift
        int push_start = children_indices[parent] + children_counts[parent] - 1;
        for (int i = children.size() - 2; i >= push_start; i--) {
            children[i + 1] = children[i];
        }
        // insert
        children[push_start] = bone_index;
    }

    return bone_index;
}

std::vector<glm::vec3> Skeleton::ForwardKinematics(Motion &motion, int frame) const {
    std::vector<glm::vec3> positions;
    positions.resize(parents.size());
    const int max_depth = *std::max_element(depths.begin(), depths.end());
    for (int depth = max_depth; depth >= 0; depth--) {
        for (int joint = 0; joint < parents.size(); joint++) {
            if (depths[joint] == depth) {
                glm::vec3 offset = offsets[joint];
                glm::quat rotation = glm::quat(1, 0, 0, 0);
                unsigned int channel_index = channel_start[joint];
                if (position_orders[joint] != -1) {
                    offset = motion.GetPosition(frame, channel_index++, position_orders[joint]);
                }
                if (rotation_orders[joint] != -1) {
                    rotation = motion.GetRotation(frame, channel_index++, rotation_orders[joint]);
                }
                auto transform = glm::translate(glm::mat4(1), offset) * glm::mat4_cast(rotation);
                // apply to myself
                positions[joint] = offset;
                // apply to children
                int head = joint;
                while (true) {
                    // find next sibling
                    // if head has children, go to the first child
                    if (children_counts[head] > 0) {
                        head = children[children_indices[head]];
                    } else {
                        // if not go to parent until we find a sibling
                        while (true) {
                            const auto parent = parents[head];
                            if (parent == parents[joint]) {
                                head = parents[joint];
                                break;
                            }
                            const auto head_index = std::find(children.begin() + children_indices[parent],
                                                              children.begin() + children_indices[parent] +
                                                              children_counts[parent],
                                                              head) - children.begin();
                            if (head_index < children_counts[parent] - 1) {
                                head = children[children_indices[parent] + head_index + 1];
                                break;
                            } else {
                                head = parent;
                            }
                        }
                        if (head == parents[joint]) {
                            break;
                        }
                    }
                    if (head == 2) {
                        std::cout << "joint: " << joint << " - " << "head: " << head << std::endl;
                    }
                    positions[head] = glm::vec3(transform * glm::vec4(positions[head], 1));
                }
            }
        }
    }
    return positions;
}
