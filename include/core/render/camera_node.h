﻿//
// Created by Scripter36 on 2024-09-28.
//

#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H
#include "core/node3d.h"

extern "C" {
#include "raylib.h"
}

#include "core/node.h"
#include "glm/glm.hpp"

namespace rayengine {
    class Camera3D : public Node3D {
    public:
        static shared_ptr<Camera3D> Create(float fov = 45.0f,
                                           glm::vec3 target = {0, 0, 0},
                                           NODE_CREATE_ARGS);

        static Camera *GetMainCamera();

        void Process(float dt) override;

    protected:
        static weak_ptr<Camera3D> main_camera;

        Camera camera;
        float fov = 45.0f;
        glm::vec3 target = {0, 0, 0};

        Camera3D() : Node3D() {
        }
    };
}


#endif //CAMERA_NODE_H
