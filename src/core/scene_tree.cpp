//
// Created by Scripter36 on 2024-09-28.
//

#include "core/scene_tree.h"

#include <ranges>
#include <stack>

#include "core/node.h"

using namespace rayengine;

shared_ptr<Node> SceneTree::root;
bool SceneTree::bIs3DMode = false;

void SceneTree::Init() { root = Node::Create(); }

void SceneTree::Process(const float dt) {
    for (const auto node : *root) {
        node->Process(dt);
    }
}

void SceneTree::Draw(const shared_ptr<Node>& root) {
    const auto target = root ? root : SceneTree::root;

    // Stack to hold pairs of node and whether its children are processed
    std::stack<std::pair<shared_ptr<Node>, bool>> stack;
    stack.emplace(target, false);

    while (!stack.empty()) {
        auto& [current, childrenProcessed] = stack.top();

        if (!childrenProcessed) {
            // First pass: Draw the current node and mark children as not processed
            current->Draw();
            stack.top().second = true;

            // Push children onto the stack in reverse order for correct traversal
            for (auto & it : std::ranges::reverse_view(current->children)) {
                stack.emplace(it, false);
            }
        } else {
            // Second pass: After all children, call PostDraw and pop the node
            current->PostDraw();
            stack.pop();
        }
    }
}
