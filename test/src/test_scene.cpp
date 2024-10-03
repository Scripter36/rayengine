//
// Created by scripter36 on 2024-09-29.
//

#include "test_scene.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "core/motion/bvh_format.h"
#include "core/motion/motion.h"
#include "core/motion/motion_editor.h"
#include "core/motion/motion_player.h"
#include "core/motion/skeleton.h"
#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"
#include "core/utils/orbit_controls.h"

using namespace rayengine;

namespace fs = std::filesystem;

TestScene::~TestScene() {
    for (const auto skeleton : skeletons) {
        delete skeleton;
    }
    for (const auto motion : motions) {
        delete motion;
    }
}

void TestScene::Init() {
    Node3D::Init();
    const auto orbit_controls = OrbitControls::Create(shared_from_this(), 10);
    const auto camera = rayengine::Camera3D::Create(orbit_controls, 45.0f, glm::vec3{0, 0, 0});

    cube = Cube::Create(shared_from_this(), glm::vec3{1, 1, 1});

    LoadBVHFiles(10);
}

void TestScene::LoadBVHFiles(int max_count) {
    int count = 0;
    vector<std::string> paths;
    for (const auto& entry : fs::directory_iterator("assets/motions")) {
        paths.push_back(entry.path().string());
        if (max_count > 0 && ++count >= max_count) {
            break;
        }
    }

#pragma omp parallel for default(none) shared(paths, skeletons, motions)
    for (int i = 0; i < paths.size(); i++) {
        auto file = std::ifstream(paths[i]);
        auto skeleton = new Skeleton();
        auto motion = new Motion();
        BVHFormat::Import(file, *skeleton, *motion);
        file.close();
#pragma omp critical
        {
            std::cout << "imported " << paths[i] << std::endl;
            MotionEditor::Scale(*motion, *skeleton, glm::vec3{0.01f});
            skeletons.push_back(skeleton);
            motions.push_back(motion);
            MotionPlayer::Create(shared_from_this(), *skeleton, *motion, glm::vec3{1, 0, 0});
        }
    }
}
