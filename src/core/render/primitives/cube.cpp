//
// Created by 1350a on 2024-09-28.
//

#include "core/render/primitives/cube.h"

extern "C" {
#include "raylib.h"
#include "rlgl.h"
}

#include "core/render/camera_node.h"
#include "gtx/matrix_interpolation.hpp"

void Cube::draw() {
    if (auto ptr = CameraNode::getMainCamera()) {
        BeginMode3D(*ptr);
        const auto transform = getGlobalTransform();
        const auto position = getGlobalPosition();
        glm::vec3 axis;
        float angle;
        glm::axisAngle(transform, axis, angle);
        const auto scale = getScale();

        rlPushMatrix(); {
            // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
            rlTranslatef(position.x, position.y, position.z);
            // rlRotatef(angle / glm::pi<float>() * 180, axis.x, axis.y, axis.z);
            // rlScalef(scale.x, scale.y, scale.z); // NOTE: Vertices are directly scaled on definition

            rlBegin(RL_TRIANGLES);
            rlColor3f(color.r, color.g, color.b); {
                // Front face
                rlNormal3f(0.0f, 0.0f, 1.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5); // Bottom Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5); // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5); // Top Left

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5); // Top Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5); // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5); // Bottom Right

                // Back face
                rlNormal3f(0.0f, 0.0f, -1.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5); // Bottom Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5); // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5); // Top Right
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5); // Top Left

                // Top face
                rlNormal3f(0.0f, 1.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5); // Top Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5); // Bottom Left
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5); // Bottom Right

                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5); // Top Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5); // Top Left
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5); // Bottom Right

                // Bottom face
                rlNormal3f(0.0f, -1.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5); // Top Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5); // Bottom Right
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5); // Bottom Left

                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5); // Top Right
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5); // Bottom Right
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5); // Top Left

                // Right face
                rlNormal3f(1.0f, 0.0f, 0.0f);
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 - 0.5); // Top Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5); // Top Left

                rlVertex3f(0 + 0.5, 0 - 0.5, 0 + 0.5); // Bottom Left
                rlVertex3f(0 + 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right
                rlVertex3f(0 + 0.5, 0 + 0.5, 0 + 0.5); // Top Left

                // Left face
                rlNormal3f(-1.0f, 0.0f, 0.0f);
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5); // Top Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 - 0.5); // Top Right

                rlVertex3f(0 - 0.5, 0 - 0.5, 0 + 0.5); // Bottom Left
                rlVertex3f(0 - 0.5, 0 + 0.5, 0 + 0.5); // Top Left
                rlVertex3f(0 - 0.5, 0 - 0.5, 0 - 0.5); // Bottom Right
            }
            rlEnd();
        }
        rlPopMatrix();
        EndMode3D();
    }
}
