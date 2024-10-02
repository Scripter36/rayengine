﻿//
// Created by scripter36 on 2024-09-29.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include "core/node3d.h"

namespace rayengine {
class SkeletonVisualizer;
class Motion;
class Skeleton;
class Cube;
}  // namespace rayengine

using namespace rayengine;

class TestScene : public Node3D {
public:
    TestScene() : Node3D() {}
    NODE_CREATE_METHOD(TestScene)

    void Init() override;
    void Process(float dt) override;

protected:
    shared_ptr<Cube> cube;
    float angle = 0;
    float elapsed_time = 0;
    Skeleton *skeleton = nullptr;
    Motion *motion = nullptr;

    shared_ptr<SkeletonVisualizer> visualizer;
};

#endif  // TEST_SCENE_H
