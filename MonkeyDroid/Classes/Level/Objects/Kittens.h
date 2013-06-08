//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __KITTENS_H__
#define __KITTENS_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Kittens : public TrackObject
{
public:
	Kittens(b2World *world, cocos2d::CCNode *ccLayer, cocos2d::CCNode* frontLayer, b2Vec2 *startPos, int type=0);
	virtual ~Kittens();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
    enum Type
	{
        KITTENS=0,
        COWS=1,
        CHICKENS=2,
        MAX
    };
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_frontLayer;
	b2Body *m_MainCollision;
    b2Vec2 m_StartPos;
	TextureObject *m_Texture;
	bool m_Exploded;
    int m_Type;
    cocos2d::CCSprite *m_censorBar;
    float m_LastJump;
};

#endif