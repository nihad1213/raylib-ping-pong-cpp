#include "Ball.h"

#include <algorithm>
#include <cmath>

#include "Config.h"

Ball::Ball() : pos_{0, 0}, vel_{0, 0}, radius_(cfg::BallRadius) {
    Reset(1);
}

void Ball::Reset(int direction) {
    serveDir_ = direction;
    pos_ = {cfg::ScreenWidth / 2.0f, cfg::ScreenHeight / 2.0f};
    vel_ = {0.0f, 0.0f};
}

void Ball::Launch() {
    float angle = static_cast<float>(GetRandomValue(-30, 30)) * DEG2RAD;
    vel_.x = serveDir_ * cfg::BallStartSpeed * std::cos(angle);
    vel_.y = cfg::BallStartSpeed * std::sin(angle);
}

void Ball::Update(float dt) {
    pos_.x += vel_.x * dt;
    pos_.y += vel_.y * dt;

    if (pos_.y - radius_ < 0.0f) {
        pos_.y = radius_;
        vel_.y = std::fabs(vel_.y);
    } else if (pos_.y + radius_ > cfg::ScreenHeight) {
        pos_.y = cfg::ScreenHeight - radius_;
        vel_.y = -std::fabs(vel_.y);
    }
}

void Ball::BounceOffPaddle(const Rectangle& paddle) {
    float paddleCenter = paddle.y + paddle.height / 2.0f;
    float offset = std::clamp((pos_.y - paddleCenter) / (paddle.height / 2.0f), -1.0f, 1.0f);
    float angle = offset * cfg::MaxBounceAngle * DEG2RAD;

    float speed = std::hypot(vel_.x, vel_.y) * cfg::BallSpeedUp;
    speed = std::min(speed, cfg::BallMaxSpeed);

    bool leftPaddle = paddle.x < cfg::ScreenWidth / 2.0f;
    float dirX = leftPaddle ? 1.0f : -1.0f;

    vel_.x = dirX * speed * std::cos(angle);
    vel_.y = speed * std::sin(angle);

    pos_.x = leftPaddle ? paddle.x + paddle.width + radius_
                        : paddle.x - radius_;
}

void Ball::Draw() const {
    DrawCircleV(pos_, radius_, RAYWHITE);
}
