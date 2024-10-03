//
// Created by 1350a on 2024-10-03.
//

#include "core/motion/motion_player.h"

#include "core/motion/motion.h"
#include "core/motion/skeleton_visualizer.h"

void MotionPlayer::Init() {
    Node3D::Init();

    visualizer = SkeletonVisualizer::Create(shared_from_this(), skeleton, color);
}

void MotionPlayer::Process(const float dt) {
    Node3D::Process(dt);
    elapsed_time += dt;
    const int frame = static_cast<int>(elapsed_time / motion.frame_time) % motion.frame_count;
    visualizer->UpdateSkeleton(motion, frame);
}