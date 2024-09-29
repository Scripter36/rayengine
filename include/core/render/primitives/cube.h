//
// Created by 1350a on 2024-09-28.
//

#ifndef CUBE_H
#define CUBE_H
#include "core/node.h"


class Cube : public Node {
public:
    static shared_ptr<Cube> create(NODE_CREATE_ARGS,
                                   const glm::vec3 color = {1, 1, 1}) {
        NODE_CREATE(node, Cube);
        node->color = color;
        return node;
    }

    void draw() override;

    glm::vec3 color = {1, 1, 1};

protected:
    NODE_DEFAULT_CONSTRUCTOR(Cube)
};


#endif //CUBE_H
