//
// Created by 1350a on 2024-10-01.
//

#include "core/motion/skeleton_visualizer.h"

#include "core/motion/skeleton.h"
#include "core/render/primitives/cylinder.h"
#include "core/render/primitives/sphere.h"

using namespace rayengine;

void SkeletonVisualizer::Init() {
    const auto positions = skeleton.ForwardKinematics();
    for (int i = 0; i < skeleton.size(); ++i) {
        // 1. draw joint as a sphere
        auto joint_sphere = Sphere::Create(shared_from_this(), color);
        joint_sphere->SetPosition(positions[i]);
        joint_sphere->SetScale(glm::vec3{0.01f});
        joints.push_back(joint_sphere);
        // 2. draw bone as a cylinder
        for (int j = 0; j < skeleton.children_counts[i]; j++) {
            auto bone_cylinder = Cylinder::Create(shared_from_this(), color);
            auto start = positions[i];
            auto end = positions[skeleton.children[j + skeleton.children_indices[i]]];
            bone_cylinder->SetPosition((start + end) / 2.0f);
            bone_cylinder->SetScale(glm::vec3{0.004f, glm::distance(start, end), 0.004f});
            bone_cylinder->SetRotation(glm::quatLookAt(glm::normalize(end - start), glm::vec3{0, 1, 0}) * glm::angleAxis(glm::half_pi<float>(), glm::vec3{1, 0, 0}));
            bones.push_back(bone_cylinder);
        }
    }
}

void SkeletonVisualizer::UpdateSkeleton(const Motion& motion, const int frame) const {
    auto positions = skeleton.ForwardKinematics(motion, frame);
    for (int i = 0; i < skeleton.size(); ++i) {
        joints[i]->SetPosition(positions[i]);
        for (int j = 0; j < skeleton.children_counts[i]; j++) {
            auto start = positions[i];
            auto end = positions[skeleton.children[j + skeleton.children_indices[i]]];
            bones[j + skeleton.children_indices[i]]->SetPosition((start + end) / 2.0f);
            bones[j + skeleton.children_indices[i]]->SetRotation(glm::quatLookAt(glm::normalize(end - start), glm::vec3{0, 1, 0}) * glm::angleAxis(glm::half_pi<float>(), glm::vec3{1, 0, 0}));
        }
    }
}
