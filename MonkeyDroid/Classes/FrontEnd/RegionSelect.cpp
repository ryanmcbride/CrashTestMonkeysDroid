//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "RegionSelect.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "cocos-ext.h"
#include "ScreenHelper.h"
#include "CCScrollingMenu.h"
#include "LevelSelect.h"
#include "SaveLoad.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

float RegionSelect::m_fScrollViewOffset = -99999.0f;

RegionSelect::RegionSelect()
{
    setTouchEnabled( true );

    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
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
    
    CCLabelTTF *label = CCLabelTTF::create("LEVELS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("LEVELS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(RegionSelect::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    
    CCScrollingMenu *screenMenu = CCScrollingMenu::create();
    screenMenu->setPosition(0,0);
    
    CCMenuItem *PlayMovieButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("OneBananaButton.png"), CCSprite::createWithSpriteFrameName("OneBananaButton_dn.png"), this, menu_selector(RegionSelect::oneBananaButtonTapped));
    PlayMovieButton->setScale(scale);
    PlayMovieButton->setPosition(ccp(0.0f,0.0f));
    screenMenu->addChild(PlayMovieButton);
    
    CCMenuItem *TutorialButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("LevelSel_Tutorial.png"), CCSprite::createWithSpriteFrameName("LevelSel_Tutorial.png"), this, menu_selector(RegionSelect::TutorialButtonTapped));
    TutorialButton->setScale(scale*0.8f);
    TutorialButton->setPosition(ccp(0.0f,0.0f));
    addName(TutorialButton,"Tutorial");
    screenMenu->addChild(TutorialButton);
    
    CCMenuItem *TikiButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), this, menu_selector(RegionSelect::TikiButtonTapped));
    TikiButton->setScale(scale*0.8f);
    TikiButton->setPosition(ccp(0.0f,0.0f));
    addName(TikiButton,"Island");
    addMedals(TikiButton,LevelSelect::REGION_TIKI);
    if(addLock(TikiButton,LevelSelect::REGION_TIKI))
    {
        TikiButton->setEnabled(false);
    }
    screenMenu->addChild(TikiButton);
    
    CCMenuItem *CityButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0502.PNG"), CCSprite::createWithSpriteFrameName("IMG_0502.PNG"), this, menu_selector(RegionSelect::CityButtonTapped));
    CityButton->setScale(scale*0.8f);
    CityButton->setPosition(ccp(0.0f,0.0f));
    addName(CityButton,"City");
    addMedals(CityButton,LevelSelect::REGION_CITY);
    if(addLock(CityButton,LevelSelect::REGION_CITY))
    {
        CityButton->setEnabled(false);
    }
    screenMenu->addChild(CityButton);
    
    CCMenuItem *BonusButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), this, menu_selector(RegionSelect::BonusButtonTapped));
    BonusButton->setScale(scale*0.8f);
    BonusButton->setPosition(ccp(0.0f,0.0f));
    addName(BonusButton,"Bonus");
    screenMenu->addChild(BonusButton);
    
    CCMenuItem *NightButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0505.PNG"), CCSprite::createWithSpriteFrameName("IMG_0505.PNG"), this, menu_selector(RegionSelect::NightButtonTapped));
    NightButton->setScale(scale*0.8f);
    NightButton->setPosition(ccp(0.0f,0.0f));
    addName(NightButton,"Night");
    addMedals(NightButton,LevelSelect::REGION_NIGHT);
    if(addLock(NightButton,LevelSelect::REGION_NIGHT))
    {
        NightButton->setEnabled(false);
    }
    screenMenu->addChild(NightButton);
    
    CCMenuItem *SpaceButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0503.PNG"), CCSprite::createWithSpriteFrameName("IMG_0503.PNG"), this, menu_selector(RegionSelect::SpaceButtonTapped));
    SpaceButton->setScale(scale*0.8f);
    SpaceButton->setPosition(ccp(0.0f,0.0f));
    addName(SpaceButton,"Space");
    addMedals(SpaceButton,LevelSelect::REGION_SPACE);
    if(addLock(SpaceButton,LevelSelect::REGION_SPACE))
    {
        SpaceButton->setEnabled(false);
    }
    screenMenu->addChild(SpaceButton);

    CCMenuItem *TwentyTwelveButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ChimpOdyseeButton.png"), CCSprite::createWithSpriteFrameName("ChimpOdyseeButton_dn.png"), this, menu_selector(RegionSelect::TwentyTwelveButtonTapped));
    TwentyTwelveButton->setScale(scale);
    TwentyTwelveButton->setPosition(ccp(0.0f,0.0f));
    screenMenu->addChild(TwentyTwelveButton);
    
    CCMenuItem *ComingSoonButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), CCSprite::createWithSpriteFrameName("IMG_0501.PNG"), this, menu_selector(RegionSelect::ComingSoonButtonTapped));
    ComingSoonButton->setScale(scale*0.8f);
    ComingSoonButton->setPosition(ccp(0.0f,0.0f));
    addName(ComingSoonButton,"Coming Soon");
    screenMenu->addChild(ComingSoonButton);
    
    
    screenMenu->alignItemsHorizontallyWithPadding(75*scaleX);
    
    CCSize viewSize;
    viewSize.width = 2320.0f*scaleX;
    viewSize.height = 320*scaleY;
    CCScrollView *scrollView = CCScrollView::create(viewSize,screenMenu);
    //scrollView->setBounceable(false);
    scrollView->setContentSize(screenMenu->getContentSize());
    scrollView->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,470.0f-(viewSize.width/scaleX)/2.0f,0.0f));
    
    if(m_fScrollViewOffset < -10000.0f)
    {
        scrollView->setContentOffset(ccp(viewSize.width*0.75f,125.0f*scaleY));
    }
    else
        scrollView->setContentOffset(ccp(m_fScrollViewOffset,125.0f*scaleY));
    
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    
    addChild(scrollView);
    
    m_Scrollview = scrollView;
}

void RegionSelect::addName(cocos2d::CCNode * node,const char *name)
{
    CCLabelTTF *label = CCLabelTTF::create(name, "Jacoby ICG Black.ttf", 30);
    node->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(122.0f,174.0f));
    
    label = CCLabelTTF::create(name, "Jacoby ICG Black.ttf", 30);
    node->addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ccp(120.0f,176.0f));
}

bool RegionSelect::addLock(cocos2d::CCNode * node,int regionID)
{
    bool isLocked = false;
    
    if(regionID==LevelSelect::REGION_TIKI)
    {
        if(!(SaveLoad::m_SaveData.levelflags[ISLAND_LEVELSTART] & SaveLoad::UNLOCKED))
            isLocked = true;
    }
    if(regionID==LevelSelect::REGION_CITY)
    {
        if(SaveLoad::NumBronzeMedals()<8)
            isLocked = true;
    }
    if(regionID==LevelSelect::REGION_NIGHT)
    {
        if(SaveLoad::NumBronzeMedals()<16)
            isLocked = true;
    }
    if(regionID==LevelSelect::REGION_SPACE)
    {
        if(SaveLoad::NumBronzeMedals()<24)
            isLocked = true;
    }
    
    if(isLocked)
    {
        CCSprite *lock = CCSprite::create("ctm_Lock.png");
        node->addChild(lock);
        lock->setScale(1.2f);
        lock->setPosition(ccp(110.0f,75.0f));
    }
    
    return isLocked;
}
void RegionSelect::addMedals(cocos2d::CCNode * node,int regionID)
{
    int medalTotal = 8;
    int medalCount = 0;
    int leveloffset = ISLAND_LEVELSTART;
    if(regionID==LevelSelect::REGION_CITY)
        leveloffset = CITY_LEVELSTART;
    if(regionID==LevelSelect::REGION_NIGHT)
        leveloffset = NIGHT_LEVELSTART;
    if(regionID==LevelSelect::REGION_SPACE)
        leveloffset = SPACE_LEVELSTART;
    
    if(SaveLoad::NumSilverMedals()==32)
    {
        medalCount += 16;
        medalTotal += 16;
        for(int i = leveloffset; i < leveloffset+8; i++)
        {
            if(SaveLoad::m_SaveData.levelflags[i] & SaveLoad::THREE_COCONUT)
                medalCount++;
        }
    }
    else if(SaveLoad::NumBronzeMedals()==32)
    {
        medalCount += 8;
        medalTotal += 8;
        for(int i = leveloffset; i < leveloffset+8; i++)
        {
            if(SaveLoad::m_SaveData.levelflags[i] & SaveLoad::TWO_COCONUT)
                medalCount++;
        }
    }
    else
    {
        for(int i = leveloffset; i < leveloffset+8; i++)
        {
            if(SaveLoad::m_SaveData.levelflags[i] & SaveLoad::ONE_COCONUT)
                medalCount++;
        }
    }
    char name[32];
    
    sprintf(name,"%d/%d",medalCount,medalTotal);
    
    
    CCLabelTTF *label = CCLabelTTF::create(name, "Jacoby ICG Black.ttf", 20);
    node->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(222.0f,-9.0f));
    
    label = CCLabelTTF::create(name, "Jacoby ICG Black.ttf", 20);
    node->addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ccp(220.0f,-7.0f));
    
    CCSprite *medal = CCSprite::createWithSpriteFrameName("Levelselect_BronzeMedal.png");
    node->addChild(medal);
    medal->setScale(0.6f);
    medal->setPosition(ccp(160,-17.0f));
}
void RegionSelect::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
void RegionSelect::oneBananaButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/LudicrousGames/MonkeyDroid/MonkeyDroid", "playMovie", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1;
        stringArg1 = t.env->NewStringUTF("OneBanana_FinalCut.mp4");
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}
void RegionSelect::TutorialButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_TUTORIAL));
}
void RegionSelect::TikiButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_TIKI));
}
void RegionSelect::CityButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_CITY));
}
void RegionSelect::NightButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_NIGHT));
}
void RegionSelect::SpaceButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_SPACE));
}
void RegionSelect::TwentyTwelveButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/LudicrousGames/MonkeyDroid/MonkeyDroid", "playMovie", "(Ljava/lang/String;)V"))
    {
        jstring stringArg1;
        stringArg1 = t.env->NewStringUTF("chimpodd");
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}
void RegionSelect::BonusButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene(LevelSelect::REGION_BONUS));
}
void RegionSelect::ComingSoonButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}

RegionSelect::~RegionSelect()
{
    m_fScrollViewOffset = m_Scrollview->getContentOffset().x;
}

CCScene* RegionSelect::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new RegionSelect();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
