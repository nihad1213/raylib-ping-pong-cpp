#pragma once
#include <raylib.h>

class Paddle {
public:
    explicit Paddle(float x);

    void Reset();
    void Move(float direction, float speedFactor, float dt);
    void Draw() const;

    Rectangle Bounds() const { return rect_; }
    float CenterY() const { return rect_.y + rect_.height / 2.0f; }

private:
    Rectangle rect_;
};
