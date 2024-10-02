//
// Created by ikjun on 24. 10. 2.
//

#include "core/render/primitives/cylinder.h"

#include "raylib.h"

using namespace rayengine;

void Cylinder::Draw() {
    Node3D::Draw();
    DrawCylinder({0, -0.5, 0}, 1, 1, 1, 32,
                 {static_cast<unsigned char>(color.r * 255), static_cast<unsigned char>(color.g * 255),
                  static_cast<unsigned char>(color.b * 255), 255});
}