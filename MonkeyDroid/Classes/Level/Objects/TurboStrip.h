//
//  TurboStrip.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TURBO_STRIP_H__
#define __TURBO_STRIP_H__

#include "cocos2d.h"
#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class TurboStrip : public TrackObject
{
public:
	TurboStrip(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, float scale = 1.0f, bool bReverse = false);
	virtual ~TurboStrip();
	virtual void CreateSelf();
	virtual void DestroySelf();
	virtual void Update(float xpos,float ypos);
	virtual bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
    cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
    TextureObject *tex;
	b2Vec2 m_StartPos;
    bool m_bReverse;
    float m_LauchDelay;
};

#endif //__TURBO_STRIP_H__