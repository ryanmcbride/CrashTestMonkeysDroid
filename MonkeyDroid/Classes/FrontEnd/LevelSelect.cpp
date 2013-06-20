//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "LevelSelect.h"
#include "SimpleAudioEngine.h"
#include "RegionSelect.h"
#include "ScreenHelper.h"
#include "Loading.h"
#include "SaveLoad.h"

using namespace cocos2d;
using namespace CocosDenshion;

int LevelSelect::m_LastRegionID = 0;
int LevelSelect::s_LevelID = 0;
char LevelSelect::s_LevelName[64];



LevelSelect::LevelSelect()
{
    setTouchEnabled( true );
}
void LevelSelect::Init(REGIONID regionID)
{
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMThemeMusicv3.3gp", true);
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("LevelSelectIcon.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LevelSelectIcon.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("LevelSelect.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LevelSelect.plist");
    
    
    CCSprite *sprite = CCSprite::create("MainBackFiller.png");
    sprite->setScaleX(scaleX*1.2f);
    sprite->setScaleY(scaleY*1.2f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-32.0f));
    addChild(sprite);
    
    sprite = CCSprite::create("ctm_UI_topOverlayA_ver1.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite,2);
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(LevelSelect::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    const char *name = NULL;
    int levels = 0;
    const char *icons[4];
    switch(regionID)
    {
        case REGION_TUTORIAL:
            name = "TUTORIAL";
            levels = 6;
            icons[0] = "TutorialIcon_1.png";
            icons[1] = "TutorialIcon_2.png";
            break;
        case REGION_TIKI:
            name = "ISLAND";
            levels = 8;
            icons[0] = "IslandIcon_1.png";
            icons[1] = "IslandIcon_2.png";
            break;
        case REGION_CITY:
            name = "CITY";
            levels = 8;
            icons[0] = "CityIcon_1.png";
            icons[1] = "CityIcon_2.png";
            break;
        case REGION_NIGHT:
            name = "NIGHT";
            levels = 8;
            icons[0] = "NightIcon_1.png";
            icons[1] = "NightIcon_2.png";
            break;
        case REGION_SPACE:
            name = "SPACE";
            levels = 8;
            icons[0] = "SpaceIcon_1.png";
            icons[1] = "SpaceIcon_2.png";
            break;
        case REGION_BONUS:
            name = "BONUS";
            levels = 4;
            icons[0] = "IslandIcon_1.png";
            icons[1] = "CityIcon_2.png";
            icons[2] = "NightIcon_1.png";
            icons[3] = "SpaceIcon_2.png";
           break;
        default:
            name = "OOOPS";
            break;
    }
    
    
    CCLabelTTF *label = CCLabelTTF::create(name, "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create(name, "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    int i;
    if(levels==6)//tutorial
    {
        for(i = 0; i < levels; i++)
        {
            int mod = 0;
            CCMenuItem *LevelButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(icons[i%2==mod]), CCSprite::createWithSpriteFrameName(icons[i%2==mod]), this, menu_selector(LevelSelect::levelButtonTapped));
            LevelButton->setScale(scale*0.8f);
            CCPoint p;
            p.x = -100 + 100 * (i>=(levels/2)?(i-levels/2):i);
            p.y = -30+(i>=(levels/2)?-50:50);
            LevelButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,p.x,p.y));
            addButtonInfo(LevelButton, regionID, i);
            menu->addChild(LevelButton);
            m_Buttons[i] = LevelButton;
        }
    }
    else if (levels==4)//bonus
    {
        for(i = 0; i < levels; i++)
        {
            CCMenuItem *LevelButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(icons[i]), CCSprite::createWithSpriteFrameName(icons[i]), this, menu_selector(LevelSelect::levelButtonTapped));
            LevelButton->setScale(scale*0.8f);
            CCPoint p;
            p.x = -150 + 100 * i;
            p.y = -30;
            LevelButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,p.x,p.y));
            addButtonInfo(LevelButton, regionID, i);
            menu->addChild(LevelButton);
            m_Buttons[i] = LevelButton;
        }
    }
    else
    {
        for(i = 0; i < levels; i++)
        {
            int mod = 0;
            if(i>=levels/2)
                mod = 1;
            CCMenuItem *LevelButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(icons[i%2==mod]), CCSprite::createWithSpriteFrameName(icons[i%2==mod]), this, menu_selector(LevelSelect::levelButtonTapped));
            LevelButton->setScale(scale*0.8f);
            CCPoint p;
            p.x = -150 + 100 * (i>=(levels/2)?(i-levels/2):i);
            p.y = -30+(i>=(levels/2)?-50:50);
            LevelButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,p.x,p.y));
            addButtonInfo(LevelButton, regionID, i);
            menu->addChild(LevelButton);
            m_Buttons[i] = LevelButton;
        }
    }
}
void LevelSelect::addButtonInfo(cocos2d::CCNode *node, REGIONID regionID, int number)
{
    char num[8];
    sprintf(num,"%d",number+1);
    
    int leveloffset = ISLAND_LEVELSTART;
    if(regionID==LevelSelect::REGION_CITY)
        leveloffset = CITY_LEVELSTART;
    if(regionID==LevelSelect::REGION_NIGHT)
        leveloffset = NIGHT_LEVELSTART;
    if(regionID==LevelSelect::REGION_SPACE)
        leveloffset = SPACE_LEVELSTART;
    if(regionID==LevelSelect::REGION_TUTORIAL)
        leveloffset = TUTORIAL_LEVELSTART;
    
    leveloffset += number;
    
//number
    if(SaveLoad::m_SaveData.levelflags[leveloffset] & SaveLoad::UNLOCKED)
    {
        CCLabelTTF *label = CCLabelTTF::create(num, "Jacoby ICG Black.ttf", 50);
        node->addChild(label, 2);
        label->setColor(ccc3(0,0,0));
        label->setPosition(ccp(82.0f,78.0f));
        
        label = CCLabelTTF::create(num, "Jacoby ICG Black.ttf", 50);
        node->addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(80.0f,80.0f));
        
//medals
        if(regionID != REGION_TUTORIAL && regionID != REGION_BONUS)
        {
            int numMedals = 0;
            
            if(SaveLoad::m_SaveData.levelflags[leveloffset] & SaveLoad::ONE_COCONUT)
                numMedals++;
            if(SaveLoad::m_SaveData.levelflags[leveloffset] & SaveLoad::TWO_COCONUT)
                numMedals++;
            if(SaveLoad::m_SaveData.levelflags[leveloffset] & SaveLoad::THREE_COCONUT)
                numMedals++;
            
            const char* medalNames[3] =
            {
                "Levelselect_BronzeMedal.png",
                "Levelselect_SilverMedal.png",
                "Levelselect_GoldMedal.png"
            };
            for(int i = 0; i < numMedals; i++)
            {
                CCSprite *medal = CCSprite::createWithSpriteFrameName(medalNames[i]);
                node->addChild(medal);
                medal->setScale(0.5f);
                medal->setPosition(ccp(40+33*i,20.0f));
            }
        }
    }
//lock
    else
    {
        CCSprite *lock = CCSprite::create("ctm_Lock.png");
        node->addChild(lock);
        lock->setScale(0.9f);
        lock->setPosition(ccp(80.0f,75.0f));
        ((CCMenuItem*)node)->setEnabled(false);
    }
    
}


void LevelSelect::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(RegionSelect::scene());
}
void LevelSelect::levelButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    
    for(int i = 0; i < 8; i ++)
    {
        if(m_Buttons[i] == object)
        {
            s_LevelID = (int)m_LastRegionID*8 + i;
        }
    }
    CCDirector::sharedDirector()->replaceScene(Loading::scene());
}
const char* LevelSelect::getLevelName()
{
    const char *level = NULL;
    switch(s_LevelID/8)
    {
        default:
        case 0:
            level = "Tutorial";
            break;
        case 1:
            level = "Island";
            break;
        case 2:
            level = "City";
            break;
        case 3:
            level = "Night";
            break;
        case 4:
            level = "Space";
            break;
        case 5:
            level = "Bonus";
            break;
    }
    sprintf(s_LevelName,"%s %d",level,(s_LevelID%8)+1);
    return s_LevelName;
}
const char* LevelSelect::getLevelXMLName()
{
    const char *level = NULL;
    switch(s_LevelID/8)
    {
        default:
        case 0:
            level = "Tutorial";
            break;
        case 1:
            level = "Tiki";
            break;
        case 2:
            level = "City";
            break;
        case 3:
            level = "NightCity";
            break;
        case 4:
            level = "Space";
            break;
        case 5:
            level = "Bonus";
            break;
    }
    if(s_LevelID<=7)
        sprintf(s_LevelName,"Tutorial7.xml");
    else
        sprintf(s_LevelName,"%s%d.xml",level,(s_LevelID%8)+1);
    return s_LevelName;
}

void LevelSelect::setNextLevel()
{
    if(s_LevelID <= 7)
        s_LevelID = 8;
    else
        s_LevelID++;
    
    m_LastRegionID = s_LevelID/8;
}
int LevelSelect::getCurrentLevel()
{
    return s_LevelID;
}
LevelGoals s_Goals[44][3] =
{
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},//TUTORIAL
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,0,200},{26.0f,200,6000},{20.0f,390,30000}},//TIKI
    {{31.0f,0,500},{20.0f,200,10000},{15.0f,350,30000}},
    {{40.0f,0,1000},{42.0f,250,22000},{38.0f,350,40000}},
    {{40.0f,0,1000},{30.0f,250,10000},{32.0f,400,40000}},
    {{35.0f,0,600},{28.0f,200,5000},{30.0f,400,20000}},
    {{40.0f,0,400},{28.0f,150,10000},{30.0f,240,30000}},
    {{40.0f,0,400},{25.0f,100,9000},{30.0f,350,30000}},
    {{35.0f,0,600},{30.0f,175,10000},{40.0f,350,30000}},
    {{50.0f,0,3500},{45.0f,210,25000},{40.0f,350,30000}},//CITY
    {{35.0f,0,2000},{30.0f,300,20000},{40.0f,350,30000}},
    {{28.0f,0,1200},{35.0f,175,9000},{40.0f,275,30000}},
    {{35.0f,0,4000},{30.0f,150,10000},{40.0f,350,30000}},
    {{50.0f,0,7000},{45.0f,200,20000},{40.0f,350,30000}},
    {{50.0f,0,3000},{45.0f,1,10000},{40.0f,1,30000}},
    {{28.0f,0,1000},{25.0f,175,10000},{40.0f,350,30000}},
    {{40.0f,0,2000},{35.0f,120,20000},{40.0f,300,30000}},
    {{25.0f,80,3000},{25.0f,130,11000},{30.0f,450,30000}},//NIGHT
    {{35.0f,110,3000},{35.0f,180,6000},{35.0f,450,30000}},
    {{45.0f,85,3000},{40.0f,100,12000},{50.0f,450,30000}},
    {{45.0f,125,3000},{35.0f,175,12000},{50.0f,450,30000}},
    {{37.0f,50,400},{40.0f,170,13000},{50.0f,450,30000}},
    {{60.0f,1,2000},{55.0f,1,10000},{50.0f,1,30000}},
    {{15.0f,80,1000},{12.0f,110,3000},{9.0f,350,30000}},
    {{45.0f,130,4000},{45.0f,220,12000},{40.0f,450,30000}},
    {{50.0f,175,4000},{55.0f,470,10000},{50.0f,450,40000}},//SPACE
    {{45.0f,130,3000},{20.0f,220,10000},{50.0f,450,40000}},
    {{45.0f,130,2000},{40.0f,175,12000},{50.0f,450,40000}},
    {{60.0f,130,1000},{55.0f,250,5000},{50.0f,450,40000}},
    {{60.0f,110,1000},{45.0f,150,15000},{50.0f,450,40000}},
    {{45.0f,0,10000},{45.0f,0,20000},{120.0f,1,40000}},
    {{60.0f,130,2000},{45.0f,275,10000},{50.0f,450,40000}},
    {{45.0f,130,2000},{55.0f,275,8000},{50.0f,600,40000}},
    {{30.0f,50,300},{40.0f,100,3000},{50.0f,500,30000}},//BONUS
    {{30.0f,50,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,50,300},{40.0f,100,3000},{50.0f,500,30000}},
    {{30.0f,50,300},{40.0f,100,3000},{50.0f,500,30000}},
};
LevelGoals *LevelSelect::getLevelGoals()
{
    int medalLevel = 0;
    if(SaveLoad::m_SaveData.levelflags[s_LevelID] & SaveLoad::THREE_COCONUT)
        medalLevel = 2;
    else if (SaveLoad::m_SaveData.levelflags[s_LevelID] & SaveLoad::TWO_COCONUT)
        medalLevel = 2;
    else if (SaveLoad::m_SaveData.levelflags[s_LevelID] & SaveLoad::ONE_COCONUT)
        medalLevel = 1;
    
    return &s_Goals[s_LevelID][medalLevel];
}


LevelSelect::~LevelSelect()
{
    
}

CCScene* LevelSelect::scene(REGIONID regionID)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    LevelSelect* layer = new LevelSelect();
    m_LastRegionID = regionID;
    layer->Init(regionID);
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
CCScene* LevelSelect::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    LevelSelect* layer = new LevelSelect();
    layer->Init((REGIONID)m_LastRegionID);
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
