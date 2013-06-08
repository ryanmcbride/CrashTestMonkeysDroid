//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __BARRIER_H__
#define __BARRIER_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Barrier : public TrackObject
{
public:
	Barrier(b2World *world, cocos2d::CCNode *ccLayer, cocos2d::CCNode* frontLayer, b2Vec2 *startPos, bool unbreakable = false);
	virtual ~Barrier();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_frontLayer;
	b2Body *m_MainCollision;
    b2Vec2 m_StartPos;
	TextureObject *m_Texture;
	bool m_Exploded;
    int m_Type;
    cocos2d::CCSprite *m_Lights;
    float m_LastFlicker;
    float m_unbreakable;
    float m_waitTime;
};
#endif