# Ping Pong (raylib + C++17)

A simple two-player / vs-computer ping pong game built with [raylib](https://www.raylib.com/).

## Project structure

```
pingpong/
├── CMakeLists.txt   build script (uses installed raylib, or downloads it)
├── include/         headers: Config, Paddle, Ball, Game
├── src/             implementations + main.cpp
```

## Requirements

- A C++17 compiler
- [CMake](https://cmake.org/download/) 3.15 or newer
- Git (CMake uses it to download raylib on the first build)
- Internet connection for the first build (unless raylib is already installed)

## 1. Install the tools

### Windows
1. Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) (choose **Desktop development with C++**), or MinGW-w64.
2. Install [CMake](https://cmake.org/download/) and [Git](https://git-scm.com/download/win).
3. Use **Developer PowerShell for VS** (or any terminal where CMake can find your compiler).

### Linux (Debian / Ubuntu)
```bash
sudo apt update
sudo apt install build-essential cmake git \
    libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev
```
Fedora: `sudo dnf install gcc-c++ cmake git libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel mesa-libGL-devel`

### macOS
```bash
xcode-select --install
brew install cmake git
```

## 2. Build

From inside the `pingpong` folder:

```bash
cmake -B build
cmake --build build --config Release
```

The first build takes a minute or two because raylib is downloaded and compiled. Later builds are fast.

## 3. Run

| OS | Command |
|----|---------|
| Linux / macOS | `./build/pingpong` |
| Windows (Visual Studio) | `.\build\Release\pingpong.exe` |
| Windows (MinGW) | `.\build\pingpong.exe` |

## Controls

| Action | Key |
|--------|-----|
| Menu: play vs computer | `1` |
| Menu: two players | `2` |
| Left paddle | `W` / `S` |
| Right paddle | `Up` / `Down` (computer-controlled in single player) |
| Serve the ball | `Space` |
| Back to menu after a match | `Enter` |
| Quit | `Esc` |

First to **5 points** wins. The ball speeds up with each hit, and where it touches the paddle changes its bounce angle.

## Customize

Everything tweakable is in `include/Config.h`: window size, paddle and ball speed, AI difficulty (`AiSpeedFactor`), and the winning score. Rebuild after changing it.

## Troubleshooting

- **`cmake` not found**: install CMake and reopen your terminal.
- **Git or download error on first build**: check your internet connection and that Git is installed. Alternatively install raylib yourself (`brew install raylib`, or your Linux package manager's `libraylib-dev`) and CMake will use it instead of downloading.
- **Linux: `X11/Xlib.h` or `GL/gl.h` not found**: install the dev packages from step 1.
- **Windows: no compiler found**: run the commands from *Developer PowerShell for VS*, or pass a generator: `cmake -B build -G "MinGW Makefiles"`.
- **Window doesn't open under WSL**: you need WSL 2 with WSLg (Windows 11 or recent Windows 10).
- **Start clean**: delete the `build` folder and repeat step 2.