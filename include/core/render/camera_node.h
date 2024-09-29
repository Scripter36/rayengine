//
// Created by 1350a on 2024-09-28.
//

#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

extern "C" {
#include "raylib.h"
}

#include "core/node.h"
#include "glm/glm.hpp"

class CameraNode : public Node {
public:
    static shared_ptr<CameraNode> create(float fov = 45.0f,
                                         glm::vec3 target = {0, 0, 0},
                                         NODE_CREATE_ARGS);

    static Camera* getMainCamera();

    void process(float dt) override;

protected:
    static weak_ptr<CameraNode> mainCamera;

    Camera camera;
    float fov = 45.0f;
    glm::vec3 target = {0, 0, 0};

    NODE_DEFAULT_CONSTRUCTOR(CameraNode)
};


#endif //CAMERA_NODE_H
