//
// Created by 1350a on 2024-09-28.
//

#include "core/engine.h"

extern "C" {
#include "raylib.h"
}

#include "core/scene_tree.h"

int Engine::screenWidth = 800;
int Engine::screenHeight = 640;
std::string Engine::title = "Engine";

void Engine::start() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, title.c_str());

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // process
        SceneTree::process(GetFrameTime());

        // draw
        BeginDrawing();
        SceneTree::draw();
        EndDrawing();
    }

    CloseWindow();
}
