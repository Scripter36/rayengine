//
// Created by Scripter36 on 2024-09-28.
//

#include "core/engine.h"

extern "C" {
#include "raylib.h"
}

#include "core/scene_tree.h"

using namespace rayengine;

int Engine::screen_width = 800;
int Engine::screen_height = 640;
std::string Engine::title = "Engine";

void Engine::Start() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screen_width, screen_height, title.c_str());

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // process
        SceneTree::Process(GetFrameTime());

        // draw
        BeginDrawing();
        ClearBackground(Color{0, 0, 0, 255});
        SceneTree::Draw();
        EndDrawing();
    }

    CloseWindow();
}
