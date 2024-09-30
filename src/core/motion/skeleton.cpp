//
// Created by Scripter36 on 24. 9. 30.
//

#include "core/motion/skeleton.h"

int rayengine::Skeleton::AddBone(const std::string &name, const glm::vec3 &offset, int parent,
                                 unsigned char channel_count, unsigned char position_order,
                                 unsigned char rotation_order) {
    parents.push_back(parent);
    names.push_back(name);
    offsets.push_back(offset);
    channel_counts.push_back(channel_count);
    position_orders.push_back(position_order);
    rotation_orders.push_back(rotation_order);
    children_indices.push_back(children.size());
    children_counts.push_back(0);

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
        for (int i = children.size() - 1; i >= push_start; i--) {
            children[i + 1] = children[i];
        }
        // insert
        children[push_start] = bone_index;
    }

    return bone_index;
}
