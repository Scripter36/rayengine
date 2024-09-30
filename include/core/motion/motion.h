//
// Created by Scripter36 on 24. 9. 30.
//

#ifndef MOTION_H
#define MOTION_H
#include <vector>


namespace rayengine {
class Motion {
public:
    int frame_count = 0;
    float frame_time = 0;
    std::vector<float> data;

    Motion() = default;
};
} // rayengine


#endif //MOTION_H
