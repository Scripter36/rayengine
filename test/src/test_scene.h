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
    static std::shared_ptr<TestScene> create(NODE_CREATE_ARGS);

    void Process(float dt) override;

protected:
    TestScene() : Node3D() {
    }

    shared_ptr<Cube> cube;
    float angle = 0;
};


#endif //TEST_SCENE_H
