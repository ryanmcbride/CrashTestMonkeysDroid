//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Feedback.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "cocos2d.h"
#include "ScreenHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

FeedbackMenu::FeedbackMenu()
{
    setTouchEnabled( true );
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();

    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_FeedBack.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_FeedBack.plist");
 
    
    CCSprite *sprite = CCSprite::create("MainBackFiller.png");
    sprite->setScaleX(scaleX*1.2f);
    sprite->setScaleY(scaleY*1.2f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-32.0f));
    addChild(sprite);
    
    sprite = CCSprite::create("ctm_UI_topOverlayA_ver1.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite);

    CCLabelTTF *label = CCLabelTTF::create("FEEDBACK", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("FEEDBACK", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
 
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(FeedbackMenu::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenuItem *StarButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_feedback_StarRating.png"), CCSprite::createWithSpriteFrameName("ctm_feedback_StarRating_dn.png"), this, menu_selector(FeedbackMenu::starButtonTapped));
    StarButton->setScale(scale*0.5f);
    StarButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,120.0f,-80.0f));

    CCMenuItem *BugButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_feedback_Bugs.png"), CCSprite::createWithSpriteFrameName("ctm_feedback_Bugs_dn.png"), this, menu_selector(FeedbackMenu::bugButtonTapped));
    BugButton->setScale(scale*0.5f);
    BugButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,120.0f,20.0f));

    CCMenuItem *ReviewButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_feedback_Review.png"), CCSprite::createWithSpriteFrameName("ctm_feedback_Review_dn.png"), this, menu_selector(FeedbackMenu::reviewButtonTapped));
    ReviewButton->setScale(scale*0.5f);
    ReviewButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_RIGHT,-120.0f,-80.0f));

    CCMenuItem *FacebookButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_feedback_facebook.png"), CCSprite::createWithSpriteFrameName("ctm_feedback_facebook_dn.png"), this, menu_selector(FeedbackMenu::facebookButtonTapped));
    FacebookButton->setScale(scale*0.5f);
    FacebookButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_RIGHT,-120.0f,20.0f));

    CCMenu* menu = CCMenu::create(BackButton, StarButton, BugButton, ReviewButton, FacebookButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
}
void FeedbackMenu::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
void FeedbackMenu::starButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void FeedbackMenu::bugButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void FeedbackMenu::reviewButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void FeedbackMenu::facebookButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "com/LudicrousGames/MonkeyDroid/MonkeyDroid", "openURL", "(Ljava/lang/String;)V"))
        {
           jstring stringArg1;
           stringArg1 = t.env->NewStringUTF("http://www.facebook.com/pages/Crash-Test-Monkeys/223880524416997");

           t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);

           t.env->DeleteLocalRef(stringArg1);
           t.env->DeleteLocalRef(t.classID);
        }
#endif
}


FeedbackMenu::~FeedbackMenu()
{
    
}

CCScene* FeedbackMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new FeedbackMenu();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
