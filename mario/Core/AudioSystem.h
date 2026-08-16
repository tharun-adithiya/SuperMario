#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

enum SoundFiles
{
    CoinCollectedSound,
    BrickDestroySound
};

class AudioSystem
{
    private:
        Music musicSource;
        std::vector<Sound> sounds;
    public: 
        static AudioSystem Instance;
        void Update(float dt);
        void Init();
        void LoadMusic(string musicPath);
        void PlayMusic();
        void PlaySoundEffect(SoundFiles soundId);
        void ShutDown();
};