//
// Created by scripter36 on 2024-09-29.
//

#include "core/engine.h"
#include "core/scene_tree.h"
#include "src/test_scene.h"

int main() {
    const auto scene = TestScene::create();
    SceneTree::init();
    SceneTree::setRoot(scene);
    Engine::start();
    return 0;
}
