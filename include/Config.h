#pragma once

namespace cfg {

    constexpr int ScreenWidth  = 900;
    constexpr int ScreenHeight = 600;
    constexpr const char* Title = "Ping Pong";
    
    constexpr float PaddleWidth  = 15.0f;
    constexpr float PaddleHeight = 100.0f;
    constexpr float PaddleSpeed  = 450.0f;
    constexpr float PaddleMargin = 30.0f;
    
    constexpr float BallRadius     = 10.0f;
    constexpr float BallStartSpeed = 400.0f;
    constexpr float BallMaxSpeed   = 900.0f;
    constexpr float BallSpeedUp    = 1.05f;
    constexpr float MaxBounceAngle = 60.0f;
    
    constexpr float AiSpeedFactor = 0.85f;
    constexpr int   WinScore      = 5;

}
