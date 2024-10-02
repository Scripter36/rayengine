//
// Created by scripter36 on 2024-09-29.
//

#include "test_scene.h"

#include "core/render/camera_node.h"
#include "core/render/primitives/cube.h"

using namespace rayengine;

void TestScene::Init() {
    Node3D::Init();
    const auto camera = rayengine::Camera3D::Create(shared_from_this(), 45.0f, glm::vec3{0, 0, 0});
    camera->SetPosition({0, 0, 10});

    cube = Cube::Create(shared_from_this(), glm::vec3{1, 1, 1});
    auto cube2 = Cube::Create(cube, glm::vec3{1, 1, 1});
    cube2->SetPosition({0, 2, 0});
}

void TestScene::Process(const float dt) {
    angle += dt;
    cube->SetRotation(glm::quat(glm::vec3{0, 0, angle}));
}
