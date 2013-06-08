//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Commercial.h"
#include "SimpleAudioEngine.h"
#include "../ScreenHelper.h"
#include "../FrontEnd/Loading.h"

#include "BoredRoom.h"
#include "CarCrash.h"
#include "CNN.h"
#include "McAcme.h"

using namespace cocos2d;
using namespace CocosDenshion;

Commercial::Commercial()
{
    glClearColor(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f);
    setTouchEnabled( true );
    ScreenHelper::isCinematic = true;
    m_TimeOut = 3.0f;
    scheduleUpdate();
}
Commercial::~Commercial()
{
    ScreenHelper::isCinematic = false;
}
void Commercial::update(float dt)
{
    m_TimeOut -= dt;
    if(m_TimeOut < 0.0f)
    {
        CCDirector::sharedDirector()->replaceScene(Loading::scene());
        m_TimeOut = 100.0f;
    }
}
CCScene* Commercial::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = NULL;
    int random = CCRANDOM_0_1()*4.0f;
    switch(random)
    {
    default:
    case 0:
        layer = new McAcme();
        break;
    case 1:
        layer = new CNN();
        break;
    case 2:
        layer = new BoredRoom();
        break;
    case 3:
        layer = new CarCrash();
        break;
    }
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
void Commercial::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        m_TimeOut = -1.0f;
    }
}
