//
// Created by Scripter36 on 2024-09-28.
//

#include "core/scene_tree.h"

#include <utility>

#include "core/node.h"
#include "raylib.h"
#include "rlgl.h"

using namespace rayengine;

shared_ptr<Node> SceneTree::root;
bool SceneTree::bIs3DMode = false;

void SceneTree::Init() { root = Node::Create(); }

void SceneTree::Process(const float dt) {
    for (const auto node : *root) {
        node->Process(dt);
    }
}

void SceneTree::Draw() {
    SceneTree::bIs3DMode = false;
    for (const auto node : *root) {
        node->Draw();
        node->PostDraw();
    }
    if (SceneTree::bIs3DMode) {
        EndMode3D();
    }
}

void SceneTree::SetRoot(shared_ptr<Node> new_root) { root = std::move(new_root); }
