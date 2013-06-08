//
//  Pickup.h
//  CTM
//
//  Created by Ryan McBride on 1/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef __PICKUP_OBJECT_H__
#define __PICKUP_OBJECT_H__

#include "cocos2d.h"
#include "Box2d.h"
#include "TrackObject.h"

class CCRotateRandom : public cocos2d::CCActionInterval
{
public:
	float angle;
	float startAngle;

    static CCRotateRandom* create(float duration,float angle);
};


class Pickup : public TrackObject
{
public:
    enum Type
	{
		PEANUT=0,
		FIRE,
		RED_SMOKE,
		WHITE_SMOKE,
		BLUE_SMOKE,
		FIRE_WORKS,
		TRICK1,
		TRICK2,
		TRICK3,
        TIME,
		MAX_TYPES
	};
	Pickup(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, float scale = 1.0f);
	Pickup(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, Type itype);
	virtual ~Pickup();
	virtual void CreateSelf();
	virtual void DestroySelf();
	virtual void Update(float xpos,float ypos);
    virtual bool InRange(float xpos);
	virtual bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
    void DoPickup();
    static void InitLevelPickups();
    static void DestroyLevelPickups();
protected:
    void DoPickupVFX();
    void DoPickupVFXBig();
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	bool m_bPickedUp;
    Type m_Type;
    float m_vfxTime;
    float m_popInStagger;
    cocos2d::CCSprite *elec;
    cocos2d::CCSprite *m_Popsprite[5];
    cocos2d::CCPoint m_PopspritePoint[5];
    static cocos2d::CCSprite *m_SpriteCache[50];
    static cocos2d::CCSprite *m_BigSpriteCache[50];
    static int m_SpriteCacheCount;
    static int m_BigSpriteCacheCount;
};
#endif