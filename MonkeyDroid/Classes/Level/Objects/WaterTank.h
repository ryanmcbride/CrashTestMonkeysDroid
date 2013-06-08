//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __WATER_TANK_H__
#define __WATER_TANK_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class WaterTank : public TrackObject
{
public:
	WaterTank(b2World *world, cocos2d::CCNode *ccLayer, cocos2d::CCNode *frontLayer, b2Vec2 *startPos, int type=0);
	virtual ~WaterTank();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
    enum Type
	{
        SHARK=0,
        ACID=1,
        SPACE=2,
        MAX
    };
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_frontLayer;
	b2Body *m_LeftCollision;
    b2Body *m_RightCollision;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	TextureObject *m_Texture;
    cocos2d::CCSprite *m_Shark;
    cocos2d::CCSprite *m_Front;
    cocos2d::CCSprite *m_censorBar;
	bool m_Exploded;
    int m_Type;
    float censorX;
    //ARCH_OPTIMAL_PARTICLE_SYSTEM *emitter;
};
#endif