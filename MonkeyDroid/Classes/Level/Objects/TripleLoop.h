//
//  Loop.h
//  CTM
//
//  Created by Ryan McBride on 3/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TRIPLE_LOOP_H__
#define __TRIPLE_LOOP_H__

#include "cocos2d.h"
#include "Box2d.h"
#include "TextureObject.h"
#include "TrackObject.h"
#include "Spline.h"

class TripleLoop : public TrackObject
{
public:
	TripleLoop(b2World *world, cocos2d::CCNode *ccLayer, cocos2d::CCLayer *frontLayer, b2Vec2 *startPos);
	virtual ~TripleLoop();
	virtual void CreateSelf();
	virtual void DestroySelf();
	virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
    bool m_bLeftSide;
    bool m_bThisLoop;
	
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_frontLayer;
	b2Body *m_MainCollision;
    b2Fixture *m_ForwardTrigger;
    cocos2d::CCSprite *m_TopTexture;
	cocos2d::CCSprite *m_BottomTexture;
    cocos2d::CCSprite *m_TopTexture2;
	cocos2d::CCSprite *m_BottomTexture2;
    cocos2d::CCSprite *m_TopTexture3;
	cocos2d::CCSprite *m_BottomTexture3;
    cocos2d::CCSprite *m_BottomTexture4;
    cocos2d::CCNode *m_BikeLoopVFX;
    b2Vec2 m_StartPos;
    Spline *m_Spline;
    float backupT;
    float t;
    b2Vec2 lastPos;
    float m_DeltaStep;
    float m_AccelStep;
    float m_AngleInterp;
    float m_EntryForward;
    float m_LaunchTime;
};
#endif