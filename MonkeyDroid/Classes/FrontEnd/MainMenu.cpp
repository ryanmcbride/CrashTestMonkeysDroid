//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Feedback.h"
#include "Achievements.h"
#include "Options.h"
#include "Store/Store.h"
#include "RegionSelect.h"

#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

class AngryBird
{
public:
	AngryBird(CCNode*layer,float scale)
	{
        char trickName[128];
		int imageNum = CCRANDOM_0_1()*9;
		switch(imageNum)
		{
			default:
			case 0:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_banana_Big.png");
				sprite->setScale(scale);
                layer->addChild(sprite,3);
				break;
			case 1:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_banana_Medium.png");
				sprite->setScale(scale);
                layer->addChild(sprite,2);
				break;
			case 2:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_banana_Small.png");
				sprite->setScale(scale);
                layer->addChild(sprite,1);
				break;
			case 3:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_coconut_Big.png");
				sprite->setScale(scale);
                layer->addChild(sprite,3);
				break;
			case 4:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_coconut_Medium.png");
				sprite->setScale(scale);
                layer->addChild(sprite,2);
				break;
			case 5:
				sprite = CCSprite::createWithSpriteFrameName("ctm_StartScreen_coconut_Small.png");
				sprite->setScale(scale);
                layer->addChild(sprite,1);
				break;
			case 6:
                sprintf(trickName,"ctm_StartScreen_Trick%d.png",(int)(CCRANDOM_0_1()*6+1));
				sprite = CCSprite::createWithSpriteFrameName(trickName);
                sprite->setScale(scale*1.0f/2.0f);
				layer->addChild(sprite,3);
				break;
			case 7:
				sprintf(trickName,"ctm_StartScreen_Trick%d.png",(int)(CCRANDOM_0_1()*6+1));
				sprite = CCSprite::createWithSpriteFrameName(trickName);
                sprite->setScale(scale*1.0f/4.0f);
				layer->addChild(sprite,2);
				break;
			case 8:
				sprintf(trickName,"ctm_StartScreen_Trick%d.png",(int)(CCRANDOM_0_1()*6+1));
				sprite = CCSprite::createWithSpriteFrameName(trickName);
                sprite->setScale(scale*1.0f/8.0f);
				layer->addChild(sprite,1);
				break;
		};
		imageNum = CCRANDOM_0_1()*4+1;
		
		if(imageNum & 0x01)
		{
			vel.x = 200*scale;
			sprite->setPosition(CCPointMake(10.0f*scale,-30.0f*scale));
		}
		else
		{
			vel.x = -200*scale;
			sprite->setPosition(CCPointMake(460.0f*scale,-30.0f*scale));
			sprite->setFlipX(true);
		}
		vel.y = (200 + 100*imageNum/2)*scale;
		rotVel = CCRANDOM_MINUS1_1()*360.0f;
		m_destroy = false;
	}
	~AngryBird()
	{
		sprite->removeFromParentAndCleanup(true);
	}
	void tick(float dt,float scale)
	{
		vel.y -= 300*dt*scale;
		sprite->setPosition(CCPointMake(sprite->getPosition().x+vel.x*dt,sprite->getPosition().y+vel.y*dt));
		
		
		sprite->setRotation(sprite->getRotation() + rotVel*dt);
		
		if(sprite->getPosition().y < -40.0f*scale)
			m_destroy = true;
	}
	bool m_destroy;
	CCSprite *sprite;
	CCPoint vel;
	float rotVel;
};


MainMenu::MainMenu()
{
    setTouchEnabled( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMThemeMusicv3.3gp", true);
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();

    CCSprite *sprite = CCSprite::create("ctm_island_BG_01.png");
    sprite->setScaleX(s.width/940.0f);
    sprite->setScaleY(s.width/940.0f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,40.0f));
    addChild(sprite,0);
    
    if(ScreenHelper::AddOBBSpriteToCache("TikiObjs.png","TikiObjs.plist"))
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_Island_01.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 64.0f, 100.0f));
        addChild(sprite,0);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_Island_02.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 380.0f, 100.0f));
        addChild(sprite,0);
    }
    
    for(int i = 0; i < 3; i++)
    {
        sprite = CCSprite::create("ctm_256_metalpanel.png");
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scaleY);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 23.0f));
        addChild(sprite,4);
        
        sprite = CCSprite::create("ctm_256_Front_hazardstripe.png");
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scaleY);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 55.0f));
        addChild(sprite,4);
    }	

    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_StartScreen.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_StartScreen.pv.plist");
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
 
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_New_StartScreen_Title.png");
    sprite->setScale(scale*0.5f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-60.0f));
    addChild(sprite,4);
 
    CCMenuItem *PlayButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_UI_Play_Btn_ver1.png"), CCSprite::createWithSpriteFrameName("ctm_UI_Play_Btn_Down.png"), this, menu_selector(MainMenu::playButtonTapped));
    PlayButton->setScale(scale);
    PlayButton->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    
    CCMenuItem *StoreButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_17.png"), CCSprite::createWithSpriteFrameName("ctm_Button_17_Down.png"), this, menu_selector(MainMenu::storeButtonTapped));
    StoreButton->setScale(scale);
    StoreButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_RIGHT,-40.0f,35.0f));

    CCMenuItem *OptionsButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_22.png"), CCSprite::createWithSpriteFrameName("ctm_Button_22_Down.png"), this, menu_selector(MainMenu::optionsButtonTapped));
    OptionsButton->setScale(scale);
    OptionsButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,40.0f,35.0f));

    CCMenuItem *AchievementsButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_18.png"), CCSprite::createWithSpriteFrameName("ctm_Button_18_Down.png"), this, menu_selector(MainMenu::achievementsButtonTapped));
    AchievementsButton->setScale(scale);
    AchievementsButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,50.0f,35.0f));

    CCMenuItem *FeedbackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("FeedbackIcon_Options.png"), CCSprite::createWithSpriteFrameName("FeedbackIcon_Options_Down.png"), this, menu_selector(MainMenu::feedbackButtonTapped));
    FeedbackButton->setScale(scale);
    FeedbackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,-50.0f,32.0f));

    CCMenu* menu = CCMenu::create(PlayButton, StoreButton, OptionsButton, AchievementsButton, FeedbackButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
        
    scheduleUpdate();
    
    m_BirdNode = CCNode::create();
    addChild(m_BirdNode,1);
    m_AngryBirds[0] = (void*)new AngryBird(m_BirdNode,scale);
    m_AngryBirds[1] = NULL;
    m_AngryBirds[2] = NULL;
    playbuttonTapped = false;
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("Select.wav");
}
void MainMenu::playButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(RegionSelect::scene());
}
void MainMenu::storeButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    
    CCDirector::sharedDirector()->pushScene(Store::scene());
}
void MainMenu::optionsButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Options::scene());
}
void MainMenu::achievementsButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Achievements::scene());
}
void MainMenu::feedbackButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(FeedbackMenu::scene());
}

MainMenu::~MainMenu()
{
    
}

void MainMenu::update(float dt)
{
    float scale = ScreenHelper::getTextureScale();
    for(int i = 0; i < 3; i++)
	{
		if(m_AngryBirds[i] != NULL)
		{
			((AngryBird*)m_AngryBirds[i])->tick(dt,scale);
			if(((AngryBird*)m_AngryBirds[i])->m_destroy == true && !playbuttonTapped)
			{

				delete ((AngryBird*)m_AngryBirds[i]);
				m_AngryBirds[i] = (void*) new AngryBird(m_BirdNode,scale);
				if(i < 2 && m_AngryBirds[i+1] == NULL)
					m_AngryBirds[i+1] = (void*) new AngryBird(m_BirdNode,scale);
			}
		}
	}
}

CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MainMenu();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
