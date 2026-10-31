#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <string>

Game::Game()
    : left_(cfg::PaddleMargin),
      right_(cfg::ScreenWidth - cfg::PaddleMargin - cfg::PaddleWidth) {}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update(GetFrameTime());
        Draw();
    }
}

void Game::StartMatch(bool vsAi) {
    vsAi_ = vsAi;
    scoreLeft_ = scoreRight_ = 0;
    left_.Reset();
    right_.Reset();
    ball_.Reset(GetRandomValue(0, 1) ? 1 : -1);
    state_ = State::Serve;
}

void Game::Update(float dt) {
    switch (state_) {
        case State::Menu:
            if (IsKeyPressed(KEY_ONE)) StartMatch(true);
            if (IsKeyPressed(KEY_TWO)) StartMatch(false);
            break;

        case State::Serve:
            UpdatePaddles(dt);
            if (IsKeyPressed(KEY_SPACE)) {
                ball_.Launch();
                state_ = State::Playing;
            }
            break;

        case State::Playing:
            UpdatePaddles(dt);
            UpdateBall(dt);
            break;

        case State::GameOver:
            if (IsKeyPressed(KEY_ENTER)) state_ = State::Menu;
            break;
    }
}

void Game::UpdatePaddles(float dt) {
    float dirLeft = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));
    left_.Move(dirLeft, 1.0f, dt);

    if (vsAi_) {
        float diff = ball_.Position().y - right_.CenterY();
        float dir = 0.0f;
        if (diff > 10.0f) dir = 1.0f;
        else if (diff < -10.0f) dir = -1.0f;
        right_.Move(dir, cfg::AiSpeedFactor, dt);
    } else {
        float dirRight = static_cast<float>(IsKeyDown(KEY_DOWN)) - static_cast<float>(IsKeyDown(KEY_UP));
        right_.Move(dirRight, 1.0f, dt);
    }
}

void Game::UpdateBall(float dt) {
    ball_.Update(dt);

    Vector2 pos = ball_.Position();
    Vector2 vel = ball_.Velocity();
    float r = ball_.Radius();

    if (vel.x < 0 && CheckCollisionCircleRec(pos, r, left_.Bounds())) {
        ball_.BounceOffPaddle(left_.Bounds());
    } else if (vel.x > 0 && CheckCollisionCircleRec(pos, r, right_.Bounds())) {
        ball_.BounceOffPaddle(right_.Bounds());
    }

    if (pos.x + r < 0.0f) Score(false);
    else if (pos.x - r > cfg::ScreenWidth) Score(true);
}

void Game::Score(bool leftScored) {
    (leftScored ? scoreLeft_ : scoreRight_)++;

    if (scoreLeft_ >= cfg::WinScore || scoreRight_ >= cfg::WinScore) {
        state_ = State::GameOver;
        return;
    }

    ball_.Reset(leftScored ? 1 : -1);
    state_ = State::Serve;
}

void Game::DrawCenteredText(const char* text, int y, int size, Color color) const {
    int w = MeasureText(text, size);
    DrawText(text, (cfg::ScreenWidth - w) / 2, y, size, color);
}

void Game::Draw() const {
    BeginDrawing();
    ClearBackground({20, 24, 33, 255});

    if (state_ == State::Menu) {
        DrawCenteredText("PING PONG", 150, 80, RAYWHITE);
        DrawCenteredText("1 - Play vs Computer", 300, 30, LIGHTGRAY);
        DrawCenteredText("2 - Two Players", 345, 30, LIGHTGRAY);
        DrawCenteredText("Left: W / S      Right: Up / Down", 450, 20, GRAY);
        EndDrawing();
        return;
    }

    for (int y = 0; y < cfg::ScreenHeight; y += 30) {
        DrawRectangle(cfg::ScreenWidth / 2 - 2, y, 4, 15, GRAY);
    }

    left_.Draw();
    right_.Draw();
    ball_.Draw();

    DrawText(std::to_string(scoreLeft_).c_str(), cfg::ScreenWidth / 2 - 80, 20, 60, RAYWHITE);
    DrawText(std::to_string(scoreRight_).c_str(), cfg::ScreenWidth / 2 + 45, 20, 60, RAYWHITE);

    if (state_ == State::Serve) {
        DrawCenteredText("Press SPACE to serve", cfg::ScreenHeight - 60, 24, LIGHTGRAY);
    } else if (state_ == State::GameOver) {
        const char* winner = (scoreLeft_ > scoreRight_) ? "LEFT PLAYER WINS!" : "RIGHT PLAYER WINS!";
        DrawCenteredText(winner, 240, 50, GOLD);
        DrawCenteredText("Press ENTER for menu", 320, 24, LIGHTGRAY);
    }

    DrawFPS(10, 10);
    EndDrawing();
}
