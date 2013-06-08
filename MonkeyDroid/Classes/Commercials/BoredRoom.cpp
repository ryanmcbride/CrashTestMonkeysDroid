//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "BoredRoom.h"
#include "SimpleAudioEngine.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum
{
    BLINK_OPEN = 0,
    BLINK_HALF = 1,
    BLINK_SHUT = 2,
    
    BLINK_HALF2 = 3,
    BLINK_OPEN2 = 4,
    
    BLINK_HALF3 = 5,
    BLINK_SHUT3 = 6,
    
    BLINK_HALF4 = 7,
    BLINK_OPEN4 = 8,
};
enum
{
    PUNCH_WAIT = 0,
    PUNCH_ONE = 1,
    PUNCH_TWO = 2,
    PUNCH_THREE = 3,
    PUNCH_HIT = 4,
    AFTER_PUNCH_ONE = 5,
    AFTER_PUNCH_TWO = 6,
    AFTER_PUNCH_THREE = 7,
    AFTER_PUNCH_FOUR = 8,
};
enum
{
    FART_WAIT = 0,
    FART_START = 1,
    FART_HOLD = 2,
    FART_FINISH = 3,
    FART_WAIT_DONE = 4,
};


BoredRoom::BoredRoom()
{
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("JohnGeoff.plist","JohnGeoff.pvr.ccz");
    
    CCSprite *sprite = NULL;
    
    
    switch(RandomInt(0, 3))
    {
        default:
        case 0:
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_BG_1.png");
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            sprite->setScale(scale);
            addChild(sprite);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Bowl_1.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 40, 0));
            addChild(sprite,1);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Sign_1.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            addChild(sprite);
            break;
        case 1:
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Bg_2.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            addChild(sprite);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Bowl_2.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 40, 0));
            addChild(sprite,1);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Sign_2.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            addChild(sprite);
            break;
        case 2:
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Bg_3.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            addChild(sprite);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Bowl_3.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 40, 0));
            addChild(sprite,1);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_Cage_Sign_3.png");
            sprite->setScale(scale);
            sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            addChild(sprite);
            break;
    }
    
    int objectPlacement = RandomInt(0, 17);
    if(objectPlacement<=11)
    {
        char objName[64];
        sprintf(objName,"BoredRoom_Props_%04d.png",objectPlacement);
        sprite = CCSprite::createWithSpriteFrameName(objName);
        sprite->setScale(scale);
        
        if( (objectPlacement==3 || objectPlacement==5) || RandomInt(0, 100)<75)
        {
            if(objectPlacement==3 || objectPlacement==5)
                sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 190, -50));
            else
                sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 190, -100));
            addChild(sprite);
        }
        else
        {
            sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -200, -120));
            addChild(sprite,1);
        }
        
        
    }
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_shadow.png");
    sprite->setScaleX(0.9f*scale);
    sprite->setScaleY(scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -20, -120));
    addChild(sprite);
    
    
    int i;
    for(i = 0; i < 6; i++)
    {
        char geoffFrame[64];
        sprintf(geoffFrame,"ctm_Zoo_Geoff_%02d.png",i+1);
        geoff[i] = CCSprite::createWithSpriteFrameName(geoffFrame);
        geoff[i]->retain();
        geoff[i]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -140, 0));
        geoff[i]->setScale(scale);
        
    }
    addChild(geoff[0]);
    
    geoffFart[0] = CCSprite::createWithSpriteFrameName("ctm_Zoo_Geoff_01_A.png");
    geoffFart[0]->retain();
    geoffFart[0]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -140, 0));
    geoffFart[1] = CCSprite::createWithSpriteFrameName("ctm_Zoo_Geoff_01_B.png");
    geoffFart[1]->retain();
    geoffFart[1]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -140, 0));
    geoffFart[0]->setScale(scale);
    geoffFart[1]->setScale(scale);
    
    for(i = 0; i < 7; i++)
    {
        char geoffHeadFrame[64];
        sprintf(geoffHeadFrame,"ctm_Zoo_GeoffHead_%02d.png",i+1);
        geoffHead[i] = CCSprite::createWithSpriteFrameName(geoffHeadFrame);
        geoffHead[i]->retain();
        geoffHead[i]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -195, 73));
        geoffHead[i]->setScale(scale);
    }
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_Zoo_John_01.png");
    sprite->setScale(scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 35, 0));
    addChild(sprite);
    
    
    for(i = 0; i < 6; i++)
    {
        char armsFrame[64];
        sprintf(armsFrame,"ctm_Zoo_JohnArm_%02d.png",i+1);
        arms[i] = CCSprite::createWithSpriteFrameName(armsFrame);
        arms[i]->retain();
        arms[i]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -23, 0));
        arms[i]->setScale(scale);
    }
    addChild(arms[0]);
    eyes[0] = CCSprite::createWithSpriteFrameName("ctm_Zoo_John_EyesClosed.png");
    eyes[0]->retain();
    eyes[0]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 35, 0));
    eyes[1] = CCSprite::createWithSpriteFrameName("ctm_Zoo_John_EyesHalf.png");
    eyes[1]->retain();
    eyes[1]->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 35, 0));
    eyes[0]->setScale(scale);
    eyes[1]->setScale(scale);
    blinkTime = 4.0f;
    blinkState = BLINK_OPEN;
    
    
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_BoredRoom_Title.png");
    sprite->setScale(scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0, 0));
    addChild(sprite,3);
    sprite->runAction(CCSequence::create(CCDelayTime::create(3.0f),CCMoveTo::create(0.1f,CCPointMake(480.0f*1.6f*scale, 160.0f*scale)),NULL));
    
    isFart = isSlap = false;
    int chance = RandomInt(0,100);
    if(chance >= 65)
        isSlap = true;
    else if(chance >= 30)
        isFart = true;
    
    punchTime = 100.0f;
    punchState = PUNCH_WAIT;
    
    headBobbleTime = 100.0f;
    headBobbleState = 0;
    
    fartTime = 100.0f;
    fartState = 0;
    
    m_TimeOut = 10.0f;

    
}
BoredRoom::~BoredRoom()
{
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    int i;
    for(i = 0; i < 6; i++)
    {
        arms[i]->autorelease();
        geoff[i]->autorelease();
    }
    for(i=0; i < 7; i++)
    {
        geoffHead[i]->autorelease();
    }
    eyes[0]->autorelease();
    eyes[1]->autorelease();
    geoffFart[0]->autorelease();
    geoffFart[1]->autorelease();
    
}

void BoredRoom::update(float dt)
{
    /*m_TimeOut -= dt;
     if(m_TimeOut <= 0.0f)
     {
         CCDirector::sharedDirector()->replaceScene(BoredRoom::scene());
         m_TimeOut = 100.0f;
     }*/

    Commercial::update(dt);
    
    blinkTick(dt);
    if(isSlap)
    {
        punchTick(dt);
        headBobbleTick(dt);
    }
    if(isFart)
    {
        fartTick(dt);
    }
    
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGZooMusic.3gp", true);
    
}


void BoredRoom::headBobbleTick(float dt)
{
    headBobbleTime -= dt;
    if(headBobbleState <  7 && headBobbleTime <= 0.0f)
    {
        if(headBobbleState)
            geoffHead[headBobbleState-1]->removeFromParentAndCleanup(false);
        
        addChild(geoffHead[headBobbleState]);
        headBobbleState++;
        headBobbleTime = 1.0f/24.0f;
    }
}
void BoredRoom::punchTick(float dt)
{
    punchTime -= dt;
    switch(punchState)
    {
        case PUNCH_WAIT:
            if(punchTime <= 0.0f)
            {
                punchState = PUNCH_ONE;
                arms[0]->removeFromParentAndCleanup(false);
                addChild(arms[1]);
                punchTime = 1.0f/24.0f;
            }
            break;
        case PUNCH_ONE:
            if(punchTime <= 0.0f)
            {
                punchState = PUNCH_TWO;
                arms[1]->removeFromParentAndCleanup(false);
                addChild(arms[2]);
                punchTime = 1.0f/24.0f;
            }
            break;
        case PUNCH_TWO:
            if(punchTime <= 0.0f)
            {
                punchState = PUNCH_THREE;
                arms[2]->removeFromParentAndCleanup(false);
                addChild(arms[3]);
                punchTime = 0.5f/24.0f;
            }
            break;
        case PUNCH_THREE:
            if(punchTime <= 0.0f)
            {
                punchState = PUNCH_HIT;
                arms[3]->removeFromParentAndCleanup(false);
                addChild(arms[4]);
                punchTime = 0.5f/24.0f;
                AudioManager::PlayEffect(AUDIO_BR_PUNCH);
            }
            break;
        case PUNCH_HIT:
            if(punchTime <= 0.0f)
            {
                punchState = AFTER_PUNCH_ONE;
                arms[4]->removeFromParentAndCleanup(false);
                addChild(arms[5]);
                
                geoff[0]->removeFromParentAndCleanup(false);
                addChild(geoff[1]);
                punchTime = 1.0f/24.0f;
            }
            break;
        case AFTER_PUNCH_ONE:
            if(punchTime <= 0.0f)
            {
                punchState = AFTER_PUNCH_TWO;
                
                geoff[1]->removeFromParentAndCleanup(false);
                addChild(geoff[2]);
                
                punchTime = 1.0f/24.0f;
            }
            break;
        case AFTER_PUNCH_TWO:
            if(punchTime <= 0.0f)
            {
                punchState = AFTER_PUNCH_THREE;
                
                geoff[2]->removeFromParentAndCleanup(false);
                addChild(geoff[3]);
                
                punchTime = 1.0f/24.0f;
            }
            break;
        case AFTER_PUNCH_THREE:
            if(punchTime <= 0.0f)
            {
                punchState = AFTER_PUNCH_FOUR;
                
                geoff[3]->removeFromParentAndCleanup(false);
                addChild(geoff[4]);
                
                punchTime = 1.0f/24.0f;
            }
            break;
        case AFTER_PUNCH_FOUR:
            if(punchTime <= 0.0f)
            {
                punchState = AFTER_PUNCH_FOUR+1;
                
                geoff[4]->removeFromParentAndCleanup(false);
                addChild(geoff[5]);
                m_TimeOut = 1.0f;
                headBobbleTime = 0.0f;
            }
            break;
            
    }
}
void BoredRoom::blinkTick(float dt)
{
    blinkTime -= dt;
    switch(blinkState)
    {
        case BLINK_OPEN:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_HALF;
                addChild(eyes[1]);
                blinkTime = 1.0f/24.0f;
                AudioManager::PlayEffect(AUDIO_BR_BLINK);
            }
            break;
        case BLINK_HALF:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_SHUT;
                eyes[1]->removeFromParentAndCleanup(false);
                addChild(eyes[0]);
                blinkTime = 2.0f/24.0f;
            }
            break;
        case BLINK_SHUT:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_HALF2;
                eyes[0]->removeFromParentAndCleanup(false);
                addChild(eyes[1]);
                blinkTime = 1.0f/24.0f;
            }
            break;
        case BLINK_HALF2:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_OPEN2;
                eyes[1]->removeFromParentAndCleanup(false);
                blinkTime = 8.0f/24.0f;
            }
            break;
        case BLINK_OPEN2:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_HALF3;
                addChild(eyes[1]);
                blinkTime = 1.0f/24.0f;
                AudioManager::PlayEffect(AUDIO_BR_BLINK);
            }
            break;
        case BLINK_HALF3:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_SHUT3;
                eyes[1]->removeFromParentAndCleanup(false);
                addChild(eyes[0]);
                blinkTime = 1.0f/24.0f;
            }
            break;
        case BLINK_SHUT3:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_HALF4;
                eyes[0]->removeFromParentAndCleanup(false);
                addChild(eyes[1]);
                blinkTime = 1.0f/24.0f;
            }
            break;
        case BLINK_HALF4:
            if(blinkTime <= 0.0f)
            {
                blinkState = BLINK_OPEN4;
                eyes[1]->removeFromParentAndCleanup(false);
                blinkTime = 1.0f/24.0f;
                punchTime = 8.0f/24.0f;
                fartTime = 8.0f/24.0f;
                if(!isSlap && !isFart)
                {
                    m_TimeOut = 0.8f;
                }
            }
            break;
        case BLINK_OPEN4:
            break;
    }
    
}
void BoredRoom::fartTick(float dt)
{
    fartTime -= dt;
    switch(fartState)
    {
        case FART_WAIT:
            if(fartTime<=0)
            {
                fartState = FART_START;
                fartTime = 0.1f;
                
                geoff[0]->removeFromParentAndCleanup(false);
                addChild(geoffFart[0]);
                AudioManager::PlayEffect(AUDIO_BR_FART);
            }
            break;
        case FART_START:
            if(fartTime<=0)
            {
                fartState = FART_HOLD;
                fartTime = 1.0f;
                
                geoffFart[0]->removeFromParentAndCleanup(false);
                addChild(geoffFart[1]);
            }
            break;
        case FART_HOLD:
            if(fartTime<=0)
            {
                fartState = FART_FINISH;
                fartTime = 0.1f;
                
                geoffFart[1]->removeFromParentAndCleanup(false);
                addChild(geoffFart[0]);
            }
            break;
        case FART_FINISH:
            if(fartTime<=0)
            {
                fartState = FART_WAIT_DONE;
                fartTime = 0.0f;
                m_TimeOut = 1.0f;
                
                geoffFart[0]->removeFromParentAndCleanup(false);
                addChild(geoff[0]);
            }
            break;
        case FART_WAIT_DONE:
            break;
    };
}


