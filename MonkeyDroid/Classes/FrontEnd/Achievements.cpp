//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Achievements.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "cocos-ext.h"
#include "ScreenHelper.h"
#include "SaveLoad.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

static const char *s_ObjImg[15] =
{
    "ctm_icon_Objectives_46_Tripple-Lindy.png",//Triple Lindy
    "ctm_icon_Objectives_49_Nut-Envy.png",//Peanut Envy
    "ctm_icon_Store_13_Riders-Block.png",//Rider's Block
    "ctm_icon_Objectives_52_Thats-no-Moon.png",//That's No Moon
    "ctm_icon_Objectives_43_Mega-Flip.png",//It's Over 9000
    "ctm_icon_Objectives_50_In-soviet-Russia.png",//In Soviet Russia
    "ctm_icon_Objectives_40_Sparta.png",//This is Sparta!
    "ctm_icon_Objectives_48_Minus-WOrld.png",//The Minus World
    "ctm_icon_Objectives_42_Hot-Coffee.png",//Hot Coffee Mod
    "ctm_icon_Objectives_41_Jump-the-Shark.png",//Jump the Shark
    "ctm_icon_Objectives_47_Mission-accomplished.png",//Mission Accomplished
    "ctm_icon_Objectives_44_Beat-up-the-Beat.png",//Beat Up the Beat
    "ctm_icon_Objectives_53_Meh.png",//Meh
    "ctm_icon_Objectives_51_Flaming-Trick-of-Fire.png",//OMGWTFBBQ FTW
    "ctm_icon_Objectives_45_Road-Kill.png",//Road Kill
};
static const char *s_ObjName[15] =
{
    "Triple Lindy",
    "Peanut Envy",
    "Rider's Block",
    "That's No Moon",
    "It's Over 9000",
    "In Soviet Russia",
    "This is Sparta!",
    "The Minus World",
    "Hot Coffee Mod",
    "Jump the Shark",
    "Mission Accomplished",
    "Music of the Night",
    "Meh",
    "Avec Fromage",
    "Road Kill",
};
static const char *s_ObjDesc[15] =
{
    "Bounce on 3 different armadillos without landing",//"Triple Lindy"
    "Earn over 1000 peanuts in a single level",//"Peanut Envy"
    "Score over 100,000 points in a Bonus level",//"Rider's Block"},
    "Earn 5 Gold Medals in the Space Levels.",//"That's No Moon"},
    "Do an UltraFlip",//"It's Over 9000"},
    "Game plays you!  Buy everything in the store.",//"In Soviet Russia"},
    "Finish a Level with all 3 powerups",//"This is Sparta!"},
    "End a Level with negative points and time",//"The Minus World"},
    "Unlock Barbara Mandrill",//"Hot Coffee Mod"},
    "Don't Jump a Shark",//"Jump the Shark"},
    "Complete the Tutorial",//"Mission Accomplished"},
    "Earn 5 Gold Medals in the Night Levels.",//"Beat Up the Beat"},
    "Have at least 30,000 in the Bank",//"Meh"},
    "Do a Flaming SuperTrick Ultraflip of Fire",//"OMGWTFBBQ FTW"},
    "Crash 10 times in a row",//"Road Kill"},
};



Achievements::Achievements()
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
    

    CCLabelTTF *label = CCLabelTTF::create("ACHIEVEMENTS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    

    label = CCLabelTTF::create("ACHIEVEMENTS", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    
    CCMenu *screenMenu = CCMenu::create();
    CCLayer *container = CCLayer::create();
    screenMenu->setTouchEnabled(false);
    screenMenu->setPosition(0,0);
    container->addChild(screenMenu);
    //sprite = CCSprite::create("MainBackFiller.png");
    //sprite->setScale(scale);
    //container->addChild(sprite);
    //container->setContentSize(sprite->getContentSize());
    
    for(int i = 0; i < 15; i++)
    {
        bool isComplete = SaveLoad::m_SaveData.objectives[i]?true:false;
        
        CCMenuItem *temp = CCMenuItemImage::create("ctm_UI_ObjectivesDarkGreyBar_ver1.png", "ctm_UI_ObjectivesDarkGreyBar_ver1.png");
        temp->setScale(scale);
        
        sprite = CCSprite::createWithSpriteFrameName(s_ObjImg[i]);
        sprite->setPosition(ccp(29,28));
        if(!isComplete)
            sprite->setColor(ccc3(255/1.5,255/1.5,255/1.5));
        
        temp->addChild(sprite);
        
        if(isComplete)
        {
            sprite = CCSprite::create("ctm_UI_ObjectivesGreenLight.png");
            sprite->setPosition(ccp(429,27));
            temp->addChild(sprite);
        }
        
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 25.0f;
        
        
        ccColor3B shadowColor = ccc3(0,0,0);
        ccColor3B fillColor = ccc3(237,188,0);
        if(!isComplete)
            fillColor = ccc3(237/1.5,188/1.5,0);
        
        CCLabelTTF *label = CCLabelTTF::create(s_ObjName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setPosition(ccp(161,30));
        label->setColor(shadowColor);
        temp->addChild(label);
        label = CCLabelTTF::create(s_ObjName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setPosition(ccp(159,32));
        label->setColor(fillColor);
        temp->addChild(label);
        
        dim.width = 400.0f;
        dim.height = 18.0f;
        
        fillColor = ccc3(230,230,230);
        if(!isComplete)
            fillColor = ccc3(230/1.5,230/1.5,230/1.5);
        
        label = CCLabelTTF::create(s_ObjDesc[i],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(shadowColor);
        label->setPosition(ccp(261,15));
        temp->addChild(label);
        label = CCLabelTTF::create(s_ObjDesc[i],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(fillColor);
        label->setPosition(ccp(259,17));
        temp->addChild(label);
        
        screenMenu->addChild(temp);
    }
    screenMenu->alignItemsVerticallyWithPadding(0);
    
    CCSize viewSize;
    viewSize.width = 480.0f*scaleX;
    viewSize.height = 960.0*scaleY;
    CCScrollView *scrollView = CCScrollView::create(viewSize,container);
    //scrollView->setBounceable(false);
    scrollView->setContentSize(container->getContentSize());
    scrollView->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,0,280.0f*(scaleY/scaleX)-(viewSize.height/scaleY)/2.0f));
    scrollView->setContentOffset(ccp(240*scaleX,0));
    scrollView->setDirection(kCCScrollViewDirectionVertical);
        
    addChild(scrollView);
    
    //container->setPosition(ccp(240,160));
    //addChild(container);
    
    
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(Achievements::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
}

void Achievements::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
Achievements::~Achievements()
{
    
}

CCScene* Achievements::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new Achievements();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
void Achievements::EarnAchievement(cocos2d::CCNode* topNode, int index)
{
    while(topNode->getParent())
    {
        topNode = topNode->getParent();
    }
    float scale = ScreenHelper::getTextureScale();
    //CCSize screenSize = [CCDirector sharedDirector].winSize;
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    
    
    CCSprite *icon = CCSprite::createWithSpriteFrameName(s_ObjImg[index]);
    icon->setPosition(ccp(22.0f,20.0f));
    CCSprite *sprite = CCSprite::create("ContainerBack.png");
    sprite->setScale(scale);
    sprite->addChild(icon);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER, 0.0f, 50.0));
    
    CCSize dim;
    dim.width = 300.0f;
    dim.height = 33.0f;
    CCLabelTTF *label = CCLabelTTF::create(s_ObjName[index],"Jacoby ICG Black.ttf",28);
    label->setColor(ccc3(230,230,230));
    label->setPosition(ccp(sprite->getTextureRect().size.width/2.0f-10,sprite->getTextureRect().size.height/2.0f));
    sprite->addChild(label);
    
    topNode->addChild(sprite);
    
    CCMoveBy *action1 = CCMoveBy::create(0.1f,ccp(0.0f,-75.0f*scale));
    CCDelayTime *action2 = CCDelayTime::create(2.0f);
    CCMoveBy *action3 = CCMoveBy::create(0.1f,ccp(0.0f,75.0f*scale));
    CCAction *action4 = CCCallFuncN::create(sprite, callfuncN_selector(CCNode::removeFromParentAndCleanup));
    CCSequence *sequence = CCSequence::create(action1,action2,action3,action4,NULL);
    
    sprite->runAction(sequence);
    
    SaveLoad::m_SaveData.objectives[index]=1;
    SaveLoad::Save();
    
    //if([CheckAvailability canDoGameCenter])
    //{
    //    CTMAppDelegate *delegate = (CTMAppDelegate *)[[UIApplication sharedApplication] delegate];
    //    [delegate.gameCenter.gameCenterManager submitAchievement:s_AchiementArray[index] percentComplete:100.0f];
    //}

}
