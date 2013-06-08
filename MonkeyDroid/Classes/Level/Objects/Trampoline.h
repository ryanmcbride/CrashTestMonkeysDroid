//
//  Trampoline.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TRAMPOLINE_H__
#define __TRAMPOLINE_H__
#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Trampoline : public TrackObject
{
public:
	Trampoline(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, float scale, int forceVersion);
	virtual ~Trampoline();
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
    int m_BouncedCount;
    float m_BounceDelay;
    void DoBounceCurl();
    int m_forceVersion;
    int m_nodeNumbers[3];
};
#endif