//
// Created by Scripter36 on 2024-09-28.
//

#include "core/render/primitives/cube.h"

#include "gtc/type_ptr.inl"

extern "C" {
#include "raylib.h"
#include "rlgl.h"
}

using namespace rayengine;
#include "core/render/camera_node.h"

void Cube::Draw() {
    Node3D::Draw();
    DrawCube({0, 0, 0}, 1, 1, 1,
             {static_cast<unsigned char>(color.r * 255), static_cast<unsigned char>(color.g * 255),
              static_cast<unsigned char>(color.b * 255), 255});
}
