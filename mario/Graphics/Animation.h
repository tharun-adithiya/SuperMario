#include "raylib.h"
#pragma once
struct Animation
{
    int firstFrame;
    int lastFrame;
    int currentFrame;
    float speed;
    float duration_left;

    Animation()
    {
        firstFrame=-1;
        lastFrame=-1;
        currentFrame=-1;
        speed=0;
    }
    Animation(int firstFrame,int lastFrame, int currentFrame,float speed,float duration_left) : firstFrame(firstFrame), 
    lastFrame(lastFrame), currentFrame(currentFrame), speed(speed), duration_left(duration_left)
    {}
    void AnimationUpdate(float dt);
    Rectangle AnimationFrame(int numberOfFramesPerRow);

};

