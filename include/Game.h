#pragma once
#include "Ball.h"
#include "Paddle.h"

class Game {
public:
    Game();
    void Run();

private:
    enum class State { Menu, Serve, Playing, GameOver };

    void StartMatch(bool vsAi);
    void Update(float dt);
    void UpdatePaddles(float dt);
    void UpdateBall(float dt);
    void Score(bool leftScored);
    void Draw() const;

    void DrawCenteredText(const char* text, int y, int size, Color color) const;

    State state_ = State::Menu;
    bool vsAi_ = true;
    int scoreLeft_ = 0;
    int scoreRight_ = 0;

    Paddle left_;
    Paddle right_;
    Ball ball_;
};
