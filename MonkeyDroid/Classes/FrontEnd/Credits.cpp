//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Credits.h"
#include "SimpleAudioEngine.h"
#include "Options.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

Credits::Credits()
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
    
    CCLabelTTF *label = CCLabelTTF::create("CREDITS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("CREDITS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    
    
    
    sprite = CCSprite::create("box2d_logo2.png");
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-10.0f));
    sprite->setScale(0.75f*scale);
    addChild(sprite);
    
    sprite = CCSprite::create("Icon@2x.png");
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_RIGHT,-90.0f,-20.0f));
    sprite->setScale(0.75f*scale);
    addChild(sprite);
    
    
    ////////////////////////////////////////////////////
    CCSize dim;
    dim.width = 300;
    dim.height = 50;
    
    dim.width = 150*scale;
    CCLabelTTF *art = CCLabelTTF::create("Art","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    art->setColor(ccc3(237,188,0));
    art->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,50.0f));
    addChild(art);
    
    CCLabelTTF *ken = CCLabelTTF::create("Ken Keys","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    ken->setColor(ccc3(230,230,230));
    ken->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,30.0f));
    addChild(ken);
    
    CCLabelTTF *garrett = CCLabelTTF::create("Garrett Wren","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    garrett->setColor(ccc3(230,230,230));
    garrett->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,10.0f));
    addChild(garrett);
    
    
    
    
    CCLabelTTF *programming = CCLabelTTF::create("Programming","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    programming->setColor(ccc3(237,188,0));
    programming->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,-25.0f));
    addChild(programming);
    
    CCLabelTTF *ryan = CCLabelTTF::create("Ryan McBride","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    ryan->setColor(ccc3(230,230,230));
    ryan->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,-45.0f));
    addChild(ryan);
    
    CCLabelTTF *audio = CCLabelTTF::create("Audio","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    audio->setColor(ccc3(237,188,0));
    audio->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,-80.0f));
    addChild(audio);
    
    CCLabelTTF *pete = CCLabelTTF::create("Peter Lehman","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentLeft);
    pete->setColor(ccc3(230,230,230));
    pete->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,90.0f,-100.0f));
    addChild(pete);
    
    
    dim.width = 300*scale;
    CCLabelTTF *ludicrous = CCLabelTTF::create("© 2013 Ludicrous Games LLC","Jacoby ICG Black.ttf",24*scale,dim,kCCTextAlignmentCenter);
    ludicrous->setColor(ccc3(237,188,0));
    ludicrous->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,0.0f,40.0f));
    addChild(ludicrous);
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(Credits::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
}
void Credits::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Options::scene());
}
void Credits::starButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void Credits::bugButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void Credits::reviewButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void Credits::facebookButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}


Credits::~Credits()
{
    
}

CCScene* Credits::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new Credits();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
