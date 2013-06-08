/*
 *  Monkey.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MONKEY_H__
#define __MONKEY_H__

#include "cocos2d.h"
#include "Biped.h"
#include "../Objects/TextureObject.h"

class TextureObject;

class Monkey : public Biped
{
public:
	Monkey(b2World*, cocos2d::CCLayer* layer, const b2Vec2& position, b2Transform& xform, b2Vec2 *linearVel=NULL,float *angularVel=NULL);
	~Monkey();
	void SetVelocity(b2Vec2 velocity);
    const b2Vec2 &getCenter(){return Pelvis->GetPosition();}
    static Monkey* getMonkey();
    static float s_RandomXVel;
    static float s_RandomYVel;
protected:
    static Monkey* s_Monkey;
	TextureObject *m_Texture[17];
};
#endif