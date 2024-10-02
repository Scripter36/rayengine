//
// Created by 1350a on 2024-10-01.
//

#include "core/motion/skeleton_visualizer.h"

#include "core/motion/skeleton.h"
#include "core/render/primitives/cylinder.h"
#include "core/render/primitives/sphere.h"

using namespace rayengine;

void SkeletonVisualizer::Init() {
    auto positions = skeleton.ForwardKinematics();
    for (int i = 0; i < skeleton.size(); ++i) {
        // 1. draw joint as a sphere
        auto joint_sphere = Sphere::Create(shared_from_this(), color);
        joint_sphere->SetPosition(positions[i]);
        joints.push_back(joint_sphere);
        // 2. draw bone as a cylinder
        for (int j = 0; j < skeleton.channel_counts[i]; j++) {
            auto bone_cylinder = Cylinder::Create(shared_from_this(), color);
            auto start = positions[i];
            auto end = positions[skeleton.children[j]];
            bone_cylinder->SetPosition((start + end) / 2.0f);
        }
    }
}

void SkeletonVisualizer::UpdateSkeleton(const Motion& motion, const int frame) {
    auto positions = skeleton.ForwardKinematics(motion, frame);
}
