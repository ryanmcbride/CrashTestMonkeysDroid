//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __LEVEL_H__
#define __LEVEL_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "Track.h"
#include "Rider/Rider.h"
#include "LevelContactListener.h"
#include "../GLES-Render.h"
#include "Backgrounds/BackGround.h"

class Rider;

class Level : public cocos2d::CCLayer
{
public:
   virtual ~Level();
    Level();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    static void ScreenShake(float duration, float magnitude, float speed);
    static cocos2d::CCNode* getHUD(){return Me->m_HUD;}
    void update(float dt);
protected:
    static Level *Me;
    static float m_ShakeDuration;
    static float m_ShakeMagnitude;
    static float m_ShakeSpeed;
    
    void FinalizeLevel();
    cocos2d::CCNode *m_HUD;
    cocos2d::CCLayer *m_DebugDraw;
    b2World* world;
    Track *m_Track;
    Rider *m_Rider;
    LevelContactListener *m_Listener;
    BackGround *m_BackGround;
    
    bool m_ZoomedOut;
    float m_idleTime;
};

#endif // __PAUSE_H__
