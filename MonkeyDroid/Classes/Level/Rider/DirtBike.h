//
//  DirtBike.h
//  CTM
//
//  Created by Ryan McBride on 3/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef DIRTBIKE_H
#define DIRTBIKE_H
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Box2D.h"
#include "Vehicle.h"
#include "../Objects/TextureObject.h"
//#import "Fire.h"

USING_NS_CC;

class DirtBike : public Vehicle
{
public:
	DirtBike(b2World *world, CCLayer *ccLayer, b2Vec2 &startPos);
	virtual ~DirtBike();
	void Step(int loop=1);
    void Crash();
    void AttachBiped(Biped *pBiped);
	void AirSpin(float val);
    void GasAndBrake(float val, bool preStart=false);
	b2Body *GetMainBody();
	void SetRiderMass(float val);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	bool isInAir(){return m_bInAir;}
	bool isUpsideDown(){return m_bIsUpsideDown;}
	bool getRiderTest()
	{
		bool retVal = m_bHitRiderTest;
		m_bHitRiderTest = false;
		return retVal;
	}
    void resetFlipCount(){m_flipcount=0;}
    b2Vec2 m_FrontWheelColCenter;
    b2Vec2 m_BackWheelColCenter;
    b2Body *GetWheelFront(){return wheel2;}
    b2Body *GetWheelBack(){return wheel1;}
    CCSprite *GetWheelFrontSprite();
    CCSprite *GetWheelBackSprite();
    static b2Body *s_Cart;
    static b2Body *s_Wheel1;
    static b2Body *s_Wheel2;
protected:
	float change;
	CCLayer *m_CCLayer;
	b2World *m_world;
    b2Body *cart;
    b2RevoluteJoint *motor1;
    b2RevoluteJoint *motor2;
    b2PrismaticJoint *spring1;
    b2PrismaticJoint *spring2;
    b2Body *wheel1;
    b2Body *wheel2;
    b2WeldJoint *m_LHJoint;
    b2WeldJoint *m_RHJoint;
    b2WeldJoint *m_LLJoint;
    b2WeldJoint *m_RLJoint;
    b2WeldJoint *m_ButtJoint;
	    
	b2Vec2 m_BackWheelStart;
	b2Vec2 m_BackWheelOffset;
	b2Vec2 m_FrontWheelStart;
	b2Vec2 m_FrontWheelOffset;
	bool	m_bHitBackWheel;
	bool	m_bHitFrontWheel;
	b2Fixture *m_BackWheel;
	b2Fixture *m_FrontWheel;
	bool m_bHitRiderTest;
	b2Fixture *m_RiderTest;
	float m_TotalMass;
	
	float m_AirSpin;
	bool m_bInAir;
	bool m_bIsUpsideDown;
	int m_flipcount;
	b2RayCastCallback *m_GroundRayCastTest;
	bool m_Crashed;
	
	TextureObject *m_Texture[6];
	b2Vec2 m_Forward;
	
    bool m_bDustOnLanding;
    
    int m_iRiderHitRefCount;
    float m_fhitCountDelay;
    
    bool m_bTestTrickDone;
    float m_LastSprigTrans1;
};


#endif