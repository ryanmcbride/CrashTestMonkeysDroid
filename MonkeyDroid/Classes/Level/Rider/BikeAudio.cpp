/*
 *  Vehicle.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "Box2D.h"
#include "SimpleAudioEngine.h"
#include "Rider.h"
#include "BikeAudio.h"
#include "../../FrontEnd/SaveLoad.h"

USING_NS_CC;
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define AUDIO_DIRECTORY "Audio/"
#else
#define AUDIO_DIRECTORY ""
#endif

static BikeAudioDesc s_CHIMPSBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"CHIMPSStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"CHIMPSBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPS1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPS2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPS3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"CHIMPSOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"CHIMPSDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_YellerBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"OldYellerStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"OldYellerBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYeller1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYeller2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYeller3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"OldYellerOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"OldYellerDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_DirtBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"DirtBikeStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"DirtBikeBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBike1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBike2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBike3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"DirtBikeOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"DirtBikeDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_IslandBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"IslandStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"IslandBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Island1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Island2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Island3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"IslandOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"IslandDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_ScifiBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"SciFiStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"SciFiBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFi1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFi2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFi3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"SciFiOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"SciFiDecelLowq.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_ElectricBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"ElectricStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"ElectricBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Electric1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Electric2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"Electric3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"ElectricOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"ElectricDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_McAcmeBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"McAcmeStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"McAcmeBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcme1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcme2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcme3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"McAcmeOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"McAcmeDecelLow.3gp",3.10,BikeAudio::IDLE},
};
static BikeAudioDesc s_PizzaBikeAudioStates[BikeAudio::NUM_STATES] =
{
    {AUDIO_DIRECTORY"",1.0,BikeAudio::START},
    {AUDIO_DIRECTORY"PizzaScooterStart.3gp",2.1,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterIdle.3gp",4.9,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterAccel.3gp",14.55,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterDecel.3gp",6.0,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterReverse.3gp",10.39,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterRough.3gp",2.85,BikeAudio::ROUGH},
    {AUDIO_DIRECTORY"PizzaScooterBounce.3gp",2.8,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooter1Loop.3gp",1.95,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooter2Loop.3gp",4.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooter3Loop.3gp",5.00,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterTurbo1.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterTurbo2.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterTurbo3.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterTurbo4.3gp",4.29,BikeAudio::IDLE},
    {AUDIO_DIRECTORY"PizzaScooterOff.3gp",3.10,BikeAudio::PRESTART},
    {AUDIO_DIRECTORY"PizzaScooterDecelLow.3gp",3.10,BikeAudio::IDLE},
};

void BikeAudio::Preload()
{
    for(int i = 1; i < BikeAudio::NUM_STATES; i++)
    {
        SimpleAudioEngine::sharedEngine()->preloadEffect(m_AudioDesc[i].filename);
    }
}
BikeAudio::BikeAudio()
{
    m_State = 0;
    m_currentSound = 0;
    m_nextSound = 0;
    m_InterpTime = 0.0f;
    m_InterpTimeMax = 0.2f;
    m_bIsPaused = false;
    m_bEnd = false;
    m_LastButtonDown = 0.0f;
    m_Attenuation = 0.5f;
    
    const char *ext = SaveLoad::GetBikeExt();
    
        
    if(strcmp(ext,"_Default")==0)
    {
        m_Attenuation = 0.4f;
        m_AudioDesc = s_YellerBikeAudioStates;
    }
    if(strcmp(ext,"_DirtBike")==0)
        m_AudioDesc = s_DirtBikeAudioStates;
    if(strcmp(ext,"_McAcme")==0)
        m_AudioDesc = s_McAcmeBikeAudioStates;
    if(strcmp(ext,"_Island")==0)
        m_AudioDesc = s_IslandBikeAudioStates;
    if(strcmp(ext,"_SciFi")==0)
        m_AudioDesc = s_ScifiBikeAudioStates;
    if(strcmp(ext,"_Electric")==0)
        m_AudioDesc = s_ElectricBikeAudioStates;
    if(strcmp(ext,"_Pizza")==0)
        m_AudioDesc = s_PizzaBikeAudioStates;
    if(strcmp(ext,"_Police")==0)
        m_AudioDesc = s_CHIMPSBikeAudioStates;
    
    Preload();
}
BikeAudio::~BikeAudio()
{
    SimpleAudioEngine::sharedEngine()->stopEffect(m_currentSound);
    SimpleAudioEngine::sharedEngine()->stopEffect(m_nextSound);
}
void BikeAudio::PushState(AudioStates state)
{
    if(m_InterpTime>0.0f)
    {
        if(m_State != OFF && state==OFF)
            m_bEnd = true;
        return;
    }
    
    if(m_State == OFF)return;
    
    if(m_State == state)
    {
        if(state == ACCEL)
        {
            m_LastButtonDown = 0.0f;
            return;
        }
        if(state == DECEL)return;
        if(state == REVERSE)
        {
            m_LastButtonDown = 0.0f;
            return;
        }
        if(state == BOUNCE)return;
    }
    
    if(state==TURBO1)
    {
        if(m_State==TURBO1)
            state=TURBO2;
        if(m_State==TURBO2)
            state=TURBO3;
        if(m_State==TURBO3)
            state=TURBO4;
        if(m_State==TURBO4)
            state=TURBO4;
    }
    if(m_State>=TURBO1 && m_State<=TURBO4)
    {
        if(state == ACCEL || state == REVERSE)
        {
            if(m_TimeInState < 3.0f)
                return;
        }
    }
    if(m_currentSound == 0)
    {
        m_currentSound = SimpleAudioEngine::sharedEngine()->playEffect(m_AudioDesc[state].filename);
        SimpleAudioEngine::sharedEngine()->setEffectVolume(m_currentSound, 1.0f-m_Attenuation);
        m_State = state;
        return;
    }
    else
    {
        m_InterpTime = m_InterpTimeMax;
        if(state == DECEL && m_TimeInState < 5.0f)
        {
            m_nextSound = SimpleAudioEngine::sharedEngine()->playEffect(m_AudioDesc[DECEL_LOW].filename);
        }
        else
        {
            if(state==IDLE)
            {
                m_nextSound = SimpleAudioEngine::sharedEngine()->playEffect(m_AudioDesc[state].filename,true);
            }
            else
            {
                m_nextSound = SimpleAudioEngine::sharedEngine()->playEffect(m_AudioDesc[state].filename);
            }
        }
        m_TimeInState = 0.0f;
        SimpleAudioEngine::sharedEngine()->setEffectVolume(m_nextSound, 0.0f);
        m_State = state;        
    }
}
void BikeAudio::Pause(bool pause)
{
    if(m_bIsPaused != pause)
    {
        if(pause)
        {
            SimpleAudioEngine::sharedEngine()->pauseEffect(m_currentSound);
            if(m_nextSound)
                SimpleAudioEngine::sharedEngine()->pauseEffect(m_nextSound);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->resumeEffect(m_currentSound);
            if(m_nextSound)
                SimpleAudioEngine::sharedEngine()->resumeEffect(m_nextSound);
        }
        m_bIsPaused = pause;
    }
}
void BikeAudio::Update(float dt)
{
    if(m_InterpTime>0.0f)
    {
        m_InterpTime -= dt;
        if(m_InterpTime>0.0f)
        {
            float percent = m_InterpTime/m_InterpTimeMax;
            SimpleAudioEngine::sharedEngine()->setEffectVolume(m_currentSound, percent*m_Attenuation);
            SimpleAudioEngine::sharedEngine()->setEffectVolume(m_nextSound, (1.0f-percent)*m_Attenuation);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->stopEffect(m_currentSound);
            
            m_currentSound = m_nextSound;
            m_nextSound = 0;
        }
        return;
    }
    if(Rider::g_isCrashed && m_State != OFF)
    {
        SimpleAudioEngine::sharedEngine()->stopEffect(m_currentSound);
        m_currentSound = 0;
        if(m_nextSound != 0)
        {
            SimpleAudioEngine::sharedEngine()->stopEffect(m_nextSound);
        }
        m_State = OFF;
    }
    m_TimeInState += dt;
    switch(m_State)
    {
        case OFF:
            m_bEnd = false;
            break;
        case IDLE:
            break;
        case PRESTART:
            PushState(START);
            break;
        case ACCEL:
            if(m_bEnd)
                PushState(OFF);
            if(m_TimeInState >= 0.2f && (m_TimeInState-dt)<0.2f)
                DoExhaust();
            if(m_TimeInState > (m_AudioDesc[m_State].length-m_InterpTimeMax))
                PushState((AudioStates)m_AudioDesc[m_State].nextState);
            else
            {
                m_LastButtonDown+=dt;
                if(m_LastButtonDown>0.5f)
                    PushState(DECEL);
            }
            break;
        case REVERSE:
            m_LastButtonDown+=dt;
            if(m_bEnd)
                PushState(OFF);
            if(m_TimeInState > (m_AudioDesc[m_State].length-m_InterpTimeMax))
                PushState((AudioStates)m_AudioDesc[m_State].nextState);
            else
            {
                m_LastButtonDown+=dt;
                if(m_LastButtonDown>0.5f)
                    PushState(DECEL);
            }
            break;
        default:
            if(m_bEnd)
                PushState(OFF);
            if(m_TimeInState > (m_AudioDesc[m_State].length-m_InterpTimeMax))
                PushState((AudioStates)m_AudioDesc[m_State].nextState);
            break;
    }
}
void BikeAudio::DoExhaust()
{
    const char *ext = SaveLoad::GetBikeExt();
    if(!(strcmp(ext,"_SciFi")==0 || strcmp(ext,"_Electric")==0))
    {
        if(Rider::g_MainBody->GetLinearVelocity().x > 10)
            return;
        
        /*[[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"ctm_VFX.plist"textureFile:@"ctm_VFX.pvr.ccz"];
        
        NSString *name = [NSString stringWithFormat:@"ctm%@_Exhaust.png",ext];
        CCSprite *exhaust1 = [CCSprite spriteWithSpriteFrameName:name];
        CCSprite *exhaust2 = [CCSprite spriteWithSpriteFrameName:name];
        CGPoint vel = ccp(Rider::g_MainBody->GetLinearVelocity().x*PTM_RATIO,0.0);
        exhaust1.position = ccp(Rider::g_MainBody->GetWorldCenter().x*PTM_RATIO-30.0f,Rider::g_MainBody->GetWorldCenter().y*PTM_RATIO);
        exhaust2.position = ccp(exhaust1.position.x-30,exhaust1.position.y);
        exhaust1.scale = 0.01f;
        CCSequence *sequence = [CCSequence actions:
                                [CCDelayTime actionWithDuration:0.05f],
                                [CCScaleTo actionWithDuration:0.25f scale:1.5f],
                                [CCCallFuncND actionWithTarget:exhaust1 selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                [CCCallFuncND actionWithTarget:exhaust1 selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                nil];
        [exhaust1 runAction:sequence];
        sequence = [CCSequence actions:
                    [CCDelayTime actionWithDuration:0.15f],
                    [CCFadeOut actionWithDuration:0.15f],
                    nil];
        [exhaust1 runAction:sequence];
        
        exhaust2.scale = 0.01f;
        sequence = [CCSequence actions:
                    [CCScaleTo actionWithDuration:0.25f scale:1.5f],
                    [CCCallFuncND actionWithTarget:exhaust2 selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                    [CCCallFuncND actionWithTarget:exhaust2 selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                    nil];
        [exhaust2 runAction:sequence];
        sequence = [CCSequence actions:
                    [CCDelayTime actionWithDuration:0.10f],
                    [CCFadeOut actionWithDuration:0.15f],
                    nil];
        [exhaust2 runAction:sequence];
        CCNode* layer = ((TextureObject*)Rider::g_MainBody->GetUserData())->GetSprite().parent.parent;
        [layer addChild:exhaust1];
        [layer addChild:exhaust2];
        
        [exhaust1 runAction:[CCMoveBy actionWithDuration:1.0 position:vel]];
        [exhaust2 runAction:[CCMoveBy actionWithDuration:1.0 position:vel]];*/
    }
}
