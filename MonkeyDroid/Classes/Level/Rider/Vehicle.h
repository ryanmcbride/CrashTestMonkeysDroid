/*
 *  Vehicle.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __VEHICLE_H__
#define __VEHICLE_H__
#include "Box2d.h"
#include "Biped.h"

#define TEST_SCALE (1.0f)


class Vehicle
{
public:
	Vehicle();
	virtual ~Vehicle();
	virtual void Step(int loop=1)=0;
    virtual void Crash()=0;
    virtual void AttachBiped(Biped *pBiped)=0;
	virtual void AirSpin(float val)=0;
    virtual void GasAndBrake(float val, bool preStart=false)=0;
	virtual b2Body *GetMainBody()=0;
	virtual void SetRiderMass(float val)=0;
	virtual void BeginContact(b2Contact* contact){}
	virtual void EndContact(b2Contact* contact){}
	virtual bool isInAir()=0;
	virtual bool getRiderTest(){return false;}
    virtual void resetFlipCount()=0;
};
#endif