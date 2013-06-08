//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __SPACE_ORB_H__
#define __SPACE_ORB_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class SpaceOrb : public TrackObject
{
public:
	SpaceOrb(b2World *world, cocos2d::CCNode *ccLayer, cocos2d::CCNode* frontLayer, b2Vec2 *startPos);
	virtual ~SpaceOrb();
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
    cocos2d::CCSprite *m_Electricity;
    cocos2d::CCSprite *m_LeftOrb;
    cocos2d::CCSprite *m_RightOrb;
    cocos2d::CCSprite *m_LeftOrbGlow;
    cocos2d::CCSprite *m_RightOrbGlow;
    int m_waitCounter;
    float m_LastJump;
};
#endif