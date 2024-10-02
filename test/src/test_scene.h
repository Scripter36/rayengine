//
// Created by scripter36 on 2024-09-29.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include "core/node3d.h"

namespace rayengine {
class Cube;
}

using namespace rayengine;

class TestScene : public Node3D {
public:
    NODE_CREATE_METHOD(TestScene)

    void Init() override;
    void Process(float dt) override;

    TestScene() : Node3D() {}
protected:

    shared_ptr<Cube> cube;
    float angle = 0;
};

#endif  // TEST_SCENE_H
