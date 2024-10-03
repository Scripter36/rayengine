//
// Created by scripter36 on 2024-09-29.
//

#include <fstream>
#include <iostream>

#include "core/engine.h"
#include "core/scene_tree.h"
#include "src/test_scene.h"

using namespace rayengine;

int main() {
    const auto scene = TestScene::Create();
    SceneTree::Init();
    SceneTree::SetRoot(scene);
    Engine::Start();
    return 0;
}
