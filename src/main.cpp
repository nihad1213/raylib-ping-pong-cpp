#include <raylib.h>
#include "Config.h"
#include "Game.h"

int main() {
    InitWindow(cfg::ScreenWidth, cfg::ScreenHeight, cfg::Title);
    SetTargetFPS(60);

    {
        Game game;
        game.Run();
    }

    CloseWindow();
    return 0;
}
