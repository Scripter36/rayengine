﻿//
// Created by Scripter36 on 2024-09-28.
//

#include "core/render/camera_node.h"

#include <iostream>

weak_ptr<rayengine::Camera3D> rayengine::Camera3D::main_camera;

shared_ptr<rayengine::Camera3D> rayengine::Camera3D::Create(const float fov, const glm::vec3 target,
                                                            const weak_ptr<Node> &parent,
                                                            const vector<shared_ptr<Node> > &children) {
    NODE_CREATE(node, Camera3D);
    node->camera = Camera();
    node->camera.fovy = fov;
    node->target = target;
    if (!main_camera.lock()) {
        main_camera = node;
    }
    return node;
}

Camera *rayengine::Camera3D::GetMainCamera() {
    if (const auto camera_node = main_camera.lock()) {
        return &camera_node->camera;
    }
    return nullptr;
}

void rayengine::Camera3D::Process(float dt) {
    // set camera position, target and up vectors from node's global position and rotation
    const auto position = GetGlobalPosition();
    camera.position = Vector3{position.x, position.y, position.z};
    const auto rotation = GetGlobalRotation();
    const auto forward = glm::rotate(rotation, glm::vec3{0, 0, -1});
    const auto up = glm::rotate(rotation, glm::vec3{0, 1, 0});
    camera.target = Vector3{position.x + forward.x, position.y + forward.y, position.z + forward.z};
    camera.up = Vector3{up.x, up.y, up.z};
}
