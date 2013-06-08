//
//  Trampoline.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __ROTATIONG_AIR_BOOST_H__
#define __ROTATIONG_AIR_BOOST_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class RotatingAirBoost : public TrackObject
{
public:
	RotatingAirBoost(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, float minrotation, float maxrotation, float rotspeed);
	virtual ~RotatingAirBoost();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	TextureObject *m_Texture;
    float m_LauchDelay;
    float m_MinRot;
    float m_MaxRot;
    float m_RotationSpeed;
    float m_Rotation;
};
#endif