#include "Paddle.h"

#include <algorithm>

#include "Config.h"

Paddle::Paddle(float x)
    : rect_{x, 0.0f, cfg::PaddleWidth, cfg::PaddleHeight} {
    Reset();
}

void Paddle::Reset() {
    rect_.y = (cfg::ScreenHeight - cfg::PaddleHeight) / 2.0f;
}

void Paddle::Move(float direction, float speedFactor, float dt) {
    rect_.y += direction * cfg::PaddleSpeed * speedFactor * dt;
    rect_.y = std::clamp(rect_.y, 0.0f, cfg::ScreenHeight - rect_.height);
}

void Paddle::Draw() const {
    DrawRectangleRec(rect_, RAYWHITE);
}
