//
// Created by Scripter36 on 2024-09-28.
//

#include "core/scene_tree.h"

#include <utility>

#include "core/node.h"

using namespace rayengine;

shared_ptr<Node> SceneTree::root;

void SceneTree::Init() { root = Node::Create(); }

void SceneTree::Process(const float dt) {
    for (const auto node : *root) {
        node->Process(dt);
    }
}

void SceneTree::Draw() {
    for (const auto node : *root) {
        node->Draw();
    }
}

void SceneTree::SetRoot(shared_ptr<Node> new_root) { root = std::move(new_root); }
