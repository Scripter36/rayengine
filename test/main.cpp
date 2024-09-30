//
// Created by scripter36 on 2024-09-29.
//

#include <fstream>

#include "core/engine.h"
#include "core/scene_tree.h"
#include "core/motion/bvh_format.h"
#include "core/motion/motion.h"
#include "core/motion/skeleton.h"
#include "src/test_scene.h"

using namespace rayengine;

int main() {
    // bvh test
    // open file in assets/walk_minimum.bvh and make istream
    auto file = std::ifstream("assets/walk_minimum.bvh");
    Skeleton skeleton;
    Motion motion;
    BVHFormat::Import(file, skeleton, motion);
    auto out = std::ofstream("assets/walk_minimum_out.bvh");
    BVHFormat::Export(out, skeleton, motion);
    file.close();
    out.close();
    const auto scene = TestScene::create();
    SceneTree::Init();
    SceneTree::SetRoot(scene);
    Engine::Start();
    return 0;
}
