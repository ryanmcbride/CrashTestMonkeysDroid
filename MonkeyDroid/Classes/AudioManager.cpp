//
//  Objectives.mm
//  CTM
//
//  Created by Ryan McBride on 1/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AudioManager.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

struct AudioDef
{
    const char *file;
    float gain;
    float pitch;
    float pan;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define AUDIO_DIRECTORY "Audio/"
#else
#define AUDIO_DIRECTORY ""
#endif

static bool s_bFadeOut = false;
static bool s_bFadeIn = false;

AudioDef g_AudioFiles[NUM_AUDIO] = {
    /*0*/    {AUDIO_DIRECTORY"Chickens.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Cows.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Armadillo1.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Armadillo2.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Armadillo3.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Beachball1.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BeachBall2.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BeachBall3.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BeachBall4.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BeachBall5.3gp",1.0f,1.0f,0.0f},
    
    /*0*/    {AUDIO_DIRECTORY"BeachBall6.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BeachBall7.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Censored.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CollectItem.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"FinishLine.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Fireworks.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"LaughTrack1.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"LaughTrack2.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"LaughTrack3.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Porcupine.3gp",1.0f,1.0f,0.0f},

    /*0*/    {AUDIO_DIRECTORY"BronzeMedal.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"FeedbackNegative.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"FeedbackPositive.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"GoldMedal.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"SilverMedal.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"StatsPopUp.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"StartClockGo.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"StartClockTick.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"SwingHit.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"LevelSwoosh.3gp",1.0f,1.0f,0.0f},
    
    /*0*/    {AUDIO_DIRECTORY"Select.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"WaterTank.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"TurboStrip1.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"TurboStrip2.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"TurboStrip3.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"BikeLand.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Crash.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"HardImpact.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"SoftImpact.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"TireChirp.3gp",1.0f,1.0f,0.0f},
    
    /*0*/    {AUDIO_DIRECTORY"JM1Loop.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JM2Loop.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JM3Loop.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMFinishLine.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMFrustrated.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMJump.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMPain.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMStart.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMTrickFlip.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"JMTrickNoFlip.3gp",1.0f,1.0f,0.0f},

    /*0*/    {AUDIO_DIRECTORY"CTMCityFailStinger.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMIslandFailStinger.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Drown.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMSpaceFailStinger.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"EyeBlink.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Fart.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"Punch.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMNewsMonkey1.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMNewsMonkey2.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMTrigger.3gp",1.0f,1.0f,0.0f},
    /*0*/    {AUDIO_DIRECTORY"CTMNightFailStinger.3gp",1.0f,1.0f,0.0f},
};

float AudioManager::g_MasterSFXAudio = 1.0f;
float AudioManager::g_MasterMusicAudio = 1.0f;

void AudioManager::PreloadAudio()
{
    int i;
    for(i = 0; i < NUM_AUDIO; i++)
    {
        SimpleAudioEngine::sharedEngine()->preloadEffect(g_AudioFiles[i].file);
    }
}
void AudioManager::UpdateAudio(float dt)
{
    if(s_bFadeOut)
    {
        bool canFadeOut = false;
        bool canFadeOut2 = false;
        float volume = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
        if(volume > 0.0f)
        {
            volume -= dt;
            if(volume < 0.0f)
            {
                canFadeOut = true;
                volume = 0.0f;
            }
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
        }
        volume = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
        if(volume > 0.0f)
        {
            volume -= dt;
            if(volume < 0.0f)
            {
                canFadeOut2 = true;
                volume = 0.0f;
            }
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
        }
        if(canFadeOut && canFadeOut2)
            s_bFadeOut = false;
    }
    
    if(s_bFadeIn)
    {
        bool canFadeOut = false;
        bool canFadeOut2 = false;
        float volume = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
        if(volume < g_MasterSFXAudio)
        {
            volume += dt;
            if(volume > g_MasterSFXAudio)
            {
                canFadeOut = true;
                volume = g_MasterSFXAudio;
            }
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
        }
        volume = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
        if(volume < g_MasterMusicAudio)
        {
            volume += dt;
            if(volume > g_MasterMusicAudio)
            {
                canFadeOut2 = true;
                volume = g_MasterMusicAudio;
            }
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
        }
        if(canFadeOut && canFadeOut2)
            s_bFadeIn = false;
    }
    
}
void AudioManager::FadeOutAudio()
{
    s_bFadeOut = true;
}
void AudioManager::FadeInAudio()
{
    s_bFadeIn = true;
}
void AudioManager::AudioOn()
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(g_MasterMusicAudio);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(g_MasterSFXAudio);
    s_bFadeOut = false;
}
void AudioManager::AudioOff()
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);    
    s_bFadeIn = false;
}
unsigned int AudioManager::PlayEffect(int sfxID, float chance)
{
    bool play = false;
    
    if(chance==1.0f)
        play=true;
    else
        play = CCRANDOM_0_1()<chance?true:false;
    
    if(play)
    {
        if(sfxID & (0xffff<<16))
        {
            int newID = RandomInt(sfxID&0xffff,(sfxID&0xffff)+(sfxID>>16));
            return SimpleAudioEngine::sharedEngine()->playEffect(g_AudioFiles[newID].file);// pitch:g_AudioFiles[newID].pitch pan:g_AudioFiles[newID].pan gain:g_AudioFiles[newID].gain];
        }
        else
        {
            return SimpleAudioEngine::sharedEngine()->playEffect(g_AudioFiles[sfxID].file);// pitch:g_AudioFiles[sfxID].pitch pan:g_AudioFiles[sfxID].pan gain:g_AudioFiles[sfxID].gain];
        }
    }
    return 0;
}
void AudioManager::MuteEngine()
{
    //mute bike here
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}