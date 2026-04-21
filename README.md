# 🏓 Pong Game — SFML C++

A classic two-player Pong game built with C++ and SFML. Two players compete on the same keyboard, bouncing a ball back and forth. The first player to reach **5 points** wins!

## Features

- Two-player local multiplayer (same keyboard)
- Ball speed increases slightly on each paddle hit
- Angle of the ball changes based on where it hits the paddle
- Live score display
- Win screen with the winner's name
- Decorative center line

## Controls

| Player | Move Up | Move Down |
|--------|---------|-----------|
| Player 1 (Left) | `W` | `S` |
| Player 2 (Right) | `↑` | `↓` |

## Prerequisites

- A C++ compiler supporting **C++17** (e.g. `g++`, `clang++`, or MSVC)
- [SFML 3.x](https://www.sfml-dev.org/download/) installed on your system
- A font file named `Roboto_Condensed-MediumItalic.ttf` placed in the same directory as the executable

## Building & Running

### Linux / macOS

```bash
g++ -std=c++17 PingPongGame.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system
./pong
```

### Windows (MinGW)

```bash
g++ -std=c++17 PingPongGame.cpp -o pong.exe -lsfml-graphics -lsfml-window -lsfml-system
pong.exe
```

### Windows (MSVC)

Open the project in Visual Studio, link the SFML libraries in your project settings, and build in Release or Debug mode.

> **Note:** Make sure the SFML `.dll` files (on Windows) or `.so`/`.dylib` files (on Linux/macOS) are accessible, either in the same directory as the executable or in your system's library path.

## Font Setup

The game uses `Roboto_Condensed-MediumItalic.ttf`. You can download it from [Google Fonts](https://fonts.google.com/specimen/Roboto+Condensed) and place it in the same folder as the executable.

## Gameplay

- The ball resets to the center after each point.
- The game ends automatically after **3 seconds** on the win screen and closes.
