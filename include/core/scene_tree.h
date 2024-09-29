//
// Created by 1350a on 2024-09-28.
//

#ifndef SCENE_TREE_H
#define SCENE_TREE_H
#include <memory>

class Node;
using namespace std;

class SceneTree {
public:
    static void init();

    static void process(float dt);

    static void draw();

    static void setRoot(shared_ptr<Node> new_root);

private:
    static shared_ptr<Node> root;
};


#endif //SCENE_TREE_H
