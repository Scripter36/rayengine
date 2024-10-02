//
// Created by Scripter36 on 2024-09-28.
//

#ifndef BASE_NODE_H
#define BASE_NODE_H

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

namespace rayengine {

#define NODE_CREATE_ARGS const weak_ptr<Node> &parent = {}, const vector<shared_ptr<Node>> &children = {}
#define NODE_CREATE(node, type)               \
    auto node = shared_ptr<type>(new type()); \
    if (parent.lock()) {                      \
        parent.lock()->AddChild(node);        \
    }                                         \
    for (const auto &child : children) {      \
        node->AddChild(child);                \
    }

class Node : public enable_shared_from_this<Node> {
public:
    virtual ~Node() = default;

    // Factory method
    static shared_ptr<Node> Create(NODE_CREATE_ARGS) {
        NODE_CREATE(node, Node);
        return node;
    }

    // Tree structure
    void AddChild(const shared_ptr<Node> &child);
    void RemoveChild(const shared_ptr<Node> &child);
    void RemoveFromParent();

    vector<shared_ptr<Node>> children;
    weak_ptr<Node> parent;

    struct Iterator {
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = shared_ptr<Node>;
        using pointer = shared_ptr<Node> *;
        using reference = shared_ptr<Node> &;

        explicit Iterator(const shared_ptr<Node> &node) : node(node) {}

        value_type operator*() { return node; }

        Iterator &operator++() {
            if (node == nullptr) {
                return *this;
            }
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

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.node == b.node; }

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.node != b.node; }

    protected:
        value_type node;
    };
    Iterator begin() { return Iterator(shared_from_this()); }
    Iterator end() { return Iterator(nullptr); }

    struct ReverseIterator {
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = shared_ptr<Node>;
        using pointer = shared_ptr<Node> *;
        using reference = shared_ptr<Node> &;

        explicit ReverseIterator(const shared_ptr<Node> &node) {
            // Find the last child
            auto head = node;
            while (head != nullptr && !head->children.empty()) {
                head = head->children.back();
            }
            this->node = head;
        }

        value_type operator*() { return node; }

        ReverseIterator &operator++() {
            if (node == nullptr) {
                return *this;
            }
            if (node->parent.lock()) {
                const auto &parent = node->parent.lock();
                const auto it = find(parent->children.begin(), parent->children.end(), node);
                if (it != parent->children.begin()) {
                    node = *(it - 1);
                    while (!node->children.empty()) {
                        node = node->children.back();
                    }
                } else {
                    node = parent;
                }
            } else {
                node = nullptr;
            }
            return *this;
        }

        friend bool operator==(const ReverseIterator &a, const ReverseIterator &b) { return a.node == b.node; }

        friend bool operator!=(const ReverseIterator &a, const ReverseIterator &b) { return a.node != b.node; }

    protected:
        value_type node;
    };
    ReverseIterator rbegin() { return ReverseIterator(shared_from_this()); }
    ReverseIterator rend() { return ReverseIterator(nullptr); }

    // Lifecycle
    virtual void EnterTree() {}
    virtual void ExitTree() {}
    virtual void Process(float dt) {}
    virtual void Draw() {}
    virtual void PostDraw() {}

protected:
    Node(){};
};

}  // namespace rayengine

#endif  // BASE_NODE_H
