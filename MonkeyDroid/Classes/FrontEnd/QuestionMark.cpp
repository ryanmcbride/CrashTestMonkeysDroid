//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "QuestionMark.h"
#include "SimpleAudioEngine.h"
#include "Options.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

QuestionMark::QuestionMark()
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
    
    CCLabelTTF *label = CCLabelTTF::create("?", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("?", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(QuestionMark::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    CCSize dim;
    int randInt = RandomInt(0,100);
    if(randInt>95)
    {
        dim.width = 420*scale;
        dim.height = 250*scale;
        const char *colorText = "\"Surely you can't be serious!\" he says, as he slowly ambles back to his crimson hued overstuffed chair.  You find yourself contemplating the simian who rebuffed your overture so out of hand.  You can't help but admire this modern Grigori Rasputin for his steely determination.  With perhaps undue influence of aqua vitae and plantains coloring your reason, you counter with tremendous vigor.  With all the potency of Hannibal and his terrene leviathan you fill your hands with your own ordure and volley it squarely into his agape maw.";
        
        CCLabelTTF *text = CCLabelTTF::create(colorText,"impact.ttf",16*scale,dim,kCCTextAlignmentCenter);
        text->setColor(ccc3(230,230,230));
        text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -70.0f));
        addChild(text);
    }
    else if(randInt>5)
    {
        int randomImage = RandomInt(1,14);
        
        CCTextureCache::sharedTextureCache()->addPVRImage("QuestionMark.pvr.ccz");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("QuestionMark.plist");
        
        char temp[64];
        sprintf(temp,"ConceptArt_%02d.png",randomImage);
        CCSprite *image = CCSprite::createWithSpriteFrameName(temp);
        image->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -35.0f));
        image->setScale(0.5f*scale);
        addChild(image);
    }
    else
    {
        dim.width = 420*scale;
        dim.height = 250*scale;
        const char *colorText = "?";
        
        CCLabelTTF *text = CCLabelTTF::create(colorText,"impact.ttf",80*scale,dim,kCCTextAlignmentCenter);
        text->setColor(ccc3(230,230,230));
        text->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, -70.0f));
        addChild(text);
    }
}
void QuestionMark::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Options::scene());
}
void QuestionMark::starButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void QuestionMark::bugButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void QuestionMark::reviewButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void QuestionMark::facebookButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}


QuestionMark::~QuestionMark()
{
    
}

CCScene* QuestionMark::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new QuestionMark();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
