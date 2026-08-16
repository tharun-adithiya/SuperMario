#include"AudioSystem.h"

void AudioSystem::Init()
{
    InitAudioDevice();
    
    sounds.resize(2);
    sounds[CoinCollectedSound] = LoadSound("mario/Audio/coinCollected.wav");
    sounds[BrickDestroySound] = LoadSound("mario/Audio/breakBrick.wav");
}

void AudioSystem::Update(float dt)
{
    UpdateMusicStream(musicSource);
}

void AudioSystem::LoadMusic(string musicPath)
{
    if(FileExists(musicPath.c_str()))
        musicSource=LoadMusicStream(musicPath.c_str());
}

void AudioSystem::PlayMusic()
{
    PlayMusicStream(musicSource);
}

void AudioSystem::PlaySoundEffect(SoundFiles soundId)
{
    if ((int)soundId >= 0 && (int)soundId < sounds.size()) {
        cout<<"Sound Plays";
        PlaySound(sounds[(int)soundId]);
    }
}

void AudioSystem::ShutDown()
{
    for (Sound& s : sounds) {
        UnloadSound(s);
    }
    CloseAudioDevice();
}