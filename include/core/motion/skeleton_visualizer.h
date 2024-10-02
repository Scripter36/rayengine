//
// Created by 1350a on 2024-10-01.
//

#ifndef SKELETON_VISUALIZER_H
#define SKELETON_VISUALIZER_H
#include "core/node3d.h"

namespace rayengine {
class Skeleton;
class Motion;
}  // namespace rayengine

namespace rayengine {

class SkeletonVisualizer : public Node3D {
public:
    NODE_CREATE_METHOD(SkeletonVisualizer)

    void Init() override;
    void UpdateSkeleton(const Motion &motion, int frame);

    SkeletonVisualizer(Skeleton &skeleton, glm::vec3 color, NODE_CREATE_ARGS)
        : Node3D(), skeleton(skeleton), color(color) {}

protected:
    Skeleton &skeleton;
    glm::vec3 color;

    // index synced with skeleton
    vector<shared_ptr<Node>> joints;
    // index synced with skeleton children
    vector<shared_ptr<Node>> bones;
};

}  // namespace rayengine

#endif  // SKELETON_VISUALIZER_H
