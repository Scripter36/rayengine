//
// Created by 1350a on 2024-09-28.
//

#include "core/engine.h"
#include "core/node.h"
#include "core/scene_tree.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    const auto scene = Node::create();

    SceneTree::init();
    SceneTree::setRoot(scene);

    Engine::start();

    return 0;
}
