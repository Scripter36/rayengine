//
// Created by scripter36 on 2024-09-29.
//

#include "test_scene.h"

#include <fstream>
#include <iostream>

#include "core/motion/bvh_format.h"
#include "core/motion/motion.h"
#include "core/motion/skeleton.h"
#include "core/motion/skeleton_visualizer.h"
#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"
#include "core/utils/orbit_controls.h"

using namespace rayengine;

void TestScene::Init() {
    Node3D::Init();
    const auto orbit_controls = OrbitControls::Create(shared_from_this(), 10);
    const auto camera = rayengine::Camera3D::Create(orbit_controls, 45.0f, glm::vec3{0, 0, 0});

    cube = Cube::Create(shared_from_this(), glm::vec3{1, 1, 1});

    // bvh test
    // open file in assets/walk_minimum.bvh
    auto file = std::ifstream("assets/walk_minimum.bvh");
    skeleton = new Skeleton();
    motion = new Motion();
    BVHFormat::Import(file, *skeleton, *motion);
    file.close();

    // skeleton visualizer test
    visualizer = SkeletonVisualizer::Create(shared_from_this(), *skeleton, glm::vec3{1, 0, 0});
    visualizer->SetPosition({0, 0, 5});
    visualizer->SetScale({0.01, 0.01, 0.01});
}

void TestScene::Process(const float dt) {
    elapsed_time += dt;
    int frame = static_cast<int>(elapsed_time / motion->frame_time);
    frame %= motion->frame_count;

    visualizer->UpdateSkeleton(*motion, frame);
}
