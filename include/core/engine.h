//
// Created by Scripter36 on 2024-09-28.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <string>

namespace rayengine {

class Engine {
public:
    static int screen_width;
    static int screen_height;
    static std::string title;

    static void Start();
};

}  // namespace rayengine

#endif  // ENGINE_H
