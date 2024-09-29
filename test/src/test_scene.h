﻿//
// Created by scripter36 on 2024-09-29.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include "core/node.h"


class Cube;

class TestScene : public Node {
public:
    static std::shared_ptr<TestScene> create(NODE_CREATE_ARGS);

    void process(float dt) override;

protected:
    NODE_DEFAULT_CONSTRUCTOR(TestScene);

    shared_ptr<Cube> cube;
    float angle = 0;
};


#endif //TEST_SCENE_H
