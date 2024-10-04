//
// Created by 1350a on 2024-10-03.
//

#include "core/motion/motion_editor.h"

#include <iostream>
#include <set>

#include "core/motion/motion.h"
#include "core/motion/skeleton.h"

void MotionEditor::Translate(Motion& motion, const Skeleton& skeleton, const glm::vec3& translation) {
    if (skeleton.size() == 0) {
        return;
    }

#pragma omp parallel for default(none) shared(motion, skeleton, translation)
    for (int t = 0; t < motion.frame_count; t++) {
        if (skeleton.position_orders[0] != -1) {
            auto root_position = motion.GetPosition(t, 0, skeleton.position_orders[0]);
            root_position += translation;
            motion.SetPosition(t, 0, skeleton.position_orders[0], root_position);
        }
    }
}

void MotionEditor::Rotate(Motion& motion, const Skeleton& skeleton, const glm::quat& rotation) {
    if (skeleton.size() == 0) {
        return;
    }

#pragma omp parallel for default(none) shared(motion, skeleton, translation)
    for (int t = 0; t < motion.frame_count; t++) {
        const int channel_index = skeleton.position_orders[0] == -1 ? 0 : 1;
        if (skeleton.rotation_orders[0] != -1) {
            auto root_rotation = motion.GetRotation(t, channel_index, skeleton.rotation_orders[0]);
            motion.SetRotation(t, channel_index, skeleton.rotation_orders[0], rotation * root_rotation);
        }
    }
}

void MotionEditor::Scale(Motion& motion, Skeleton& skeleton, const glm::vec3& scale) {
    // 1. scale the skeleton
    for (int i = 0; i < skeleton.size(); i++) {
        skeleton.offsets[i] *= scale;
    }

    // 2. scale the motion
    for (int t = 0; t < motion.frame_count; t++) {
        for (int i = 0; i < skeleton.size(); i++) {
            const auto channel_index = skeleton.channel_start[i];
            if (skeleton.position_orders[i] != -1) {
                auto position = motion.GetPosition(t, channel_index, skeleton.position_orders[i]);
                position *= scale;
                motion.SetPosition(t, channel_index, skeleton.position_orders[i], position);
            }
        }
    }
}

void MotionEditor::Mirror(Motion& motion, const Skeleton& skeleton, const glm::vec3& axis) {
    if (skeleton.size() == 0) {
        return;
    }

    glm::vec3 root_position = {0, 0, 0};
    if (skeleton.position_orders[0] != -1) {
        root_position = motion.GetPosition(0, 0, skeleton.position_orders[0]);
    }

    auto symmetric_pairs = std::vector<std::pair<int, int>>();
    auto found_pairs = std::set<int>();
    for (int i = 0; i < skeleton.size(); i++) {
        if (found_pairs.contains(i)) continue;

        auto name = skeleton.names[i];
        if (name.find("Left") != std::string::npos) {
            auto right_name = name;
            right_name.replace(right_name.find("Left"), 4, "Right");
            for (int j = 0; j < skeleton.size(); j++) {
                if (skeleton.names[j] == right_name) {
                    symmetric_pairs.emplace_back(i, j);
                    found_pairs.insert(i);
                    found_pairs.insert(j);
                    break;
                }
            }
        } else if (name.find("Right") != std::string::npos) {
            auto left_name = name;
            left_name.replace(left_name.find("Right"), 5, "Left");
            for (int j = 0; j < skeleton.size(); j++) {
                if (skeleton.names[j] == left_name) {
                    symmetric_pairs.emplace_back(i, j);
                    found_pairs.insert(i);
                    found_pairs.insert(j);
                    break;
                }
            }
        } else {
            symmetric_pairs.emplace_back(i, i);
            found_pairs.insert(i);
        }
    }


#pragma omp parallel for default(none) shared(motion, skeleton, root_position, axis, symmetric_pairs)
    for (int t = 0; t < motion.frame_count; t++) {
        for (const auto [i, j] : symmetric_pairs) {
            auto channel_index = skeleton.channel_start[i];
            auto channel_index_mirror = skeleton.channel_start[j];
            if (skeleton.position_orders[i] != -1) {
                if (i == j) {
                    auto position = motion.GetPosition(t, channel_index, skeleton.position_orders[i]);
                    motion.SetPosition(t, channel_index, skeleton.position_orders[j], root_position + MirrorVector(position - root_position, axis));
                    channel_index++;
                } else {
                    auto position = motion.GetPosition(t, channel_index, skeleton.position_orders[i]);
                    auto position2 = motion.GetPosition(t, channel_index_mirror, skeleton.position_orders[j]);
                    motion.SetPosition(t, channel_index_mirror, skeleton.position_orders[j], root_position + MirrorVector(position - root_position, axis));
                    motion.SetPosition(t, channel_index, skeleton.position_orders[i], root_position + MirrorVector(position2 - root_position, axis));
                }
            }
            if (skeleton.rotation_orders[i] != -1) {
                if (i == j) {
                    auto rotation = motion.GetRotation(t, channel_index, skeleton.rotation_orders[i]);
                    motion.SetRotation(t, channel_index, skeleton.rotation_orders[j], MirrorQuaternion(rotation, axis));
                } else {
                    auto rotation = motion.GetRotation(t, channel_index, skeleton.rotation_orders[i]);
                    auto rotation2 = motion.GetRotation(t, channel_index_mirror, skeleton.rotation_orders[j]);
                    motion.SetRotation(t, channel_index_mirror, skeleton.rotation_orders[j], MirrorQuaternion(rotation, axis));
                    motion.SetRotation(t, channel_index, skeleton.rotation_orders[i], MirrorQuaternion(rotation2, axis));
                }
            }
        }
    }
}