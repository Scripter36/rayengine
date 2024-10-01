//
// Created by Scripter36 on 2024-09-28.
//

#ifndef SCENE_TREE_H
#define SCENE_TREE_H
#include <memory>

using namespace std;

namespace rayengine {
class Node;

class SceneTree {
public:
    static void Init();
    static void Process(float dt);
    static void Draw();
    static void SetRoot(shared_ptr<Node> new_root);

private:
    static shared_ptr<Node> root;
};
}  // namespace rayengine

#endif  // SCENE_TREE_H
