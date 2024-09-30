//
// Created by scripter36 on 2024-09-29.
//

#include "test_scene.h"

#include <iostream>

#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"

std::shared_ptr<TestScene> TestScene::create(const weak_ptr<Node> &parent, const vector<shared_ptr<Node> > &children) {
    NODE_CREATE(node, TestScene);
    const auto camera = rayengine::Camera3D::Create(45.0f, {0, 0, 0}, node);
    camera->SetPosition({0, 0, 10});

    node->cube = Cube::Create(node);
    auto cube2 = Cube::Create(node->cube);
    cube2->SetPosition({0, 2, 0});

    return node;
}

void TestScene::Process(const float dt) {
    angle += dt;
    cube->SetRotation(glm::quat(glm::vec3{0, 0, angle}));
}
