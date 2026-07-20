#include "Animation.h"

void Animation::AnimationUpdate(float dt)
{
    duration_left-=dt;
    if(duration_left<=0)
    {
        duration_left=this->speed;
        currentFrame++;
        if(currentFrame>lastFrame)
        {
            currentFrame=firstFrame;
        }
    }
    
}

Rectangle Animation::AnimationFrame(int numberOfFramesPerRow)
{
    int x= (currentFrame%numberOfFramesPerRow)*16;
    int y= (currentFrame/numberOfFramesPerRow)*16;
    return Rectangle((float)x,(float)y,16,16);
}