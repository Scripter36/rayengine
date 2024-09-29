//
// Created by 1350a on 2024-09-28.
//

#include <utility>

#include "core/scene_tree.h"

#include "core/node.h"

shared_ptr<Node> SceneTree::root;

void SceneTree::init() {
    root = Node::create();
}

void SceneTree::process(const float dt) {
    for (const auto node: *root) {
        node->process(dt);
    }
}

void SceneTree::draw() {
    for (const auto node: *root) {
        node->draw();
    }
}

void SceneTree::setRoot(shared_ptr<Node> new_root) {
    root = std::move(new_root);
}
