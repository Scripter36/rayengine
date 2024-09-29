//
// Created by 1350a on 2024-09-28.
//

#include "core/node.h"

void Node::addChild(const shared_ptr<Node>& child) {
    // check if child is already in children
    for (auto& c: children) {
        if (c == child) {
            return;
        }
    }

    // remove child from previous parent
    if (const auto p = child->parent.lock()) {
        p->removeChild(child);
    }

    // add child to children
    children.push_back(child);
    child->parent = shared_from_this();
}

void Node::removeChild(const shared_ptr<Node>& child) {
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

void Node::removeFromParent() {
    if (const auto p = parent.lock()) {
        p->removeChild(shared_from_this());
    }
}

glm::mat4 Node::getLocalTransform() const {
    const auto translationMatrix = glm::translate(glm::mat4(1.0f), position);
    const auto rotationMatrix = glm::mat4_cast(rotation);
    const auto scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Node::getGlobalTransform() const {
    if (const auto p = parent.lock()) {
        return p->getGlobalTransform() * getLocalTransform();
    } else {
        return getLocalTransform();
    }
}
