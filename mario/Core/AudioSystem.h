#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

enum MusicFiles
{
    GAME_MUSIC,
    DEATH_MUSIC,
    GAME_OVER_MUSIC
};

enum SoundFiles
{
    CoinCollectedSound,
    BrickDestroySound,
    JumpSound,
    StompSound,
};

class AudioSystem
{
    private:
        std::vector<Music> musicStreams;
        MusicFiles currentMusic = GAME_MUSIC;
        std::vector<Sound> sounds;
    public: 
        static AudioSystem Instance;
        void Update(float dt);
        void Init();
        void PlayMusic(MusicFiles musicId);
        void StopMusic();
        void PlaySoundEffect(SoundFiles soundId);
        void ShutDown();
};