//
// Created by Scripter36 on 2024-09-28.
//

#include "core/node.h"
using namespace rayengine;

void Node::AddChild(const shared_ptr<Node>& child) {
    // check if child is already in children
    for (auto& c : children) {
        if (c == child) {
            return;
        }
    }

    // remove child from previous parent
    if (const auto p = child->parent.lock()) {
        p->RemoveChild(child);
    }

    // add child to children
    children.push_back(child);
    child->parent = shared_from_this();
}

void Node::RemoveChild(const shared_ptr<Node>& child) {
    // find child in children
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == child) {
            // remove child from children
            children.erase(it);
            child->parent.reset();
            return;
        }
    }
}

void Node::RemoveFromParent() {
    if (const auto p = parent.lock()) {
        p->RemoveChild(shared_from_this());
    }
}
