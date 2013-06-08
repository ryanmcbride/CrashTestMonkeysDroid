/*
 *  Ramp.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PLATFORM_OBJECT_H__
#define __PLATFORM_OBJECT_H__
#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Platform : public TrackObject
{
public:
	enum Type
	{
		LONG=0,
		SHORT,
		BLUE_CAR_BACK,
		ORANGE_CAR_BACK,
		HOT_DOG_BACK,
		MAIL_TRUCK_BACK,
		POLICE_BACK,
		TAXI_BACK,
		SCHOOLBUS_LEFT,
		SEMITRUCK_LEFT,
		BLUE_CAR_LEFT,
		ORANGE_CAR_LEFT,
		HOT_DOG_LEFT,
		MAIL_TRUCK_LEFT,
		POLICE_LEFT,
		TAXI_LEFT,
		BLUE_CAR_FRONT,
		ORANGE_CAR_FRONT,
		HOT_DOG_FRONT,
		MAIL_TRUCK_FRONT,
		POLICE_FRONT,
		TAXI_FRONT,
		SCHOOLBUS_RIGHT,
		SEMITRUCK_RIGHT,
		BLUE_CAR_RIGHT,
		ORANGE_CAR_RIGHT,
		HOT_DOG_RIGHT,
		MAIL_TRUCK_RIGHT,
		POLICE_RIGHT,
		TAXI_RIGHT,
		HIGH_WALL,
		HIGH_WALL2,
		HIGH_WALL3,
        BACK_WALL_RAMP,
		MAX_TYPES
	};
	Platform(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, Type intype, int sort=0);
	Platform(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, Type intype, cocos2d::CCNode *backLayer, int sort=0);
	virtual ~Platform();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	b2Body *GetBody(){return m_MainCollision;}
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_backLayer;
    cocos2d::CCSprite *post;
	b2Body *m_MainCollision;
	TextureObject *m_Texture;
	b2Vec2 m_StartPos;
	float m_Scale;
	Type m_Type;
    int m_sort;
    float yscale;
};
#endif