---
description: Build and Run the Raylib project
---

This workflow helps you build and run your Raylib project on Windows.

1. Clean the project
// turbo
run_command: C:/raylib/w64devkit/bin/mingw32-make.exe clean

2. Build the project
// turbo
run_command: C:/raylib/w64devkit/bin/mingw32-make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=main OBJS=main.cpp BUILD_MODE=DEBUG

3. Run the project
run_command: ./main.exe
