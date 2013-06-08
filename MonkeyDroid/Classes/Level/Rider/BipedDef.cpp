#include "BipedDef.h"

int16 BipedDef::count = 0;

const float32 k_scale = 2.5f;
BipedDef::BipedDef()
{
    SetDynamic();
    SetFriction(0.8f);
	SetMotorTorque(2.0f);
	SetMotorSpeed(0.0f);
	SetDensity(1.0f);
	SetRestitution(0.0f);
	SetLinearDamping(0.0f);
	SetAngularDamping(0.005f);
	SetGroupIndex(-1);
	EnableMotor();
	EnableLimit();
	
	DefaultVertices();
	DefaultPositions();
	DefaultJoints();

	LFootPolyfix.friction = RFootPolyfix.friction = 0.85f;

    
    LFootPolyfix.shape = &LFootPoly;
    RFootPolyfix.shape = &RFootPoly;
    LCalfPolyfix.shape = &LCalfPoly;
    RCalfPolyfix.shape = &RCalfPoly;
    LThighPolyfix.shape = &LThighPoly;
    RThighPolyfix.shape = &RThighPoly;
    PelvisPolyfix.shape = &PelvisPoly;
    StomachPolyfix.shape = &StomachPoly;
    ChestPolyfix.shape = &ChestPoly;
    NeckPolyfix.shape = &NeckPoly;
    LUpperArmPolyfix.shape = &LUpperArmPoly;
    RUpperArmPolyfix.shape = &RUpperArmPoly;
    LForearmPolyfix.shape = &LForearmPoly;
    RForearmPolyfix.shape = &RForearmPoly;
    LHandPolyfix.shape = &LHandPoly;
    RHandPolyfix.shape = &RHandPoly;
    HeadCircfix.shape = &HeadCirc;
}
void BipedDef::SetDynamic()
{
    LFootDef.type			= b2_dynamicBody;
    RFootDef.type			= b2_dynamicBody;
    LCalfDef.type			= b2_dynamicBody;
    RCalfDef.type			= b2_dynamicBody;
    LThighDef.type		    = b2_dynamicBody;
    RThighDef.type		    = b2_dynamicBody;
    PelvisDef.type		    = b2_dynamicBody;
    StomachDef.type		    = b2_dynamicBody;
    ChestDef.type			= b2_dynamicBody;
    NeckDef.type			= b2_dynamicBody;
    HeadDef.type			= b2_dynamicBody;
    LUpperArmDef.type		= b2_dynamicBody;
    RUpperArmDef.type		= b2_dynamicBody;
    LForearmDef.type		= b2_dynamicBody;
    RForearmDef.type		= b2_dynamicBody;
    LHandDef.type			= b2_dynamicBody;
    RHandDef.type			= b2_dynamicBody;
}
void BipedDef::IsFast(bool b)
{
	B2_NOT_USED(b);
	/*
	LFootDef.isFast			= b;
	RFootDef.isFast			= b;
	LCalfDef.isFast			= b;
	RCalfDef.isFast			= b;
	LThighDef.isFast		= b;
	RThighDef.isFast		= b;
	PelvisDef.isFast		= b;
	StomachDef.isFast		= b;
	ChestDef.isFast			= b;
	NeckDef.isFast			= b;
	HeadDef.isFast			= b;
	LUpperArmDef.isFast		= b;
	RUpperArmDef.isFast		= b;
	LForearmDef.isFast		= b;
	RForearmDef.isFast		= b;
	LHandDef.isFast			= b;
	RHandDef.isFast			= b;
	*/
}

void BipedDef::SetGroupIndex(int16 i)
{
/*	LFootPolyfix.filter.groupIndex		= i;
	RFootPolyfix.filter.groupIndex		= i;
	LCalfPolyfix.filter.groupIndex		= i;
	RCalfPolyfix.filter.groupIndex		= i;
	LThighPolyfix.filter.groupIndex		= i;
	RThighPolyfix.filter.groupIndex		= i;
	PelvisPolyfix.filter.groupIndex		= i;
	StomachPolyfix.filter.groupIndex		= i;
	ChestPolyfix.filter.groupIndex		= i;
	NeckPolyfix.filter.groupIndex			= i;
	HeadCircfix.filter.groupIndex			= i;
	LUpperArmPolyfix.filter.groupIndex	= i;
	RUpperArmPolyfix.filter.groupIndex	= i;
	LForearmPolyfix.filter.groupIndex		= i;
	RForearmPolyfix.filter.groupIndex		= i;
	LHandPolyfix.filter.groupIndex		= i;
	RHandPolyfix.filter.groupIndex		= i;
*/
    LFootPolyfix.filter.categoryBits		= 0x0004;
    RFootPolyfix.filter.categoryBits		= 0x0004;
    LCalfPolyfix.filter.categoryBits		= 0x0004;
    RCalfPolyfix.filter.categoryBits		= 0x0004;
    LThighPolyfix.filter.categoryBits		= 0x0004;
    RThighPolyfix.filter.categoryBits		= 0x0004;
    PelvisPolyfix.filter.categoryBits		= 0x0004;
    StomachPolyfix.filter.categoryBits		= 0x0004;
    ChestPolyfix.filter.categoryBits		= 0x0004;
    NeckPolyfix.filter.categoryBits			= 0x0004;
    HeadCircfix.filter.categoryBits			= 0x0004;
    LUpperArmPolyfix.filter.categoryBits	= 0x0004;
    RUpperArmPolyfix.filter.categoryBits	= 0x0004;
    LForearmPolyfix.filter.categoryBits		= 0x0004;
    RForearmPolyfix.filter.categoryBits		= 0x0004;
    LHandPolyfix.filter.categoryBits		= 0x0004;
    RHandPolyfix.filter.categoryBits		= 0x0004;
    
    LFootPolyfix.filter.maskBits		= 0x0011;
    RFootPolyfix.filter.maskBits		= 0x0011;
    LCalfPolyfix.filter.maskBits		= 0x0011;
    RCalfPolyfix.filter.maskBits		= 0x0011;
    LThighPolyfix.filter.maskBits		= 0x0011;
    RThighPolyfix.filter.maskBits		= 0x0011;
    PelvisPolyfix.filter.maskBits		= 0x0011;
    StomachPolyfix.filter.maskBits		= 0x0011;
    ChestPolyfix.filter.maskBits		= 0x0011;
    NeckPolyfix.filter.maskBits			= 0x0011;
    HeadCircfix.filter.maskBits			= 0x0011;
    LUpperArmPolyfix.filter.maskBits	= 0x0011;
    RUpperArmPolyfix.filter.maskBits	= 0x0011;
    LForearmPolyfix.filter.maskBits		= 0x0011;
    RForearmPolyfix.filter.maskBits		= 0x0011;
    LHandPolyfix.filter.maskBits		= 0x0011;
    RHandPolyfix.filter.maskBits		= 0x0011;
}

void BipedDef::SetLinearDamping(float f)
{
	LFootDef.linearDamping		= f;
	RFootDef.linearDamping		= f;
	LCalfDef.linearDamping		= f;
	RCalfDef.linearDamping		= f;
	LThighDef.linearDamping		= f;
	RThighDef.linearDamping		= f;
	PelvisDef.linearDamping		= f;
	StomachDef.linearDamping	= f;
	ChestDef.linearDamping		= f;
	NeckDef.linearDamping		= f;
	HeadDef.linearDamping		= f;
	LUpperArmDef.linearDamping	= f;
	RUpperArmDef.linearDamping	= f;
	LForearmDef.linearDamping	= f;
	RForearmDef.linearDamping	= f;
	LHandDef.linearDamping		= f;
	RHandDef.linearDamping		= f;
}

void BipedDef::SetAngularDamping(float f)
{
	LFootDef.angularDamping		= f;
	RFootDef.angularDamping		= f;
	LCalfDef.angularDamping		= f;
	RCalfDef.angularDamping		= f;
	LThighDef.angularDamping	= f;
	RThighDef.angularDamping	= f;
	PelvisDef.angularDamping	= f;
	StomachDef.angularDamping	= f;
	ChestDef.angularDamping		= f;
	NeckDef.angularDamping		= f;
	HeadDef.angularDamping		= f;
	LUpperArmDef.angularDamping	= f;
	RUpperArmDef.angularDamping	= f;
	LForearmDef.angularDamping	= f;
	RForearmDef.angularDamping	= f;
	LHandDef.angularDamping		= f;
	RHandDef.angularDamping		= f;
}

void BipedDef::SetMotorTorque(float f)
{
	LAnkleDef.maxMotorTorque		= f;
	RAnkleDef.maxMotorTorque		= f;
	LKneeDef.maxMotorTorque		= f;
	RKneeDef.maxMotorTorque		= f;
	LHipDef.maxMotorTorque			= f;
	RHipDef.maxMotorTorque			= f;
	LowerAbsDef.maxMotorTorque		= f;
	UpperAbsDef.maxMotorTorque		= f;
	LowerNeckDef.maxMotorTorque	= f;
	UpperNeckDef.maxMotorTorque	= f;
	LShoulderDef.maxMotorTorque	= f;
	RShoulderDef.maxMotorTorque	= f;
	LElbowDef.maxMotorTorque		= f;
	RElbowDef.maxMotorTorque		= f;
	LWristDef.maxMotorTorque		= f;
	RWristDef.maxMotorTorque		= f;
}

void BipedDef::SetMotorSpeed(float f)
{
	LAnkleDef.motorSpeed		= f;
	RAnkleDef.motorSpeed		= f;
	LKneeDef.motorSpeed			= f;
	RKneeDef.motorSpeed			= f;
	LHipDef.motorSpeed			= f;
	RHipDef.motorSpeed			= f;
	LowerAbsDef.motorSpeed		= f;
	UpperAbsDef.motorSpeed		= f;
	LowerNeckDef.motorSpeed		= f;
	UpperNeckDef.motorSpeed		= f;
	LShoulderDef.motorSpeed		= f;
	RShoulderDef.motorSpeed		= f;
	LElbowDef.motorSpeed		= f;
	RElbowDef.motorSpeed		= f;
	LWristDef.motorSpeed		= f;
	RWristDef.motorSpeed		= f;
}

void BipedDef::SetDensity(float f)
{
	LFootPolyfix.density			= f;
	RFootPolyfix.density			= f;
	LCalfPolyfix.density			= f;
	RCalfPolyfix.density			= f;
	LThighPolyfix.density			= f;
	RThighPolyfix.density			= f;
	PelvisPolyfix.density			= f;
	StomachPolyfix.density			= f;
	ChestPolyfix.density			= f;
	NeckPolyfix.density			= f;
	HeadCircfix.density			= f;
	LUpperArmPolyfix.density		= f;
	RUpperArmPolyfix.density		= f;
	LForearmPolyfix.density		= f;
	RForearmPolyfix.density		= f;
	LHandPolyfix.density			= f;
	RHandPolyfix.density			= f;
}

void BipedDef::SetFriction(float f)
{
    LFootPolyfix.friction			= f/3.0f;
    RFootPolyfix.friction			= f/3.0f;
    LCalfPolyfix.friction			= f;
    RCalfPolyfix.friction			= f;
    LThighPolyfix.friction			= f;
    RThighPolyfix.friction			= f;
    PelvisPolyfix.friction			= f;
    StomachPolyfix.friction			= f;
    ChestPolyfix.friction			= f;
    NeckPolyfix.friction			= f;
    HeadCircfix.friction			= f;
    LUpperArmPolyfix.friction		= f;
    RUpperArmPolyfix.friction		= f;
    LForearmPolyfix.friction		= f;
    RForearmPolyfix.friction		= f;
    LHandPolyfix.friction			= f;
    RHandPolyfix.friction			= f;
}

void BipedDef::SetRestitution(float f)
{
	LFootPolyfix.restitution		= f;
	RFootPolyfix.restitution		= f;
	LCalfPolyfix.restitution		= f;
	RCalfPolyfix.restitution		= f;
	LThighPolyfix.restitution		= f;
	RThighPolyfix.restitution		= f;
	PelvisPolyfix.restitution		= f;
	StomachPolyfix.restitution		= f;
	ChestPolyfix.restitution		= f;
	NeckPolyfix.restitution		= f;
	HeadCircfix.restitution		= f;
	LUpperArmPolyfix.restitution	= f;
	RUpperArmPolyfix.restitution	= f;
	LForearmPolyfix.restitution	= f;
	RForearmPolyfix.restitution	= f;
	LHandPolyfix.restitution		= f;
	RHandPolyfix.restitution		= f;
}

void BipedDef::EnableLimit()
{
	SetLimit(true);
}

void BipedDef::DisableLimit()
{
	SetLimit(false);
}

void BipedDef::SetLimit(bool b)
{
	LAnkleDef.enableLimit		= b;
	RAnkleDef.enableLimit		= b;
	LKneeDef.enableLimit		= b;
	RKneeDef.enableLimit		= b;
	LHipDef.enableLimit			= b;
	RHipDef.enableLimit			= b;
	LowerAbsDef.enableLimit		= b;
	UpperAbsDef.enableLimit		= b;
	LowerNeckDef.enableLimit	= b;
	UpperNeckDef.enableLimit	= b;
	LShoulderDef.enableLimit	= b;
	RShoulderDef.enableLimit	= b;
	LElbowDef.enableLimit		= b;
	RElbowDef.enableLimit		= b;
	LWristDef.enableLimit		= b;
	RWristDef.enableLimit		= b;
}

void BipedDef::EnableMotor()
{
	SetMotor(true);
}

void BipedDef::DisableMotor()
{
	SetMotor(false);
}

void BipedDef::SetMotor(bool b)
{
	LAnkleDef.enableMotor		= b;
	RAnkleDef.enableMotor		= b;
	LKneeDef.enableMotor		= b;
	RKneeDef.enableMotor		= b;
	LHipDef.enableMotor			= b;
	RHipDef.enableMotor			= b;
	LowerAbsDef.enableMotor		= b;
	UpperAbsDef.enableMotor		= b;
	LowerNeckDef.enableMotor	= b;
	UpperNeckDef.enableMotor	= b;
	LShoulderDef.enableMotor	= b;
	RShoulderDef.enableMotor	= b;
	LElbowDef.enableMotor		= b;
	RElbowDef.enableMotor		= b;
	LWristDef.enableMotor		= b;
	RWristDef.enableMotor		= b;
}

BipedDef::~BipedDef(void)
{
}

void BipedDef::DefaultVertices()
{
	{	// feet
		b2Vec2 verts[4] = 
        {
            b2Vec2(-8.0f/16.0f,0.0f/16.0f),
            b2Vec2(-8.0f/16.0f,-5.0f/16.0f),
            b2Vec2(9.0f/16.0f,-5.0f/16.0f),
            b2Vec2(9.0f/16.0f,0.0f/16.0f),
        };
        LFootPoly.Set(verts,4);
        RFootPoly.Set(verts,4);
	}
	{	// calves
		b2Vec2 verts[4] = 
        {
            b2Vec2(-2.0f/16.0f,8.0f/16.0f),
			b2Vec2(-1.0f/16.0f,-8.0f/16.0f),
            b2Vec2(2.0f/16.0f,-9.0f/16.0f),
            b2Vec2(3.0f/16.0f,8.0f/16.0f),
		};
        LCalfPoly.Set(verts,4);
        RCalfPoly.Set(verts,4);
	}
	{	// thighs
		b2Vec2 verts[4] = 
        {
            b2Vec2(3.0f/16.0f,8.0f/16.0f),
            b2Vec2(-4.0f/16.0f,8.0f/16.0f),
            b2Vec2(-4.0f/16.0f,-6.0f/16.0f),
            b2Vec2(3.0f/16.0f,-6.0f/16.0f),
        };
        LThighPoly.Set(verts,4);
        RThighPoly.Set(verts,4);
	}
	{	// pelvis
		b2Vec2 verts[4] = 
        {
            b2Vec2(5.0f/16.0f,6.0f/16.0f),
            b2Vec2(-7.0f/16.0f,5.0f/16.0f),
            b2Vec2(-1.0f/16.0f,-4.0f/16.0f),
            b2Vec2(6.0f/16.0f,-4.0f/16.0f),
        };
        PelvisPoly.Set(verts,4);
	}
	{	// stomach
		b2Vec2 verts[4] = 
        {
            b2Vec2(6.0f/16.0f,3.0f/16.0f),
            b2Vec2(-4.0f/16.0f,9.0f/16.0f),
            b2Vec2(-6.0f/16.0f,-4.0f/16.0f),
            b2Vec2(4.0f/16.0f,-6.0f/16.0f),
        };
        StomachPoly.Set(verts,4);
	}
	{	// chest
		b2Vec2 verts[4] = 
        {
            0.8f * b2Vec2(2.0f/16.0f,11.0f/16.0f),
            0.8f * b2Vec2(-8.0f/16.0f,-4.0f/16.0f),
            0.8f * b2Vec2(3.0f/16.0f,-13.0f/16.0f),
            0.8f * b2Vec2(10.0f/16.0f,0.0f/16.0f),
        };
        ChestPoly.Set(verts,4);
	}
	{	// head
		HeadCirc.m_radius = 0.6f;
	}
	{	// neck
		b2Vec2 verts[4] = 
        {
            b2Vec2(-0.25f,-0.25f),
            b2Vec2(0.25f,-0.25f),
            b2Vec2(0.5f,0.25f),
            b2Vec2(0.0f,0.25f),
        };
        NeckPoly.Set(verts,4);
	}
	{	// upper arms
		b2Vec2 verts[4] = 
        {
            0.8f*b2Vec2(5.0f/16.0f,11.0f/16.0f),
            0.8f*b2Vec2(-4.0f/16.0f,12.0f/16.0f),
            0.8f*b2Vec2(-2.0f/16.0f,-11.0f/16.0f),
            0.8f*b2Vec2(4.0f/16.0f,-10.0f/16.0f),
        };
        LUpperArmPoly.Set(verts,4);
        RUpperArmPoly.Set(verts,4);
	}
	{	// forearms
		b2Vec2 verts[4] = 
        {
            0.8f*b2Vec2(2.0f/16.0f,12.0f/16.0f),
            0.8f*b2Vec2(-4.0f/16.0f,8.0f/16.0f),
            0.8f*b2Vec2(-1.0f/16.0f,-12.0f/16.0f),
            0.8f*b2Vec2(2.0f/16.0f,-12.0f/16.0f),
        };
        LForearmPoly.Set(verts,4);
        RForearmPoly.Set(verts,4);
	}
	{	// hands
		b2Vec2 verts[4] = 
        {
            0.8f*b2Vec2(1.0f/16.0f,6.0f/16.0f),
            0.8f*b2Vec2(-4.0f/16.0f,0.0f/16.0f),
            0.8f*b2Vec2(-4.0f/16.0f,-6.0f/16.0f),
            0.8f*b2Vec2(5.0f/16.0f,-6.0f/16.0f),
        };
        LHandPoly.Set(verts,4);
        RHandPoly.Set(verts,4);
	}
}

void BipedDef::DefaultJoints()
{
	//b.LAnkleDef.body1		= LFoot;
	//b.LAnkleDef.body2		= LCalf;
	//b.RAnkleDef.body1		= RFoot;
	//b.RAnkleDef.body2		= RCalf;
	{	// ankles
		b2Vec2 anchor = b2Vec2(-1.0f/16.0f,-39.0f/16.0f);
		LAnkleDef.localAnchorA		= RAnkleDef.localAnchorA	= anchor - LFootDef.position;
		LAnkleDef.localAnchorB		= RAnkleDef.localAnchorB	= anchor - LCalfDef.position;
		LAnkleDef.referenceAngle	= RAnkleDef.referenceAngle	= 0.0f;
		LAnkleDef.lowerAngle		= RAnkleDef.lowerAngle		= -0.523598776f;
		LAnkleDef.upperAngle		= RAnkleDef.upperAngle		= 0.523598776f;
	}

	//b.LKneeDef.body1		= LCalf;
	//b.LKneeDef.body2		= LThigh;
	//b.RKneeDef.body1		= RCalf;
	//b.RKneeDef.body2		= RThigh;
	{	// knees
		b2Vec2 anchor = b2Vec2(1.0f/16.0f,-22.0f/16.0f);
		LKneeDef.localAnchorA	= RKneeDef.localAnchorA		= anchor - LCalfDef.position;
		LKneeDef.localAnchorB	= RKneeDef.localAnchorB		= anchor - LThighDef.position;
		LKneeDef.referenceAngle	= RKneeDef.referenceAngle	= 0.0f;
		LKneeDef.lowerAngle		= RKneeDef.lowerAngle		= 0;
		LKneeDef.upperAngle		= RKneeDef.upperAngle		= 2.61799388f;
	}

	//b.LHipDef.body1			= LThigh;
	//b.LHipDef.body2			= Pelvis;
	//b.RHipDef.body1			= RThigh;
	//b.RHipDef.body2			= Pelvis;
	{	// hips
		b2Vec2 anchor = b2Vec2(-1.0f/16.0f,-5.0f/16.0f);
		LHipDef.localAnchorA	= RHipDef.localAnchorA		= anchor - LThighDef.position;
		LHipDef.localAnchorB	= RHipDef.localAnchorB		= anchor - PelvisDef.position;
		LHipDef.referenceAngle	= RHipDef.referenceAngle	= 0.0f;
		LHipDef.lowerAngle		= RHipDef.lowerAngle		= -2.26892803f;
		LHipDef.upperAngle		= RHipDef.upperAngle		= 0;
	}

	//b.LowerAbsDef.body1		= Pelvis;
	//b.LowerAbsDef.body2		= Stomach;
	{	// lower abs
		b2Vec2 anchor = b2Vec2(1.0f/16.0f,4.0f/16.0f);
		LowerAbsDef.localAnchorA	= anchor - PelvisDef.position;
		LowerAbsDef.localAnchorB	= anchor - StomachDef.position;
		LowerAbsDef.referenceAngle	= 0.0f;
		LowerAbsDef.lowerAngle		= -0.523598776f;
		LowerAbsDef.upperAngle		= 0.523598776f;
	}

	//b.UpperAbsDef.body1		= Stomach;
	//b.UpperAbsDef.body2		= Chest;
	{	// upper abs
		b2Vec2 anchor = b2Vec2(2.0f/16.0f,16.0f/16.0f);
		UpperAbsDef.localAnchorA	= anchor - StomachDef.position;
		UpperAbsDef.localAnchorB	= anchor - ChestDef.position;
		UpperAbsDef.referenceAngle	= 0.0f;
		UpperAbsDef.lowerAngle		= -0.523598776f;
		UpperAbsDef.upperAngle		= 0.174532925f;
	}

	//b.LowerNeckDef.body1	= Chest;
	//b.LowerNeckDef.body2	= Neck;
	{	// lower neck
		b2Vec2 anchor = b2Vec2(4.0f/16.0f,30.0f/16.0f);
		LowerNeckDef.localAnchorA	= anchor - ChestDef.position;
		LowerNeckDef.localAnchorB	= anchor - NeckDef.position;
		LowerNeckDef.referenceAngle	= 0.0f;
		LowerNeckDef.lowerAngle		= -0.174532925f;
		LowerNeckDef.upperAngle		= 0.174532925f;
	}

	//b.UpperNeckDef.body1	= Neck;
	//b.UpperNeckDef.body2	= Head;
	{	// upper neck
		b2Vec2 anchor = b2Vec2(6.0f/16.0f,34.0f/16.0f);
		UpperNeckDef.localAnchorA	= anchor - NeckDef.position;
		UpperNeckDef.localAnchorB	= anchor - HeadDef.position;
		UpperNeckDef.referenceAngle	= 0.0f;
		UpperNeckDef.lowerAngle		= -0.610865238f;
		UpperNeckDef.upperAngle		= 0.785398163f;
	}

	//b.LShoulderDef.body1	= Chest;
	//b.LShoulderDef.body2	= LUpperArm;
	//b.RShoulderDef.body1	= Chest;
	//b.RShoulderDef.body2	= RUpperArm;
	{	// shoulders
		b2Vec2 anchor = b2Vec2(-1.0f/16.0f,24.0f/16.0f);
		LShoulderDef.localAnchorA	= RShoulderDef.localAnchorA		= anchor - ChestDef.position;
		LShoulderDef.localAnchorB	= RShoulderDef.localAnchorB		= anchor - LUpperArmDef.position;
		LShoulderDef.referenceAngle	= RShoulderDef.referenceAngle	= 0.0f;
		LShoulderDef.lowerAngle		= RShoulderDef.lowerAngle		= -1.04719755f;
		LShoulderDef.upperAngle		= RShoulderDef.upperAngle		= 3.14159265f;
	}

	//b.LElbowDef.body1		= LForearm;
	//b.LElbowDef.body2		= LUpperArm;
	//b.RElbowDef.body1		= RForearm;
	//b.RElbowDef.body2		= RUpperArm;
	{	// elbows
		b2Vec2 anchor = b2Vec2(-1.0f/16.0f,9.0f/16.0f);
		LElbowDef.localAnchorA		= RElbowDef.localAnchorA	= anchor - LForearmDef.position;
		LElbowDef.localAnchorB		= RElbowDef.localAnchorB	= anchor - LUpperArmDef.position;
		LElbowDef.referenceAngle	= RElbowDef.referenceAngle	= 0.0f;
		LElbowDef.lowerAngle		= RElbowDef.lowerAngle		= -2.7925268f;
		LElbowDef.upperAngle		= RElbowDef.upperAngle		= 0;
	}

	//b.LWristDef.body1		= LHand;
	//b.LWristDef.body2		= LForearm;
	//b.RWristDef.body1		= RHand;
	//b.RWristDef.body2		= RForearm;
	{	// wrists
		b2Vec2 anchor = b2Vec2(-1.0f/16.0f,-12.0f/16.0f);
		LWristDef.localAnchorA		= RWristDef.localAnchorA	= anchor - LHandDef.position;
		LWristDef.localAnchorB		= RWristDef.localAnchorB	= anchor - LForearmDef.position;
		LWristDef.referenceAngle	= RWristDef.referenceAngle	= 0.0f;
		LWristDef.lowerAngle		= RWristDef.lowerAngle		= -0.174532925f;
		LWristDef.upperAngle		= RWristDef.upperAngle		= 0.174532925f;
	}
}

void BipedDef::DefaultPositions()
{
	LFootDef.position		= RFootDef.position			= b2Vec2(4.0f/16.0f,-40.0f/16.0f);
	LCalfDef.position		= RCalfDef.position			= b2Vec2(-1.0f/16.0f,-30.0f/16.0f);
	LThighDef.position		= RThighDef.position		= b2Vec2(1.0f/16.0f,-13.0f/16.0f);
	LUpperArmDef.position	= RUpperArmDef.position		= b2Vec2(-2.0f/16.0f,18.0f/16.0f);
	LForearmDef.position	= RForearmDef.position		= b2Vec2(-2.0f/16.0f,-1.0f/16.0f);
	LHandDef.position		= RHandDef.position			= b2Vec2(-3.0f/16.0f,-17.0f/16.0f);
	PelvisDef.position									= b2Vec2(0.0f/16.0f,0.0f/16.0f);
	StomachDef.position									= b2Vec2(1.0f/16.0f,10.0f/16.0f);
	ChestDef.position									= b2Vec2(1.0f/16.0f,23.0f/16.0f);
	NeckDef.position									= b2Vec2(6.0f/16.0f,32.0f/16.0f);
	HeadDef.position									= b2Vec2(15.0f/16.0f,37.0f/16.0f);
}
