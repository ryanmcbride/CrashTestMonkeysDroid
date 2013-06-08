//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "MoreGames.h"
#include "SimpleAudioEngine.h"
#include "Options.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

MoreGames::MoreGames()
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
    

    CCLabelTTF *label = CCLabelTTF::create("MORE GAMES", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    

    label = CCLabelTTF::create("MORE GAMES", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(MoreGames::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    sprite = CCSprite::create("TeslaIcon.png");
    sprite->setScale(0.6f*scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,100.0f,-50.0f));
    addChild(sprite);
    
    CCSize dim;
    dim.width = 400*scale;
    dim.height = 25*scale;
    const char *colorText = "A Game from our friends at iCOOLgeeks";
    
    CCLabelTTF *text = CCLabelTTF::create(colorText, "impact.ttf", 20*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(0,0,0));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,53.0f));
    addChild(text,4);
    
    text = CCLabelTTF::create(colorText, "impact.ttf", 20*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(230,230,230));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,55.0f));
    addChild(text,4);
    
    dim.width = 250*scaleX;
    dim.height = 250*scaleY;
    
    const char *titleText  = "Tesla's Electric Mist";
    text = CCLabelTTF::create(titleText, "impact.ttf", 24*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(0,0,0));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,77.0f,-92.0f));
    addChild(text,4);
    
    text = CCLabelTTF::create(titleText, "impact.ttf", 24*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(60,230,60));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,75.0f,-90.0f));
    addChild(text,4);
    
    const char *detailText = "A Point-and-Click adventure revolving around the mysterious inventor, Nikola Tesla, a time travel machine he invented, and an experiment gone terribly wrong.";
    
    text = CCLabelTTF::create(detailText, "impact.ttf", 17*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(0,0,0));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,77.0f,-127.0f));
    addChild(text,4);
    
    text = CCLabelTTF::create(detailText, "impact.ttf", 17*scale,dim,kCCTextAlignmentCenter);
    text->setColor(ccc3(150,230,150));
    text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,75.0f,-125.0f));
    addChild(text,4);
}
void MoreGames::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Options::scene());
}
void MoreGames::starButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void MoreGames::bugButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void MoreGames::reviewButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void MoreGames::facebookButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}


MoreGames::~MoreGames()
{
    
}

CCScene* MoreGames::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MoreGames();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
