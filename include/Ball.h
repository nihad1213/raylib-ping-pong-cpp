#pragma once
#include <raylib.h>

class Ball {
public:
    Ball();

    void Reset(int direction);
    void Launch();

    void Update(float dt);
    void BounceOffPaddle(const Rectangle& paddle);
    void Draw() const;

    Vector2 Position() const { return pos_; }
    Vector2 Velocity() const { return vel_; }
    float Radius() const { return radius_; }

private:
    Vector2 pos_;
    Vector2 vel_;
    float radius_;
    int serveDir_ = 1;
};
