//
//  DummyRider.h
//  CTM
//
//  Created by Ryan McBride on 6/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __DUMMYRIDER_H__
#define __DUMMYRIDER_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "../Objects/TextureObject.h"
#include "Monkey.h"
#include "AnimationSet.h"
#include "Fire.h"

class Monkey;

class DummyRider
{
public:
	DummyRider(b2World *world,cocos2d::CCLayer* layer);
	~DummyRider();
	void Step();
	bool SetTrick(int index);
	void Crash();
	b2Vec2 GetCameraFocus();
    void HandlePauseChange(bool pause);
protected:
	b2World *m_World;
    cocos2d::CCLayer *m_Layer;
	int m_Index;
	Monkey *m_Monkey;
	bool m_IsCrashed;

	//Animation Stuff
	AnimationSet *m_AnimSet;
    BikeFire *m_BikeFire;
    WheelFire *m_WheelFire[2];
    ExhaustFX *m_ExhaustFX;
};
#endif