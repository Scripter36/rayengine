//
// Created by 1350a on 2024-10-03.
//

#ifndef MOTION_PLAYER_H
#define MOTION_PLAYER_H
#include <utility>

#include "core/node3d.h"

namespace rayengine {
class SkeletonVisualizer;
}
namespace rayengine {
class Skeleton;
class Motion;
}  // namespace rayengine

using namespace rayengine;

namespace rayengine {

class MotionPlayer : public Node3D {
public:
    MotionPlayer(Skeleton& skeleton, Motion& motion, glm::vec3 color)
        : Node3D(), skeleton(skeleton), motion(motion), color(color) {}
    NODE_CREATE_METHOD(MotionPlayer)

    void Init() override;
    void Process(float dt) override;

protected:
    Skeleton& skeleton;
    Motion& motion;
    glm::vec3 color;
    shared_ptr<SkeletonVisualizer> visualizer;
    float elapsed_time = 0;
};

}  // namespace rayengine

#endif  // MOTION_PLAYER_H
