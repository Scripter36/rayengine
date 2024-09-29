//
// Created by 1350a on 2024-09-28.
//

#include "core/engine.h"
#include "core/node.h"
#include "core/scene_tree.h"
#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    const auto scene = Node::create();

    const auto camera = CameraNode::create(45.0f, {0, 0, 0}, scene);
    camera->setPosition({0, 0, 10});

    auto cube = Cube::create(scene);

    SceneTree::init();
    SceneTree::setRoot(scene);

    Engine::start();

    return 0;
}
