#include"AudioSystem.h"

void AudioSystem::Init()
{
    InitAudioDevice();
    
    sounds.resize(4);
    sounds[CoinCollectedSound] = LoadSound("mario/Audio/coinCollected.wav");
    sounds[BrickDestroySound] = LoadSound("mario/Audio/breakBrick.wav");
    sounds[JumpSound]=LoadSound("mario/Audio/JumpSound.wav");
    sounds[StompSound]=LoadSound("mario/Audio/stompSound.wav");
    
    musicStreams.resize(3);
    musicStreams[GAME_MUSIC] = LoadMusicStream("mario/Audio/MainBGM.mp3");
    musicStreams[DEATH_MUSIC] = LoadMusicStream("mario/Audio/deathMusic.wav");
    musicStreams[GAME_OVER_MUSIC] = LoadMusicStream("mario/Audio/deathMusic.wav");
}

void AudioSystem::Update(float dt)
{
    UpdateMusicStream(musicStreams[(int)currentMusic]);
}

void AudioSystem::PlayMusic(MusicFiles musicId)
{
    StopMusicStream(musicStreams[(int)currentMusic]);
    currentMusic = musicId;
    PlayMusicStream(musicStreams[(int)currentMusic]);
}

void AudioSystem::StopMusic()
{
    StopMusicStream(musicStreams[(int)currentMusic]);
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
    for (Music& m : musicStreams) {
        UnloadMusicStream(m);
    }
    CloseAudioDevice();
}