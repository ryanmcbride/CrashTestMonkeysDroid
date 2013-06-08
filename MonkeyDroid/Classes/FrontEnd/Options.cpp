//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Options.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "MoreGames.h"
#include "QuestionMark.h"
#include "Credits.h"
#include "ScreenHelper.h"
#include "SaveLoad.h"
#include "../AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

Options::Options()
{
    setTouchEnabled( true );

    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
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
    
    CCLabelTTF *label = CCLabelTTF::create("OPTIONS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("OPTIONS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(Options::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenuItem *QuestionMarkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_20.png"), CCSprite::createWithSpriteFrameName("ctm_Button_20_Down.png"), this, menu_selector(Options::questionButtonTapped));
    QuestionMarkButton->setScale(scale);
    QuestionMarkButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,0.0f,65.0f));
    
    CCMenuItem *MoreGamesButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("MoreGames.png"), CCSprite::createWithSpriteFrameName("MoreGames_dn.png"), this, menu_selector(Options::moreGamesButtonTapped));
    MoreGamesButton->setScale(scale);
    MoreGamesButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,55.0f,65.0f));
    
    CCMenuItem *CreditsButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("Credits.png"), CCSprite::createWithSpriteFrameName("Credits_dn.png"), this, menu_selector(Options::creditsButtonTapped));
    CreditsButton->setScale(scale);
    CreditsButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_RIGHT,-55.0f,65.0f));
    
    CCLabelTTF *optionsLabel = NULL;
    if(SaveLoad::m_SaveData.sfxVolume <= 0.0f)
        optionsLabel = CCLabelTTF::create("SFX:  OFF", "impact.ttf", 40*scale);
    else
        optionsLabel = CCLabelTTF::create("SFX:  ON", "impact.ttf", 40*scale);
    
    CCMenuItemLabel *SoundFX = CCMenuItemLabel::create(optionsLabel, this, menu_selector(Options::sfxButtonTapped));
    SoundFX->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0, 20));
    
    
    
    if(SaveLoad::m_SaveData.musicVolume <= 0.0f)
        optionsLabel = CCLabelTTF::create("Music:  OFF", "impact.ttf", 40*scale);
    else
        optionsLabel = CCLabelTTF::create("Music:  ON", "impact.ttf", 40*scale);
    
    CCMenuItemLabel *Music = CCMenuItemLabel::create(optionsLabel, this, menu_selector(Options::musicButtonTapped));
    Music->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0, -20));
    
    
    
    CCMenu* menu = CCMenu::create(BackButton, QuestionMarkButton, MoreGamesButton, CreditsButton, SoundFX, Music, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    scheduleUpdate();
}
void Options::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

void Options::moreGamesButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(MoreGames::scene());
}
void Options::creditsButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Credits::scene());
}
void Options::questionButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(QuestionMark::scene());
}
void Options::sfxButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCMenuItemLabel *SoundFX = (CCMenuItemLabel*)object;
    CCLabelTTF *label = (CCLabelTTF *)SoundFX->getLabel();
    
    if(SaveLoad::m_SaveData.sfxVolume <= 0.0f)
    {
        SaveLoad::m_SaveData.sfxVolume = 1.0f;
        label->setString("SFX:  ON");
        AudioManager::g_MasterSFXAudio = 1.0f;
    }
    else
    {
        SaveLoad::m_SaveData.sfxVolume = 0.0f;
        label->setString("SFX:  OFF");
        AudioManager::g_MasterSFXAudio = 0.0f;
    }
    AudioManager::AudioOn();
    SaveLoad::Save();
}
void Options::musicButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCMenuItemLabel *SoundFX = (CCMenuItemLabel*)object;
    CCLabelTTF *label = (CCLabelTTF *)SoundFX->getLabel();
    
    if(SaveLoad::m_SaveData.musicVolume <= 0.0f)
    {
        SaveLoad::m_SaveData.musicVolume = 1.0f;
        label->setString("Music:  ON");
        AudioManager::g_MasterMusicAudio = 1.0f;
    }
    else
    {
        SaveLoad::m_SaveData.musicVolume = 0.0f;
        label->setString("Music:  OFF");
        AudioManager::g_MasterMusicAudio = 0.0f;
    }
    AudioManager::AudioOn();
    SaveLoad::Save();
}


Options::~Options()
{
    
}
void Options::update(float dt)
{
    AudioManager::UpdateAudio(dt);
}

CCScene* Options::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new Options();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
