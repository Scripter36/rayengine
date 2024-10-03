//
// Created by ikjun on 24. 10. 2.
//

#include "core/utils/orbit_controls.h"

extern "C" {
#include "raylib.h"
}

using namespace rayengine;

void OrbitControls::Init() {
    Node3D::Init();
    SetPosition({0, 0, distance});
}

void OrbitControls::Process(float dt) {
    Node3D::Process(dt);

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        auto [x, y] = GetMouseDelta();
        yaw -= x * 0.005f;
        pitch = glm::clamp(pitch - y * 0.005f, -glm::half_pi<float>(), glm::half_pi<float>());
    }

    distance = glm::max(0.0f, distance * glm::pow(1.1f, -GetMouseWheelMove()));

    SetRotation(glm::quat(glm::vec3{pitch, yaw, 0}));
    SetPosition(glm::rotate(GetRotation(), glm::vec3{0, 0, distance}));
}