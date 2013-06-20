//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __SAVE_LOAD_H__
#define __SAVE_LOAD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

#define TUTORIAL_LEVELSTART 0
#define ISLAND_LEVELSTART 8
#define CITY_LEVELSTART 16
#define NIGHT_LEVELSTART 24
#define SPACE_LEVELSTART 32
#define BONUS_LEVELSTART 40
#define REGULAR_LEVELS (BONUS_LEVELSTART-1)

class SaveLoad
{
public:
    
    static struct SaveData
	{
		int bHasBeenPlayed;
		unsigned int currency;
        int backgroundsUnlocked;
		int costumesUnlocked;
        int currentCostume;
        int vehiclesUnlocked;
        int currentVehicle;
        int trampLockLevel;
        int turboLockLevel;
        int flipLockLevel;
        int trickLockLevel;
        int timeLockLevel;
        int peanutLockLevel;
        int fireLockLevel;
        int numDoubleNuts;
        int numTimeSlow;
        int numLevelFire;
        int characters[20];
        int bikes[20];
        int commercialIndex;
        int medalLockLevel;
        int objectives[50];
        int levelflags[200];//level 0 is training
        int currentLevel;
        int currentHint;
        int crashCount;
        int64_t trickHiScore;
        float sfxVolume;
        float musicVolume;
        int beenToStore;
        int beenToPeanuts;
        int used2X;
        int usedFire;
        int usedTime;
        int hasRated;
	} m_SaveData;
    enum levelFlags
    {
        UNLOCKED = 0x00000001,
        SELECTED = 0x00000002,
        ONE_COCONUT = 0x00000004,
        TWO_COCONUT = 0x00000008,
        THREE_COCONUT = 0x00000010,
        HINT_DISPLAY = 0x00000020,
        MAX_INT =  0xffffffff,
    };
    enum objective_flags
    {
        TRIPLE_LINDY = 0,
        PEANUT_ENVY = 1,
        RIDERS_BLOCK = 2,
        THATS_NO_MOON = 3,
        ITS_OVER_9000 = 4,
        IN_SOVIET_RUSSIA = 5,
        THIS_IS_SPARTA = 6,
        THE_MINUS_WORLD = 7,
        HOT_COFFEE_MOD = 8,
        JUMP_THE_SHARK = 9,
        MISSION_ACCOMPLISHED = 10,
        BEAT_UP_THE_BEAT = 11,
        MEH = 12,
        OMGWTFBBQ_FTW = 13,
        ROAD_KILL = 14,
        MAX = 0xffffffff
    };
    static void Init();
    static void Release();
    static void Save();
    static void Load();
    static int NumGoldMedals();
    static int NumSilverMedals();
    static int NumBronzeMedals();
    static int DoNightMedalCount();
    static int DoSpaceMedalCount();
    static const char* GetBikeExt();
    static int GetRiderNumber();
private:
    

};

#endif // __SAVE_LOAD_H__
