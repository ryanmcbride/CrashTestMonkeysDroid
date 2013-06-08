//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Loading.h"
#include "../AudioManager.h"
#include "MainMenu.h"
#include "ScreenHelper.h"
#include "../Level/Level.h"
#include "LevelSelect.h"
#include "XMLLevelLoader.h"
#include "Store/STore.h"
#include "SaveLoad.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern bool g_2XPeanuts;
extern bool g_PermanentFire;
extern bool g_SlowClock;
extern int g_TutorialState;
bool g_isTrickLevel = false;


Loading::Loading()
{
    glClearColor(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f);
    setTouchEnabled( true );

    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("LoadingScreen.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LoadingScreen.plist");
    
    CCPoint scalePoint;
    scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
    scalePoint.y += -5*scale;
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Loading_Screen_ver2.png");
    sprite->setScale(scale);
    sprite->setPosition(scalePoint);
    addChild(sprite);
    
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_Loading_ProgressScroll_Graphic.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY*1.2f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,-140.0f,-50.0f));
    loadingBar = sprite;
    addChild(sprite,2);
    
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_Loading_TopPanel.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-55.0f));
    addChild(sprite,2);
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_Loading_TopOverlay.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite,2);
    
    sprite = CCSprite::createWithSpriteFrameName("BackgroundPlate.png");
    sprite->setScale(scale);
    scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
    scalePoint.x += -135.0f*scale;
    scalePoint.y += -97.0f*scale;
    sprite->setPosition(scalePoint);
    addChild(sprite,2);
    
    sprite = CCSprite::createWithSpriteFrameName("BronzeText.png");
    sprite->setScale(scale);
    scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
    scalePoint.x += -135.0f*scale;
    scalePoint.y += -97.0f*scale;
    sprite->setPosition(scalePoint);
    addChild(sprite,2);
    
    CCLabelTTF *label = CCLabelTTF::create(LevelSelect::getLevelName(), "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-44.0f));
    
    label = CCLabelTTF::create(LevelSelect::getLevelName(), "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-42.0f));
    
    int currentLevel = LevelSelect::getCurrentLevel();
    if(currentLevel >= BONUS_LEVELSTART)
        g_isTrickLevel = true;
    else
        g_isTrickLevel = false;
    
    
    int medalLevel = SaveLoad::m_SaveData.medalLockLevel;
    int showMedal = 0;
    if(medalLevel==0)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::ONE_COCONUT)
            showMedal = 1;
    }
    if(medalLevel==1)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::TWO_COCONUT)
            showMedal = 2;
    }
    if(medalLevel==2)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::THREE_COCONUT)
            showMedal = 3;
    }
    
    if(!showMedal)
    {
        CCSize dimensions;
        dimensions.width = 100*scale;
        dimensions.height  = 25*scale;
        label = CCLabelTTF::create("Time:", "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(237,188,0));

        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+90.0f)*scale;
        scalePoint.y += 50.0f*scale;
        label->setPosition(scalePoint);
        
        char tempLabelStr[32];
        sprintf(tempLabelStr,"%.2f",LevelSelect::getLevelGoals()->time);
        label = CCLabelTTF::create(tempLabelStr, "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(255,255,255));
        
        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+150.0f)*scale;
        scalePoint.y += 50.0f*scale;
        label->setPosition(scalePoint);
                
        label = CCLabelTTF::create("Peanuts:", "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        
        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+90.0f)*scale;
        scalePoint.y += 20.0f*scale;
        label->setPosition(scalePoint);
        
        sprintf(tempLabelStr,"%d",LevelSelect::getLevelGoals()->peanuts);
        label = CCLabelTTF::create(tempLabelStr, "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(255,255,255));
        
        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+170.0f)*scale;
        scalePoint.y += 20.0f*scale;
        label->setPosition(scalePoint);
        
        label = CCLabelTTF::create("Points:", "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        
        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+90.0f)*scale;
        scalePoint.y += -10.0f*scale;
        label->setPosition(scalePoint);
        
        sprintf(tempLabelStr,"%d",LevelSelect::getLevelGoals()->points);
        label = CCLabelTTF::create(tempLabelStr, "impact.ttf", 21*scale,dimensions,kCCTextAlignmentLeft);
        addChild(label, 2);
        label->setColor(ccc3(255,255,255));

        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += (-240.0f+160.0f)*scale;
        scalePoint.y += -10.0f*scale;
        label->setPosition(scalePoint);        
    }
    else
    {
        CCTextureCache::sharedTextureCache()->addPVRImage("LoadingScreen2.pvr.ccz");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LoadingScreen2.plist");

        if(showMedal == 1)
            sprite = CCSprite::createWithSpriteFrameName("ctm_BronzeMedalBig.png");
        if(showMedal == 2)
            sprite = CCSprite::createWithSpriteFrameName("ctm_SilverMedalBig.png");
        if(showMedal == 3)
            sprite = CCSprite::createWithSpriteFrameName("ctm_Loading_LargeGold.png");
        
        sprite->setScale(scale);
        scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
        scalePoint.x += -135.0f*scale;
        scalePoint.y += 5.0f*scale;
        sprite->setPosition(scalePoint);
        addChild(sprite,2);
    }
    
    CCMenuItem *StoreButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_17.png"), CCSprite::createWithSpriteFrameName("ctm_Button_17_Down.png"), this, menu_selector(Loading::storeButtonTapped));
    StoreButton->setScale(scale);
    scalePoint = ccp(0,0);
    scalePoint.x += 85.0f*scale;
    scalePoint.y += -100.0f*scale;
    StoreButton->setPosition(scalePoint);
    
    CCMenu* menu = CCMenu::create(StoreButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(menu,4);
    
    
    
    CCMenuItemSprite *items[3];
    //if(SaveLoad::m_SaveData.numDoubleNuts)
    {
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 35.0f;
        CCSprite *barImage = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        CCSprite *barImageSel = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        barImage->setOpacity(0);
        barImageSel->setOpacity(0);
        CCMenuItemSprite *menuImage = CCMenuItemSprite::create(barImage,barImageSel,this,menu_selector(Loading::nutsButtonTapped));
        CCLabelTTF *blabel = CCLabelTTF::create(" Use 2X Peanuts","Jacoby ICG Black.ttf",18,dim,kCCTextAlignmentLeft);
        blabel->setColor(ccc3(237,188,0));
        blabel->setPosition(ccp(157.0f,18.0f));
        menuImage->addChild(blabel,0,1234);
        items[1] = menuImage;
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_icon_Store_17_2X-peanuts.png");
        sprite->setPosition(ccp(30,23));
        sprite->setScale(0.925f);
        menuImage->addChild(sprite,0,4321);
        menuImage->setScale(scale);
        
        if(!SaveLoad::m_SaveData.numDoubleNuts)
        {
            //[menuImage setIsEnabled:NO];
            blabel->setColor(ccc3(237/2,188/2,0));
            sprite->setColor(ccc3(128,128,128));
        }
        
    }
    //if(SaveLoad::m_SaveData.numLevelFire)
    {
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 35.0f;
        CCSprite *barImage = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        CCSprite *barImageSel = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        barImage->setOpacity(0);
        barImageSel->setOpacity(0);
        CCMenuItemSprite *menuImage = CCMenuItemSprite::create(barImage,barImageSel,this,menu_selector(Loading::fireButtonTapped));
        CCLabelTTF *blabel = CCLabelTTF::create(" Use Permanent Fire","Jacoby ICG Black.ttf",18,dim,kCCTextAlignmentLeft);
        blabel->setColor(ccc3(237,188,0));
        blabel->setPosition(ccp(157.0f,18.0f));
        menuImage->addChild(blabel,0,1234);
        items[2] = menuImage;
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_icon_Store_18_Fire.png");
        sprite->setPosition(ccp(30,23));
        sprite->setScale(0.925f);
        menuImage->addChild(sprite,0,4321);
        menuImage->setScale(scale);
        
        if(!SaveLoad::m_SaveData.numLevelFire)
        {
            //[menuImage setIsEnabled:NO];
            blabel->setColor(ccc3(237/2,188/2,0));
            sprite->setColor(ccc3(128,128,128));
        }
    }
    //if(SaveLoad::m_SaveData.numTimeSlow)
    {
        
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 35.0f;
        CCSprite *barImage = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        CCSprite *barImageSel = CCSprite::create("ctm_UI_smallGreyStrip_ver1.png");
        barImage->setOpacity(0);
        barImageSel->setOpacity(0);
        CCMenuItemSprite *menuImage = CCMenuItemSprite::create(barImage,barImageSel,this,menu_selector(Loading::timeButtonTapped));
        CCLabelTTF *blabel = CCLabelTTF::create(" Use Slow Clock","Jacoby ICG Black.ttf",18,dim,kCCTextAlignmentLeft);
        blabel->setColor(ccc3(237,188,0));
        blabel->setPosition(ccp(157.0f,18.0f));
        menuImage->addChild(blabel,0,1234);
        items[0] = menuImage;
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_icon_Store_16_Slow-Clock.png");
        sprite->setPosition(ccp(30,23));
        sprite->setScale(0.925f);
        menuImage->addChild(sprite,0,4321);
        menuImage->setScale(scale);
        
        if(!SaveLoad::m_SaveData.numTimeSlow)
        {
            //[menuImage setIsEnabled:NO];
            blabel->setColor(ccc3(237/2,188/2,0));
            sprite->setColor(ccc3(128,128,128));
        }

        
    }
    CCMenu *powerUpMenu = CCMenu::create(items[0], items[1], items[2], NULL);
    
    powerUpMenu->alignItemsVerticallyWithPadding(-10.0);
    scalePoint = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER);
    scalePoint.x += 100.0f*scale;
    scalePoint.y += 10.0f*scale;
    powerUpMenu->setPosition(scalePoint);
    addChild(powerUpMenu);
    
    
    m_TimeOut = 3.0f;
    scheduleUpdate();
}
void Loading::backButtonTapped(CCObject*object)
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
void Loading::storeButtonTapped(CCObject*object)
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    m_TimeOut = 3.0f;
    CCDirector::sharedDirector()->pushScene(Store::scene());
}
void Loading::nutsButtonTapped(CCObject*object)
{
    
    //if(s_isStorePopupActive)return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    
    if(g_2XPeanuts || SaveLoad::m_SaveData.numDoubleNuts)
    {
        if(g_2XPeanuts)
        {
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            item->removeChildByTag(10,true);
            SaveLoad::m_SaveData.numDoubleNuts++;
            SaveLoad::Save();
            g_2XPeanuts = false;
        }
        else
        {
            SaveLoad::m_SaveData.numDoubleNuts--;
            SaveLoad::Save();
            g_2XPeanuts = true;
            
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            
            CCSprite *checkMark = CCSprite::createWithSpriteFrameName("ctm_Loading_SelectedGreenTick.png");
            checkMark->setPosition(ccp(227.0f,22.0f));
            item->addChild(checkMark,0,10);
        }
    }
    else
    {
//        [self addChild:[StorePopup node]];
    }
    
}
void Loading::fireButtonTapped(CCObject*object)
{
    //if(s_isStorePopupActive)return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    if(g_PermanentFire || SaveLoad::m_SaveData.numLevelFire)
    {
        if(g_PermanentFire)
        {
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            item->removeChildByTag(10,true);
            SaveLoad::m_SaveData.numLevelFire++;
            SaveLoad::Save();
            g_PermanentFire = false;
        }
        else
        {
            SaveLoad::m_SaveData.numLevelFire--;
            SaveLoad::Save();
            g_PermanentFire = true;
            
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            CCSprite *checkMark = CCSprite::createWithSpriteFrameName("ctm_Loading_SelectedGreenTick.png");
            checkMark->setPosition(ccp(227.0f,22.0f));
            item->addChild(checkMark,0,10);
        }
    }
    else
    {
        //[self addChild:[StorePopup node]];
    }

}
void Loading::timeButtonTapped(CCObject*object)
{
    //if(s_isStorePopupActive)return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    if(g_SlowClock || SaveLoad::m_SaveData.numTimeSlow)
    {
        if(g_SlowClock)
        {
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            item->removeChildByTag(10,true);
            SaveLoad::m_SaveData.numTimeSlow++;
            SaveLoad::Save();
            g_SlowClock = false;
        }
        else
        {
            SaveLoad::m_SaveData.numTimeSlow--;
            SaveLoad::Save();
            g_SlowClock = true;
            
            CCMenuItemImage *item = ((CCMenuItemImage*)object);
            CCSprite *checkMark = CCSprite::createWithSpriteFrameName("ctm_Loading_SelectedGreenTick.png");
            checkMark->setPosition(ccp(227.0f,22.0f));
            item->addChild(checkMark,0,10);
        }
    }
    else
    {
        //[self addChild:[StorePopup node]];
    }

}

void Loading::update(float dt)
{
    m_TimeOut -= dt;
    if(m_TimeOut < 0.0f)
    {
        CCDirector::sharedDirector()->replaceScene(Level::scene());
        m_TimeOut = 100.0f;
    }
    else
    {
        float width = 400.0f;
        float positionX = (3.0f-m_TimeOut)/3.0f*width-140.0f;
        loadingBar->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,positionX,-50.0f));
    }
}

Loading::~Loading()
{
    
}


class TutorialLoading : public CCLayer
{
public:
    TutorialLoading(int number)
    {
        float scale = ScreenHelper::getTextureScale();
        float scaleX = ScreenHelper::getTextureScaleX();
        float scaleY = ScreenHelper::getTextureScaleY();
        
        m_TimeOut = 2.99f;
        scheduleUpdate();
        
        CCTextureCache::sharedTextureCache()->addPVRImage("LoadingScreen.pvr.ccz");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LoadingScreen.plist");
        
        CCNode *grid = CCNode::create();
        
        CCSprite *gridSprite = CCSprite::createWithSpriteFrameName("LoadTutGridBG.png");
        gridSprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
        gridSprite->setScaleX(scaleX);
        gridSprite->setScaleY(scaleY);
        grid->addChild(gridSprite);
        addChild(grid,1);
        switch(number)
        {
            case 1:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Moving Forward","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                label->setOpacity(160);
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -35.0f, 40.0f));
                grid->addChild(label);
                
                label = CCLabelTTF::create("and Backward","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                label->setOpacity(160);
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -35.0f, -30.0f));
                grid->addChild(label);
                CCSprite *forwardSprite = CCSprite::create("ctm_UI_Forward_Btn_ver1.png");
                forwardSprite->setOpacity(200);
                forwardSprite->setScale(scale);
                forwardSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 175.0f, 35.0f));
                grid->addChild(forwardSprite);
                
                CCSprite *backwardSprite = CCSprite::create("ctm_UI_Backward_Btn_ver1.png");
                backwardSprite->setOpacity(200);
                backwardSprite->setScale(scale);
                backwardSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 165.0f, -35.0f));
                grid->addChild(backwardSprite);
                
                
            }
                break;
            case 2:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Jumping","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                
                label->setOpacity(160);
                
                //CCLabelTTF *label = CCLabelTTF::create("Jumping" fontName:@"impact.ttf" fontSize: 60];
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 15.0f));
                //label->setOpacity(200;
                grid->addChild(label);
                
                CCSprite *jumpSprite = CCSprite::create("ctm_UI_Jump_Btn_ver1.png");
                jumpSprite->setOpacity(200);
                jumpSprite->setScale(scale);
                jumpSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 130.0f, 10.0f));
                grid->addChild(jumpSprite);
            }
                break;
            case 3:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Working for\nPeanuts","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                label->setOpacity(160);
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 40.0f));
                grid->addChild(label);
                
                CCSprite *peanutSprite = CCSprite::createWithSpriteFrameName("TutPeanuts.png");
                peanutSprite->setOpacity(200);
                peanutSprite->setScale(scale);
                peanutSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -50.0f));
                grid->addChild(peanutSprite);
                
                //label = CCLabelTTF::create("Thrilling Conclusion" fontName:@"impact.ttf" fontSize: 32];
                //label->setPosition(ccp(480.0f/2.0f,320.0f/2.0f-20.0f);
                //[self addChild:label];
            }
                break;
            case 4:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Trampolines","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                
                label->setOpacity(160);
                
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 40.0f));
                grid->addChild(label);
                
                label = CCLabelTTF::create("and Tricks","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                
                label->setOpacity(160);
                
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -10.0f));
                grid->addChild(label);
                
                CCSprite *jumpSprite = CCSprite::create("ctm_UI_Jump_Btn_ver1.png");
                jumpSprite->setOpacity(200);
                jumpSprite->setScale(scale);
                jumpSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 140.0f, -15.0f));
                grid->addChild(jumpSprite);
                //label = CCLabelTTF::create("Thrilling Conclusion" fontName:@"impact.ttf" fontSize: 32];
                //label->setPosition(ccp(480.0f/2.0f,320.0f/2.0f-20.0f);
                //[self addChild:label];
            }
                break;
            case 5:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Time","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                
                label->setOpacity(160);
                
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 15.0f));
                grid->addChild(label);
                
                //label = CCLabelTTF::create("Thrilling Conclusion" fontName:@"impact.ttf" fontSize: 32];
                //label->setPosition(ccp(480.0f/2.0f,320.0f/2.0f-20.0f);
                //[self addChild:label];
            }
                break;
            case 6:
            {
                CCSize dim;
                dim.width = 400.0f;
                dim.height = 150.0f;
                
                CCLabelTTF *label = CCLabelTTF::create("Earning Medals","impact.ttf",50*scale);
                label->setColor(ccc3(255,255,255));
                
                
                label->setOpacity(160);
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 40.0f));
                grid->addChild(label);
                
                CCTextureCache::sharedTextureCache()->addPVRImage("LoadingScreen2.pvr.ccz");
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LoadingScreen2.plist");
                
                CCSprite *bronze = CCSprite::createWithSpriteFrameName("ctm_BronzeMedalBig.png");
                bronze->setOpacity(200);
                bronze->setScale(scale);
                bronze->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 120.0f, -25.0f));
                grid->addChild(bronze);
                CCSprite *silver = CCSprite::createWithSpriteFrameName("ctm_SilverMedalBig.png");
                silver->setOpacity(200);
                silver->setScale(scale);
                silver->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -25.0f));
                grid->addChild(silver);
                CCSprite *gold = CCSprite::createWithSpriteFrameName("ctm_Loading_LargeGold.png");
                gold->setOpacity(200);
                gold->setScale(scale);
                gold->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -120.0f, -25.0f));
                grid->addChild(gold);
                
            }
                break;
        }
        
        g_TutorialState = number;
        
    }
    virtual ~TutorialLoading()
    {
        
    }
    virtual void update(float dt)
    {
        m_TimeOut -= dt;
        if(m_TimeOut < 0.0f)
        {
            CCDirector::sharedDirector()->replaceScene(Level::scene());
            m_TimeOut = 100.0f;
        }
    }
protected:
    float m_TimeOut;
};

CCScene* Loading::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCLayer* layer = NULL;
    
    if(LevelSelect::getCurrentLevel() <= 6)
        layer = new TutorialLoading(LevelSelect::getCurrentLevel()+1);
    else
        layer = new Loading();
    // add layer as a child to scene
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
