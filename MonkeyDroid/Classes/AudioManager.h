//
//  Options.h
//  CTM
//
//  Created by Ryan McBride on 1/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"

#define AUDIO_CHICKENS              0
#define AUDIO_COWS                  1
#define AUDIO_ARMADILLO             ((3<<16)|2)//2,3,4
#define AUDIO_ARMADILLO1             2
#define AUDIO_ARMADILLO2             3
#define AUDIO_ARMADILLO3             4
#define AUDIO_BEACH_BALL            ((7<<16)|5)//5,6,7,8,9,10,11
#define AUDIO_CENSORED              12
#define AUDIO_COLLECT_ITEM          13
#define AUDIO_FINISH_LINE           14
#define AUDIO_FIREWORKS             15
#define AUDIO_LAUGH_TRACK           ((3<<16)|16)//16,17,18
#define AUDIO_PORCUPINE             19
#define AUDIO_BRONZE_MEDAL          20
#define AUDIO_FEEDBACK_NEGATIVE     21
#define AUDIO_FEEDBACK_POSITIVE     22
#define AUDIO_GOLD_MEDAL            23
#define AUDIO_SILVER_MEDAL          24
#define AUDIO_STATS_POPUP           25
#define AUDIO_STARTCLOCK_GO         26
#define AUDIO_STARTCLOCK_TICK       27
#define AUDIO_SWING_HIT             28
#define AUDIO_LEVEL_SWOOSH          29
#define AUDIO_SELECT                30
#define AUDIO_WATER_TANK            31
#define AUDIO_TURBO_STRIP           ((3<<16)|32)//32,33,34
#define AUDIO_BIKE_LAND             35
#define AUDIO_BIKE_CRASH            36
#define AUDIO_BIKE_HARD_IMPACT      37
#define AUDIO_BIKE_SOFT_IMPACT      38
#define AUDIO_BIKE_TIRE_CHIRP       39

#define AUDIO_CHAR_LOOP1            40
#define AUDIO_CHAR_LOOP2            41
#define AUDIO_CHAR_LOOP3            42
#define AUDIO_CHAR_FINISH           43
#define AUDIO_CHAR_FRUSTRATED       44
#define AUDIO_CHAR_JUMP             45
#define AUDIO_CHAR_PAIN             46
#define AUDIO_CHAR_START            47
#define AUDIO_CHAR_TRICK_FLIP       48
#define AUDIO_CHAR_TRICK_NO_FLIP    49

#define AUDIO_FAIL_STINGER_CITY     50
#define AUDIO_FAIL_STINGER_ISLAND   51
#define AUDIO_CHAR_DROWN            52
#define AUDIO_FAIL_STINGER_SPACE    53
#define AUDIO_BR_BLINK              54
#define AUDIO_BR_FART               55
#define AUDIO_BR_PUNCH              56
#define AUDIO_NEWS_ANCHOR           ((2<<16)|57)//57,58
#define AUDIO_TRIGGER               59
#define AUDIO_FAIL_STINGER_NIGHT    60

#define NUM_AUDIO                   61

class AudioManager
{
public:
    static void PreloadAudio();
    static void UpdateAudio(float dt);
    static void FadeOutAudio();
    static void FadeInAudio();
    static void AudioOn();
    static void AudioOff();
    static unsigned int PlayEffect(int sfxID,float chance=1.0f);
    static void MuteEngine();
    static float g_MasterSFXAudio;
    static float g_MasterMusicAudio;
};

#endif
