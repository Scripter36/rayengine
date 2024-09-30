//
// Created by 1350a on 2024-09-28.
//

#ifndef BASE_NODE_H
#define BASE_NODE_H

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

using namespace std;

namespace rayengine {
#define NODE_CREATE_ARGS \
const weak_ptr<Node> &parent = {}, \
const vector<shared_ptr<Node>>& children = {}
#define NODE_CREATE(node, Node) \
auto node = shared_ptr<Node>(new Node()); \
if (parent.lock()) { \
parent.lock()->addChild(node); \
} \
for (const auto &child : children) { \
node->addChild(child); \
}

    class Node : public enable_shared_from_this<Node> {
    public:
        virtual ~Node() = default;

        // Factory method
        static shared_ptr<Node> create(NODE_CREATE_ARGS) {
            NODE_CREATE(node, Node);
            return node;
        }

        // Tree structure
        void addChild(const shared_ptr<Node> &child);

        void removeChild(const shared_ptr<Node> &child);

        void removeFromParent();

        vector<shared_ptr<Node> > children;
        weak_ptr<Node> parent;

        struct Iterator {
            using iterator_category = forward_iterator_tag;
            using difference_type = ptrdiff_t;
            using value_type = shared_ptr<Node>;
            using pointer = shared_ptr<Node> *;
            using reference = shared_ptr<Node> &;

            explicit Iterator(const shared_ptr<Node> &node) : node(node) {
            }

            value_type operator*() {
                return node;
            }

            Iterator &operator++() {
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    while (node->parent.lock() && node == node->parent.lock()->children.back()) {
                        node = node->parent.lock();
                    }
                    if (node->parent.lock()) {
                        const auto &parent = node->parent.lock();
                        const auto it = find(parent->children.begin(), parent->children.end(), node);
                        node = *(it + 1);
                    } else {
                        node = nullptr;
                    }
                }
                return *this;
            }

            Iterator operator++(int) {
                Iterator it = *this;
                ++(*this);
                return it;
            }

            friend bool operator==(const Iterator &a, const Iterator &b) {
                return a.node == b.node;
            }

            friend bool operator!=(const Iterator &a, const Iterator &b) {
                return a.node != b.node;
            }

        protected:
            value_type node;
        };

        Iterator begin() {
            return Iterator(shared_from_this());
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        // Lifecycle
        virtual void enter_tree() {
        }

        virtual void exit_tree() {
        }

        virtual void process(float dt) {
        }

        virtual void draw() {
        }

    protected:
        Node() {
        };
    };
}


#endif //BASE_NODE_H
