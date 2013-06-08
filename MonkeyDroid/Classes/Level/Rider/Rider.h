/*
 *  Rider.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RIDER_H__
#define __RIDER_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "Vehicle.h"
#include "DummyRider.h"
#include "BikeAudio.h"
#include "../ScoreManager.h"


class DummyRider;

class Rider : public b2ContactListener
{
public:
	enum VEHICLE_TYPE 
	{
		MOTORCYCLE = 0,
		SEGWAY = 1,
		SHOPPING_CART = 2
	};
	Rider(b2World *world, cocos2d::CCNode *ccLayer);
	virtual ~Rider();
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	
	void GetCameraPosition(b2Vec2 &outVec);
    void Step(int loops = 1);
    void Crash();
	bool Trick(int trickNum);
	void AirSpin(float val);
    void GasAndBrake(float val, bool preStart=false);
    void HandlePauseChange(bool pause);
	
	static b2Vec2 g_LauchDir;
	static bool g_DoLaunch;
	static bool g_inLoop;
	static b2Body* g_MainBody;
	static b2Vec2 g_startPos;
	static bool g_isInAir;
	static bool g_isFinished;
	static bool g_isCrashed;
	static float g_OnFire;
	static float g_ForceCrash;
    static bool g_WaterCrash;
	static int g_Score;
	static int g_Pickups;
	static int g_TrickState;
    static void FixWheelPos();
    static ScoreManager* g_ScoreManager;
    static BikeAudio *g_BikeAudio;
    static Vehicle *s_Vehicle;
    static bool s_bWheelsTouch;
protected:
    
    cocos2d::CCNode *m_CCLayer;
	b2World *m_world;
	Vehicle *m_Vehicle;
	DummyRider *m_DummyRider;
    bool m_doCrash;
	b2Vec2 m_LastCamera;
	int m_TrickState;
	float m_TrickTimer;
	float m_CrashTimer;
	float cameraInterpolateCount;
    float m_bTrickedAlready;
};
#endif