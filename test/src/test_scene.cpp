//
// Created by scripter36 on 2024-09-29.
//

#include "test_scene.h"

#include <iostream>

#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"

std::shared_ptr<TestScene> TestScene::create(const weak_ptr<Node> &parent, const vector<shared_ptr<Node> > &children) {
    NODE_CREATE(node, TestScene);
    const auto camera = CameraNode::create(45.0f, {0, 0, 0}, node);
    camera->setPosition({0, 0, 10});

    node->cube = Cube::create(node);
    auto cube2 = Cube::create(node->cube);
    cube2->setPosition({0, 2, 0});

    return node;
}

void TestScene::process(const float dt) {
    angle += dt;
    cube->setRotation(glm::quat(glm::vec3{0, 0, angle}));
}
