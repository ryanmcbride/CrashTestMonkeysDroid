//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "cocos2d.h"
#include "SaveLoad.h"
#include "LocalStorage.h"
#include "../AudioManager.h"
#include <string>


USING_NS_CC;


SaveLoad::SaveData SaveLoad::m_SaveData;

void SaveLoad::Init()
{
    char path[256];
    sprintf(path,"%s%s",CCFileUtils::sharedFileUtils()->getWriteablePath().c_str(),"CTMData.bin");
    localStorageInit(path);
    
    Load();
    
}
void SaveLoad::Release()
{
    localStorageFree();
}

void SaveLoad::Save()
{
    localStorageSetItem("SaveGame",(char*)&m_SaveData,sizeof(SaveLoad::SaveData));
}
void SaveLoad::Load()
{
    const char *value = localStorageGetItem("SaveGame");
    if(value)
    {
        memcpy(&m_SaveData,value, sizeof(SaveLoad::SaveData));
        //delete value;
    }
    else
    {
        memset(&m_SaveData,0,sizeof(SaveLoad::SaveData));
        
        memset(&m_SaveData,0,sizeof(m_SaveData));
        m_SaveData.currency = 0;
        m_SaveData.commercialIndex = 5;
        m_SaveData.currentLevel = 1;
        m_SaveData.trampLockLevel = 1;
        //m_SaveData.turboLockLevel = 2;
        m_SaveData.characters[0] |= UNLOCKED;
        m_SaveData.characters[0] |= SELECTED;
        m_SaveData.bikes[0] |= UNLOCKED;
        m_SaveData.bikes[0] |= SELECTED;
        m_SaveData.levelflags[TUTORIAL_LEVELSTART] |= UNLOCKED;
        //m_SaveData.levelflags[ISLAND_LEVELSTART] |= UNLOCKED;
        m_SaveData.levelflags[CITY_LEVELSTART] |= UNLOCKED;
        m_SaveData.levelflags[NIGHT_LEVELSTART] |= UNLOCKED;
        m_SaveData.levelflags[SPACE_LEVELSTART] |= UNLOCKED;
        
        for(int i = TUTORIAL_LEVELSTART; i < SPACE_LEVELSTART+8; i++)
        {
            m_SaveData.levelflags[i] |= UNLOCKED;
            m_SaveData.levelflags[i] |= ONE_COCONUT;
        }
        
        m_SaveData.musicVolume = 1.0f;
        m_SaveData.sfxVolume = 1.0f;
        
    }
    AudioManager::g_MasterMusicAudio = m_SaveData.musicVolume;
    AudioManager::g_MasterSFXAudio = m_SaveData.sfxVolume;
    AudioManager::AudioOn();
}
const char* SaveLoad::GetBikeExt()
{
    
    int bikenum = 0;
    int i;
    for(i = 0; i < 8; i++)
    {
        if(m_SaveData.bikes[i] & SELECTED)
        {
            bikenum = i;
            break;
        }
    }
    switch(bikenum)
    {
        case 0:
            return "_Default";
        case 1:
            return "_DirtBike";
        case 2:
            return "_McAcme";
        case 3:
            return "_Island";
        case 4:
            return "_SciFi";
        case 5:
            return "_Electric";
        case 6:
            return "_Pizza";
        case 7:
            return "_Police";
    }
    
    return "_Default";
}
int SaveLoad::GetRiderNumber()
{
    int charnum = 0;
    int i;
    for(i = 0; i < 5; i++)
    {
        if(m_SaveData.characters[i] & SELECTED)
        {
            charnum = i;
            break;
        }
    }
    return charnum;
}

int SaveLoad::NumGoldMedals()
{
    int medalCount = 0;
    for(int i = ISLAND_LEVELSTART; i <= REGULAR_LEVELS; i++)
    {
        if(m_SaveData.levelflags[i] & THREE_COCONUT)
        {
            medalCount++;
        }
    }
    return medalCount;
}
int SaveLoad::NumSilverMedals()
{
    int medalCount = 0;
    for(int i = ISLAND_LEVELSTART; i <= (REGULAR_LEVELS); i++)
    {
        if(m_SaveData.levelflags[i] & TWO_COCONUT)
        {
            medalCount++;
        }
    }
    return medalCount;

}

int SaveLoad::NumBronzeMedals()
{
    int medalCount = 0;
    for(int i = ISLAND_LEVELSTART; i <= (REGULAR_LEVELS); i++)
    {
        if(m_SaveData.levelflags[i] & ONE_COCONUT)
        {
            medalCount++;
        }
    }
    return medalCount;
}
int SaveLoad::DoNightMedalCount()
{
    int medalCount = 0;
    int startLevel = NIGHT_LEVELSTART;
    int endLevel = NIGHT_LEVELSTART+8;
    for(int i = startLevel; i <= endLevel; i++)
    {
        if(m_SaveData.levelflags[i] & THREE_COCONUT)
        {
            medalCount++;
        }
    }
    return medalCount;
}
int SaveLoad::DoSpaceMedalCount()
{
    int medalCount = 0;
    int startLevel = SPACE_LEVELSTART;
    int endLevel = SPACE_LEVELSTART+8;
    for(int i = startLevel; i <= endLevel; i++)
    {
        if(m_SaveData.levelflags[i] & THREE_COCONUT)
        {
            medalCount++;
        }
    }
    return medalCount;
}


