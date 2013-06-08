/*
 *  Fire.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __BIKE_AUDIO_H__
#define __BIKE_AUDIO_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

struct BikeAudioDesc
{
    const char* filename;
    float length;
    int nextState;
};
class BikeAudio
{
public:
    enum AudioStates
    {
        PRESTART = 0,
        START = 1,
        IDLE = 2,
        ACCEL = 3,
        DECEL = 4,
        REVERSE = 5,
        ROUGH = 6,
        BOUNCE = 7,
        LOOP1 = 8,
        LOOP2 = 9,
        LOOP3 = 10,
        TURBO1 = 11,
        TURBO2 = 12,
        TURBO3 = 13,
        TURBO4 = 14,
        OFF = 15,
        DECEL_LOW = 16,
        NUM_STATES = 17,
    };
    BikeAudio();
    ~BikeAudio();
    void PushState(AudioStates state);
    void Pause(bool pause);
    void Update(float dt);
    void Preload();
protected:
    void DoExhaust();
    bool m_bEnd;
    bool m_bIsPaused;
    unsigned int m_currentSound;
    unsigned int m_nextSound;
    BikeAudioDesc *m_AudioDesc;
    int m_State;
    float m_TimeInState;
    float m_InterpTime;
    float m_InterpTimeMax;
    float m_LastButtonDown;
    float m_Attenuation;
};
#endif