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
    if (const auto camera = Camera3D::GetMainCamera()) {
        BeginMode3D(*camera);
        rlPushMatrix();
        {
            rlMultMatrixf(glm::value_ptr(GetGlobalTransform()));

            rlBegin(RL_TRIANGLES);
            rlColor3f(color.r, color.g, color.b);
            {
                // Front face
                rlNormal3f(0.0f, 0.0f, 1.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5);  // Top Left

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5);  // Top Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5);  // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Right

                // Back face
                rlNormal3f(0.0f, 0.0f, -1.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5);  // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5);  // Top Right
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5);  // Top Left

                // Top face
                rlNormal3f(0.0f, 1.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5);  // Top Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5);  // Bottom Left
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5);  // Bottom Right

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5);  // Top Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5);  // Top Left
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5);  // Bottom Right

                // Bottom face
                rlNormal3f(0.0f, -1.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5);  // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Right
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Left

                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5);  // Top Right
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Right
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5);  // Top Left

                // Right face
                rlNormal3f(1.0f, 0.0f, 0.0f);
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5);  // Top Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5);  // Top Left

                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5);  // Top Left

                // Left face
                rlNormal3f(-1.0f, 0.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5);  // Top Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5);  // Top Right

                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5);  // Bottom Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5);  // Top Left
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5);  // Bottom Right
            }
            rlEnd();
        }
        rlPopMatrix();
        EndMode3D();
    }
}
