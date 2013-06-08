//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __SWING_OBJECT_H__
#define __SWING_OBJECT_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Swing : public TrackObject
{
public:
	Swing(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, int type=0);
	virtual ~Swing();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
    enum Type
	{
        FISH=0,
        MASK=1,
        CRATE=2,
        TIRE=3,
        PLANET=4,
        ORB=5,
        MAX=6
    };
protected:
    float m_waitTime;
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	bool m_Exploded;
    cocos2d::CCNode *m_Pivot;
    cocos2d::CCSprite *m_Swing;
    cocos2d::CCSprite *m_PivotImage;
    cocos2d::CCNode *m_EndSwing;
    cocos2d::CCPoint m_EndPosition;
    float m_RotVel;
    float m_RotAcc;
    float m_Rot;
    int m_Type;
};
#endif