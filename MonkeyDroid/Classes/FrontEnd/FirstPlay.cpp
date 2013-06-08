//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "FirstPlay.h"
#include "SimpleAudioEngine.h"
#include "ScreenHelper.h"
#include "Loading.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

FirstPlay::FirstPlay()
{
    setTouchEnabled( true );
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    m_RatingNode = CCNode::create();
    addChild(m_RatingNode);
    CCLayerColor *bg = CCLayerColor::create(ccc4(10,240,10,255),480.0f*scaleX,320.0f*scaleY);
    m_RatingNode->addChild(bg);
    
    CCPoint p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,72.0f);
    char *line = (char*)"The following has been rated";
    CCLabelTTF *label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(p.x+2,p.y-2));
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    
    p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,0.0f);
    line = (char*)"MEH";
    label = CCLabelTTF::create(line, "impact.ttf", 64*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(p.x+2,p.y-2));
    label = CCLabelTTF::create(line, "impact.ttf", 64*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    
    
    p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,-72.0f);
    line = (char*)"For Monkey Excrement Hijinks.";
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(p.x+2,p.y-2));
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    
    
    p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,-102.0f);
    line = (char*)"Please Dress Accordingly.";
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ccp(p.x+2,p.y-2));
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_RatingNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    
    
    
    m_ConclusionNode = CCNode::create();
    addChild(m_ConclusionNode);
    m_ConclusionNode->setVisible(false);
    
    bg = CCLayerColor::create(ccc4(0,0,0,255),480.0f*scaleX,320.0f*scaleY);
    m_ConclusionNode->addChild(bg);
    
    p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,20.0f);
    line = (char*)"And Now";
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_ConclusionNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    p = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,-20.0f);
    line = (char*)"The Thrilling Conclusion";
    label = CCLabelTTF::create(line, "impact.ttf", 28*scale);
    m_ConclusionNode->addChild(label, 2);
    label->setColor(ccc3(255,255,255));
    label->setPosition(p);
    
    scheduleUpdate();
    
    m_TimeOut = 6.0f;
    m_bMoviePlayed = false;
}


void FirstPlay::update(float dt)
{
    m_TimeOut -= dt;
    if(!m_bMoviePlayed && m_TimeOut < 3.0f)
    {
        m_bMoviePlayed = true;
        m_RatingNode->setVisible(false);
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
    if(m_TimeOut <= 2.0f)
    {
        m_ConclusionNode->setVisible(true);
    }
    if(m_TimeOut <= 0.0f)
    {
        CCDirector::sharedDirector()->replaceScene(Loading::scene());
    }
}
FirstPlay::~FirstPlay()
{
    
}

CCScene* FirstPlay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new FirstPlay();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
