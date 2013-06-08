//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "McAcme.h"
#include "SimpleAudioEngine.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

int McAcme::s_adNumber = 1;

void McAcme::SetAdNumber(int num)
{
    if(num >=1 && num <= 20)
        s_adNumber = num;
}

McAcme::McAcme()
{
    float scale = ScreenHelper::getTextureScale();

    CCSprite *sprite = NULL;
    char tempName[64];
    
    if(s_adNumber >=1 && s_adNumber <= 6)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("McAcme1-6.plist","McAcme1-6.pvr.ccz");
        sprintf(tempName,"ctm_McAcme__Ad_%02d.png",s_adNumber);
        sprite = CCSprite::createWithSpriteFrameName(tempName);
    }
    else if(s_adNumber >=7 && s_adNumber <= 12)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("McAcme7-12.plist","McAcme7-12.pvr.ccz");
        sprintf(tempName,"ctm_McAcme__Ad_%02d.png",s_adNumber);
        sprite = CCSprite::createWithSpriteFrameName(tempName);
    }
    else if(s_adNumber >=13 && s_adNumber <= 18)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("McAcme13-18.plist","McAcme13-18.pvr.ccz");
        sprintf(tempName,"ctm_McAcme__Ad_%02d.png",s_adNumber);
        sprite = CCSprite::createWithSpriteFrameName(tempName);
    }
    else
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("McAcme19-20.plist","McAcme19-20.pvr.ccz");
        sprintf(tempName,"ctm_McAcme__Ad_%02d.png",s_adNumber);
        sprite = CCSprite::createWithSpriteFrameName(tempName);
    }
    
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    sprite->setScale(scale);
    addChild(sprite);
    m_Ad = sprite;
    m_Ad->setOpacity(0);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("McAcmeXtra.plist","McAcmeXtra.pvr.ccz");
    
    switch(RandomInt(0,100)%10)
    {
        case 0:
        case 3:
        case 6:
        case 9:
            BuildIntroShort();
            BuildOutroShort();
            m_TimeOut = 10.0f;
            break;
        case 1:
        case 4:
        case 7:
            BuildIntroMed();
            BuildOutroMed();
            m_TimeOut = 20.0f;
            break;
        case 2:
        case 5:
        case 8:
        default:
            BuildIntro();
            BuildOutro();
            m_TimeOut = 29.0f;
            break;
    };

}

McAcme::~McAcme()
{
}

void McAcme::BuildIntroShort()
{
    m_Ad->runAction(CCSequence::create(CCFadeIn::create(0.5),CCDelayTime::create(5.0f),CCFadeOut::create(0.5), NULL));
}
void McAcme::BuildOutroShort()
{
    float scale = ScreenHelper::getTextureScale();
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("McAcme_Intro_BG.png");
    addChild(background);
    background->setScale(scale);
    background->setPosition(m_Ad->getPosition());
    background->setOpacity(0);
    background->runAction(CCSequence::create(CCDelayTime::create(5.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *logo2 = CCSprite::createWithSpriteFrameName("McAcme_Intro_Logo.png");
    background->addChild(logo2);
    logo2->setPosition(ccp(240.0f,160.0f-10));
    logo2->setOpacity(0);
    logo2->runAction(CCSequence::create(CCDelayTime::create(5.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *name = CCSprite::createWithSpriteFrameName("McAcme_Intro_title.png");
    background->addChild(name);
    name->setPosition(ccp(240.0f,160.0f+100));
    name->setOpacity(0);
    name->runAction(CCSequence::create(CCDelayTime::create(5.5f),CCFadeIn::create(0.5),NULL));
    
    CCSprite *slogan = CCSprite::createWithSpriteFrameName("Advertisments_Intro.png");
    background->addChild(slogan);
    slogan->setPosition(ccp(240.0f,160.0f-100));
    slogan->setOpacity(0);
    slogan->runAction(CCSequence::create(CCDelayTime::create(5.5f),CCFadeIn::create(0.5),NULL));
}
void McAcme::BuildIntroMed()
{
    float scale = ScreenHelper::getTextureScale();
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("McAcme_Intro_BG.png");
    addChild(background);
    background->setScale(scale);
    background->setPosition(m_Ad->getPosition());
    background->setOpacity(0);
    background->runAction(CCSequence::create(CCFadeIn::create(0.5),CCDelayTime::create(4.5f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *logo = CCSprite::createWithSpriteFrameName("McAcme_Intro_Logo.png");
    background->addChild(logo);
    logo->setPosition(ccp(240.0f,160.0f-10));
    logo->setOpacity(0);
    logo->runAction(CCSequence::create(CCFadeIn::create(0.5), CCDelayTime::create(4.5f),CCFadeOut::create(0.5),NULL));
    
    CCSprite *name = CCSprite::createWithSpriteFrameName("McAcme_Intro_title.png");
    background->addChild(name);
    name->setPosition(ccp(240.0f,160.0f+100));
    name->setOpacity(0);
    name->runAction(CCSequence::create(CCDelayTime::create(0.5f),CCFadeIn::create(0.5), CCDelayTime::create(4.0f),CCFadeOut::create(0.5),NULL));
    
    CCSize dim;
    dim.width = 400;
    dim.height = 40;
    CCLabelTTF *forYou = CCLabelTTF::create("Has a Product for You!","Jacoby ICG Black.ttf",36,dim,kCCTextAlignmentCenter);
    CCLabelTTF *forYouShadow = CCLabelTTF::create("Has a Product for You!","Jacoby ICG Black.ttf",36,dim,kCCTextAlignmentCenter);
    forYou->setColor(ccc3(0,0,0));
    forYouShadow->setColor(ccc3(90,130,230));
    background->addChild(forYouShadow);
    background->addChild(forYou);
    forYou->setPosition(ccp(240.0f,160.0f-100));
    forYou->setOpacity(0);
    forYouShadow->setOpacity(0);
    forYouShadow->setPosition(ccp(forYou->getPosition().x+2,forYou->getPosition().y-2));
    
    forYou->runAction(CCSequence::create(CCDelayTime::create(1.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    forYouShadow->runAction(CCSequence::create(CCDelayTime::create(1.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    
    
    m_Ad->runAction(CCSequence::create(CCDelayTime::create(5.0f),CCFadeIn::create(0.5),CCDelayTime::create(5.0f),CCFadeOut::create(0.5), NULL));
}
void McAcme::BuildOutroMed()
{
    float scale = ScreenHelper::getTextureScale();
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("McAcme_Intro_BG.png");
    addChild(background);
    background->setScale(scale);
    background->setPosition(m_Ad->getPosition());
    background->setOpacity(0);
    background->runAction(CCSequence::create(CCDelayTime::create(10.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *easy = CCSprite::createWithSpriteFrameName("McAcme_3$_Easy.png");
    background->addChild(easy);
    easy->setPosition(ccp(240.0f-75,160.0f+100));
    easy->setOpacity(0);
    easy->runAction(CCSequence::create(CCDelayTime::create(10.5f),CCFadeIn::create(0.5),CCDelayTime::create(4.0f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *logo = CCSprite::createWithSpriteFrameName("McAcme_3$_Logo.png");
    background->addChild(logo);
    logo->setPosition(ccp(240.0f+150,160.0f+100));
    logo->setOpacity(0);
    logo->runAction(CCSequence::create(CCDelayTime::create(10.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *price = CCSprite::createWithSpriteFrameName("McAcme_3$_Flare.png");
    background->addChild(price);
    price->setPosition(ccp(240.0f+20,160.0f));
    price->setOpacity(0);
    price->runAction(CCSequence::create(CCDelayTime::create(11.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *price2 = CCSprite::createWithSpriteFrameName("McAcme_3$_Price.png");
    background->addChild(price2);
    price2->setPosition(ccp(240.0f,160.0f-50));
    price2->setOpacity(0);
    price2->runAction(CCSequence::create(CCDelayTime::create(11.5f),CCFadeIn::create(0.5), CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    
    
    CCSprite *callFlare = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Flare.png");
    background->addChild(callFlare);
    callFlare->setPosition(ccp(240.0f,160.0f-50));
    callFlare->setOpacity(0);
    callFlare->runAction(CCSequence::create(CCDelayTime::create(15.0f),CCFadeIn::create(0.5),NULL));
    
    CCSprite *call = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Call.png");
    background->addChild(call);
    call->setPosition(ccp(240.0f,160.0f-50));
    call->setOpacity(0);
    call->runAction(CCSequence::create(CCDelayTime::create(15.0f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *operators = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Operators.png");
    background->addChild(operators);
    operators->setPosition(ccp(240.0f-75,160.0f+100));
    operators->setOpacity(0);
    operators->runAction(CCSequence::create(CCDelayTime::create(16.0f),CCFadeIn::create(0.5), NULL));

}
#define NUM_NEEDS 13
void McAcme::BuildIntro()
{
    float scale = ScreenHelper::getTextureScale();
    CCSize dim;
    dim.width = 220*scale;
    dim.height = 160*scale;
    const char *needArray[NUM_NEEDS] =
    {
        "Do you have trouble sleeping?",
        "Are you tired of working for peanuts?",
        "Do you feel entitled?",
        "Are you a compulsive shopper?",
        "Do you hear strange voices?",
        "Is your medication wearing off?",
        "Have you ever wet your pants?",
        "Do you have a horrible job?",
        "Do you have unusual cravings?",
        "Have you ever trained a walrus?",
        "Are there too many hours in the day?",
        "Has somebody turned off the light at the end of the tunnel?",
        "Is your neighbors grass always greener?",
    };
    const char *needArray2[NUM_NEEDS] =
    {
        "Do you want more friends?",
        "Are you watching TV?",
        "Are you afraid of aliens?",
        "Do minnows follow you around?",
        "Do your plants need water?",
        "Are you always forgetting something?",
        "Are you being followed?",
        "Did you see the news?",
        "Why did the chicken cross the road?",
        "Do you feel like a square peg in a round hole?",
        "How many monkeys does it take to change a lightbulb?",
        "Have you ever wanted more for yourself?",
        "Do you have large feet?",
    };
    int index = RandomInt(0,NUM_NEEDS);
    CCLabelTTF *firstText = CCLabelTTF::create(needArray[index],"impact.ttf",28*scale,dim,kCCTextAlignmentLeft);
    
    firstText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -120, 40));
    firstText->runAction(CCSequence::create(CCDelayTime::create(2.5f),CCFadeOut::create(0.5),CCCallFuncN::create(firstText, callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
    addChild(firstText);
    
    index = RandomInt(0,8);
    CCLabelTTF *secondText = CCLabelTTF::create(needArray2[index],"",28*scale,dim,kCCTextAlignmentRight);
    secondText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 120, -120));
    secondText->setOpacity(0);
    secondText->runAction(CCSequence::create(CCDelayTime::create(2.5f),CCFadeIn::create(0.5),CCDelayTime::create(2.5f),CCFadeOut::create(0.5), CCCallFuncN::create(firstText, callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
    addChild(secondText);
    
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("McAcme_Intro_BG.png");
    addChild(background);
    background->setScale(scale);
    background->setPosition(m_Ad->getPosition());
    background->setOpacity(0);
    background->runAction(CCSequence::create(CCDelayTime::create(6.0f),CCFadeIn::create(0.5),CCDelayTime::create(4.5f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *logo = CCSprite::createWithSpriteFrameName("McAcme_Intro_Logo.png");
    background->addChild(logo);
    logo->setPosition(ccp(240.0f,160.0f-10));
    logo->setOpacity(0);
    logo->runAction(CCSequence::create(CCDelayTime::create(6.0f),CCFadeIn::create(0.5), CCDelayTime::create(4.5f),CCFadeOut::create(0.5),NULL));
    
    CCSprite *name = CCSprite::createWithSpriteFrameName("McAcme_Intro_title.png");
    background->addChild(name);
    name->setPosition(ccp(240.0f,160.0f+100));
    name->setOpacity(0);
    name->runAction(CCSequence::create(CCDelayTime::create(6.5f),CCFadeIn::create(0.5), CCDelayTime::create(4.0f),CCFadeOut::create(0.5),NULL));
    
    dim.width = 400;
    dim.height = 40;
    CCLabelTTF *forYou = CCLabelTTF::create("Has a Product for You!","Jacoby ICG Black.ttf",36,dim,kCCTextAlignmentCenter);
    CCLabelTTF *forYouShadow = CCLabelTTF::create("Has a Product for You!","Jacoby ICG Black.ttf",36,dim,kCCTextAlignmentCenter);
    forYou->setColor(ccc3(0,0,0));
    forYouShadow->setColor(ccc3(90,130,230));
    background->addChild(forYouShadow);
    background->addChild(forYou);
    forYou->setPosition(ccp(240.0f,160.0f-100));
    forYou->setOpacity(0);
    forYouShadow->setOpacity(0);
    forYouShadow->setPosition(ccp(forYou->getPosition().x+2,forYou->getPosition().y-2));
    
    forYou->runAction(CCSequence::create(CCDelayTime::create(7.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    forYouShadow->runAction(CCSequence::create(CCDelayTime::create(7.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    
    m_Ad->runAction(CCSequence::create(CCDelayTime::create(11.0f),CCFadeIn::create(0.5),CCDelayTime::create(5.0f),CCFadeOut::create(0.5), NULL));
}
void McAcme::BuildOutro()
{
    float scale = ScreenHelper::getTextureScale();
    //16.5
    CCSprite *background = CCSprite::createWithSpriteFrameName("McAcme_Intro_BG.png");
    addChild(background);
    background->setScale(scale);
    background->setPosition(m_Ad->getPosition());
    background->setOpacity(0);
    background->runAction(CCSequence::create(CCDelayTime::create(16.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *easy = CCSprite::createWithSpriteFrameName("McAcme_3$_Easy.png");
    background->addChild(easy);
    easy->setPosition(ccp(240.0f-75,160.0f+100));
    easy->setOpacity(0);
    easy->runAction(CCSequence::create(CCDelayTime::create(16.5f),CCFadeIn::create(0.5),CCDelayTime::create(4.0f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *logo = CCSprite::createWithSpriteFrameName("McAcme_3$_Logo.png");
    background->addChild(logo);
    logo->setPosition(ccp(240.0f+150,160.0f+100));
    logo->setOpacity(0);
    logo->runAction(CCSequence::create(CCDelayTime::create(16.5f),CCFadeIn::create(0.5),CCDelayTime::create(8.5f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *price = CCSprite::createWithSpriteFrameName("McAcme_3$_Flare.png");
    background->addChild(price);
    price->setPosition(ccp(240.0f+20,160.0f));
    price->setOpacity(0);
    price->runAction(CCSequence::create(CCDelayTime::create(17.5f),CCFadeIn::create(0.5),CCDelayTime::create(3.0f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *price2 = CCSprite::createWithSpriteFrameName("McAcme_3$_Price.png");
    background->addChild(price2);
    price2->setPosition(ccp(240.0f,160.0f-50));
    price2->setOpacity(0);
    price2->runAction(CCSequence::create(CCDelayTime::create(17.5f),CCFadeIn::create(0.5), CCDelayTime::create(3.0f),CCFadeOut::create(0.5),NULL));
    
    
    CCSprite *callFlare = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Flare.png");
    background->addChild(callFlare);
    callFlare->setPosition(ccp(240.0f,160.0f-50));
    callFlare->setOpacity(0);
    callFlare->runAction(CCSequence::create(CCDelayTime::create(21.0f),CCFadeIn::create(0.5), CCDelayTime::create(4.0f),CCFadeOut::create(0.5),NULL));
    
    CCSprite *call = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Call.png");
    background->addChild(call);
    call->setPosition(ccp(240.0f,160.0f-50));
    call->setOpacity(0);
    call->runAction(CCSequence::create(CCDelayTime::create(21.0f),CCFadeIn::create(0.5), CCDelayTime::create(4.0f),CCFadeOut::create(0.5), NULL));
    
    CCSprite *operators = CCSprite::createWithSpriteFrameName("McAcme_CALLNOW_Operators.png");
    background->addChild(operators);
    operators->setPosition(ccp(240.0f-75,160.0f+100));
    operators->setOpacity(0);
    operators->runAction(CCSequence::create(CCDelayTime::create(22.0f),CCFadeIn::create(0.5), CCDelayTime::create(3.0f),CCFadeOut::create(0.5), NULL));
    
    
    
    CCSprite *logo2 = CCSprite::createWithSpriteFrameName("McAcme_Intro_Logo.png");
    background->addChild(logo2);
    logo2->setPosition(ccp(240.0f,160.0f-10));
    logo2->setOpacity(0);
    logo2->runAction(CCSequence::create(CCDelayTime::create(25.5f),CCFadeIn::create(0.5), NULL));
    
    CCSprite *name = CCSprite::createWithSpriteFrameName("McAcme_Intro_title.png");
    background->addChild(name);
    name->setPosition(ccp(240.0f,160.0f+100));
    name->setOpacity(0);
    name->runAction(CCSequence::create(CCDelayTime::create(25.5f),CCFadeIn::create(0.5),NULL));
    
    CCSprite *slogan = CCSprite::createWithSpriteFrameName("Advertisments_Intro.png");
    background->addChild(slogan);
    slogan->setPosition(ccp(240.0f,160.0f-100));
    slogan->setOpacity(0);
    slogan->runAction(CCSequence::create(CCDelayTime::create(25.5f),CCFadeIn::create(0.5),NULL));
}

void McAcme::update(float dt)
{
    Commercial::update(dt);
    
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMMcAcmeMusic.3gp", true);
}