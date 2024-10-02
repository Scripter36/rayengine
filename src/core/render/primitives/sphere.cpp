//
// Created by 1350a on 2024-10-01.
//

#include "core/render/primitives/sphere.h"

#include "raylib.h"

using namespace rayengine;

void Sphere::Draw() {
    Node3D::Draw();
    DrawSphere({0, 0, 0}, 1,
               {static_cast<unsigned char>(color.r * 255), static_cast<unsigned char>(color.g * 255),
                static_cast<unsigned char>(color.b * 255), 255});
}