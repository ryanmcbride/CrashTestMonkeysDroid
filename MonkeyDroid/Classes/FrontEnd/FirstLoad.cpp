//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "FirstLoad.h"
#include "SimpleAudioEngine.h"
#include "ScreenHelper.h"
#include "../Level/Level.h"
#include "MainMenu.h"
#include "FirstPlay.h"
#include "SaveLoad.h"
#include "../AudioManager.h"


using namespace cocos2d;
using namespace CocosDenshion;

FirstLoad::FirstLoad()
{
    setTouchEnabled( true );
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();

    CCSprite *sprite = CCSprite::create("FirstLoad.png");
    sprite->setScaleX(0.5f*scaleY);
    sprite->setScaleY(0.5f*scaleX);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,0.0f));
    sprite->setRotation(-90.0f);
    addChild(sprite);
    scheduleUpdate();
}


void FirstLoad::update(float dt)
{
    AudioManager::PreloadAudio();
    
    CCTextureCache::sharedTextureCache()->addImage("ctm_VFX.png");

    CCTextureCache::sharedTextureCache()->addImage("Pause_Menu.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Backward_Btn_ver1_down.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Backward_Btn_ver1.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Forward_Btn_ver1_down.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Forward_Btn_ver1.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Jump_Btn_ver1_down.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Jump_Btn_ver1.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Pause_Btn_ver1_down.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_UI_Pause_Btn_ver1.png");

    CCTextureCache::sharedTextureCache()->addImage("ctm_Objects.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Grass_withplants_00.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_island_BG_01.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_island_FG_01.png");
    CCTextureCache::sharedTextureCache()->addImage("CTMDefault-hd.png");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick1.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick2.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick3.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick4.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick5.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick6.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick7.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick8.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_Trick9.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Default_RideCycle.pvr.ccz");
    
    CCTextureCache::sharedTextureCache()->addImage("ctm_Rider-hd.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_StartScreen.pvr.ccz");
    ScreenHelper::AddOBBSpriteToCache("TikiObjs.png","TikiObjs.plist");
    CCTextureCache::sharedTextureCache()->addImage("LevelSelectIcon.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("LevelSelect.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_Icons.pvr.ccz");
    CCTextureCache::sharedTextureCache()->addImage("ctm_WinScreen.pvr.ccz");
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Rider-hd.pv.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_VFX.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Objects.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("CTMDefault-hd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_WinScreen.pv.plist");
    
    if(SaveLoad::m_SaveData.bHasBeenPlayed)
    {
        // create a scene. it's an autorelease object
        CCScene *pScene = MainMenu::scene();
        // run
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    else
    {
        SaveLoad::m_SaveData.bHasBeenPlayed = 1;
        SaveLoad::Save();
        // create a scene. it's an autorelease object
        CCScene *pScene = FirstPlay::scene();
        // run
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    
}
FirstLoad::~FirstLoad()
{
    
}

CCScene* FirstLoad::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new FirstLoad();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
