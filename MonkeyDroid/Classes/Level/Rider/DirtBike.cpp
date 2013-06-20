//
//  DirtBike.mm
//  CTM
//
//  Created by Ryan McBride on 3/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DirtBike.h"
#include "Rider.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../../ScreenHelper.h"
#include "../../AudioManager.h"

//#import "FinishParticle.h"
//#import "GameLevel.h"
using namespace CocosDenshion;

extern bool g_is60;
extern bool g_bIsRetina;
extern bool g_PermanentFire;

void createDustVFX(CCNode *ccLayer, float x,float y)
{
    CCParticleSystemQuad *emitter = CCParticleSystemQuad::create("ctm_Dust_Kick_02.plist");
    emitter->setPosition(ccp(x*ScreenHelper::getCameraZoom(),y*ScreenHelper::getCameraZoom()));
    ccLayer->addChild(emitter);
}

class GroundTestCallback : public b2RayCastCallback 
{
public:
	GroundTestCallback()
	{
		m_bHitGround = false;
		m_ingorefixtures = 0;
	}
	virtual ~GroundTestCallback(){}
	virtual float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
								  const b2Vec2& normal, float32 fraction)
	{
        if(fixture->IsSensor())
            return -1.0f;
        
		for(int i = 0; i < m_ingorefixtures; i++)
		{
			if(m_pIgnoreFixtures[i] == fixture)
				return -1.0f;
		}
		m_bHitGround = true;
		return 0.0f;
	}
	void addIgnoreFixture( b2Fixture* fixture)
	{
		assert(m_ingorefixtures<30);
		m_pIgnoreFixtures[m_ingorefixtures] = fixture;
		m_ingorefixtures++;		
		
	}
	b2Fixture *m_pIgnoreFixtures[30];
	int m_ingorefixtures;
	bool m_bHitGround;
	b2Vec2 m_Parallel;
};

b2Body *DirtBike::s_Cart = NULL;
b2Body *DirtBike::s_Wheel1 = NULL;
b2Body *DirtBike::s_Wheel2 = NULL;

DirtBike::DirtBike(b2World *world, CCLayer *ccLayer, b2Vec2 &startPos)
{
	m_LHJoint = NULL;
	m_CCLayer = ccLayer;
	m_world = world;
	m_bHitBackWheel = false;
	m_bHitFrontWheel = false;
	m_bHitRiderTest = false;
	m_AirSpin = 0.0f;
	m_bInAir = false;
	m_bIsUpsideDown = false;
	m_flipcount = 0;
	m_Crashed = false;
	m_GroundRayCastTest = new GroundTestCallback();
	m_Forward.x = 1.0f;
	m_Forward.y = 0.0f;
    m_bDustOnLanding = false;
    m_iRiderHitRefCount = 0;
    m_fhitCountDelay = 0.3f;
    m_bTestTrickDone = false;
	
	float axel1Length = TEST_SCALE*0.7f;
	float axel1Angle = b2_pi/2.75f;
	b2Vec2 axel1Pos(TEST_SCALE*-1.6f,TEST_SCALE*-0.3f);
	float axel2Length = TEST_SCALE*0.7f;
	float axel2Angle = -b2_pi/2.75f;
	b2Vec2 axel2Pos(TEST_SCALE*1.6f,TEST_SCALE*-0.3f);
	
	// add cart //
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	bodyDef.position.Set(startPos.x,startPos.y);
	bodyDef.type = b2_dynamicBody;
	
	cart = m_world->CreateBody(&bodyDef);
	
	fixtureDef.density = 25.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.filter.categoryBits = 0x0008;
	fixtureDef.filter.maskBits = 0x0003;
	
	
	polygonShape.SetAsBox(1.5f, 0.3f);
	fixtureDef.shape = &polygonShape;
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(cart->CreateFixture(&fixtureDef));
	
	
	fixtureDef.density = 0.0f;
	fixtureDef.isSensor = true;
	b2Vec2 points[6] = 
	{
		
		b2Vec2(0.7f,0.0f),
		b2Vec2(0.7f,3.25f),
		b2Vec2(-0.7f,3.25f),
		b2Vec2(-0.7f,0.0f),
	};
	polygonShape.Set(points,4);
	m_RiderTest = cart->CreateFixture(&fixtureDef);
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(m_RiderTest);
	fixtureDef.isSensor = false;
	fixtureDef.density = 25.0f;
	
	
	
	fixtureDef.filter.categoryBits = 0x0010;
	fixtureDef.filter.maskBits = 0x0007;
	polygonShape.SetAsBox(TEST_SCALE*0.4f, TEST_SCALE*0.15f, axel1Pos, axel1Angle);
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(cart->CreateFixture(&fixtureDef));
	
	polygonShape.SetAsBox(0.4f*axel2Length, TEST_SCALE*0.15f, axel2Pos, axel2Angle);
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(cart->CreateFixture(&fixtureDef));
	
	
	bodyDef.position.Set(startPos.x,startPos.y);
	
	cart->ResetMassData();
	
	fixtureDef.density = 18.0f;
	
	
	// add the axles //
	b2Body *axle1 = m_world->CreateBody(&bodyDef);
	
	polygonShape.SetAsBox(TEST_SCALE*0.4f, TEST_SCALE*0.1f, b2Vec2(axel1Pos.x - axel1Length*0.6f*cosf(axel1Angle), axel1Pos.y - axel1Length*0.6f*sinf(axel1Angle)), axel1Angle);
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(axle1->CreateFixture(&fixtureDef));
	axle1->ResetMassData();
	
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.Initialize(cart, axle1, axle1->GetWorldCenter(), b2Vec2(cosf(axel1Angle), sinf(axel1Angle)));
	prismaticJointDef.lowerTranslation = -0.3f*axel1Length;
	prismaticJointDef.upperTranslation = 0.5f*axel1Length;
	prismaticJointDef.enableLimit = true;
	prismaticJointDef.enableMotor = true;
	
	spring1 = (b2PrismaticJoint*)m_world->CreateJoint(&prismaticJointDef);
	
	
	b2Body *axle2 = m_world->CreateBody(&bodyDef);
	
	polygonShape.SetAsBox(0.4f*axel2Length, TEST_SCALE*0.1f, b2Vec2(axel2Pos.x + axel2Length*0.6f*cosf(axel2Angle), axel2Pos.y + axel2Length*0.6f*sinf(axel2Angle)), axel2Angle);
	((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(axle2->CreateFixture(&fixtureDef));
	axle2->ResetMassData();
	
	prismaticJointDef.Initialize(cart, axle2, axle2->GetWorldCenter(), b2Vec2(-cosf(-axel2Angle), sinf(-axel2Angle)));
	
	prismaticJointDef.lowerTranslation = -0.3f*axel2Length;
	prismaticJointDef.upperTranslation = 0.5f*axel2Length;
	spring2 = (b2PrismaticJoint*)m_world->CreateJoint(&prismaticJointDef);
	
	
	// add wheels //
	circleShape.m_radius = TEST_SCALE*0.8f;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 6.0f;
	fixtureDef.friction = 0.05f;
	fixtureDef.restitution = 0.1f;
	
	for (int i = 0; i < 2; i++) 
	{
		if (i == 0) 
		{
			m_BackWheelStart.Set(axel1Pos.x - axel1Length*1.3f*cosf(axel1Angle), axel1Pos.y - axel1Length*1.3f*sinf(axel1Angle));
			m_BackWheelOffset.Set(0.0f,0.0f);
			circleShape.m_p = m_BackWheelOffset;
			fixtureDef.density = 0.0f;
			fixtureDef.isSensor = true;
			m_BackWheel = cart->CreateFixture(&fixtureDef);
			((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(m_BackWheel);
			circleShape.m_p.Set(0.0f,0.0f);
			fixtureDef.isSensor = false;
			fixtureDef.density = 6.0f;
			bodyDef.position.Set(axle1->GetWorldCenter().x - axel1Length*0.3f*cosf(axel1Angle), axle1->GetWorldCenter().y - axel1Length*0.3f*sinf(axel1Angle));
		}
		else 
		{
			m_FrontWheelStart.Set(axel2Pos.x + axel2Length*1.3f*cosf(axel2Angle), axel2Pos.y + axel2Length*1.3f*sinf(axel2Angle));
			m_FrontWheelOffset.Set(0.0f,0.0f);
			circleShape.m_p = m_FrontWheelStart;
			fixtureDef.density = 0.0f;
			fixtureDef.isSensor = true;
			m_FrontWheel = cart->CreateFixture(&fixtureDef);
			((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(m_FrontWheel);
			circleShape.m_p.Set(0.0f,0.0f);
			fixtureDef.isSensor = false;
			fixtureDef.density = 6.0f;
			//fixtureDef.friction = 0.05f;
			bodyDef.position.Set(axle2->GetWorldCenter().x + axel2Length*0.3f*cosf(axel2Angle), axle2->GetWorldCenter().y + axel2Length*0.3f*sinf(axel2Angle));
		}
		bodyDef.allowSleep = false;
		
        //m_FrontWheelColCenter.Set(axle2->GetWorldCenter().x + axel2Length*0.3f*cosf(axel2Angle), axle2->GetWorldCenter().y + axel2Length*0.3f*sinf(axel2Angle));
        //m_BackWheelColCenter.Set(axle1->GetWorldCenter().x - axel1Length*0.3f*cosf(axel1Angle), axle1->GetWorldCenter().y - axel1Length*0.3f*sinf(axel1Angle));
        m_FrontWheelColCenter = m_FrontWheelStart;
        m_BackWheelColCenter = m_BackWheelStart;
        
		if (i == 0) 
		{
			wheel1 = m_world->CreateBody(&bodyDef);
            //wheel1->SetBullet(true);
		}
		else 
		{
			wheel2 = m_world->CreateBody(&bodyDef);
            //wheel2->SetBullet(true);
		}
		
		((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture((i == 0 ? wheel1 : wheel2)->CreateFixture(&fixtureDef));
		(i == 0 ? wheel1 : wheel2)->ResetMassData();
		
	}
	
	
	// add joints //
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.enableMotor = false;
	
	revoluteJointDef.Initialize(axle1, wheel1, wheel1->GetWorldCenter());
	motor1 = (b2RevoluteJoint*)m_world->CreateJoint(&revoluteJointDef);
	
	revoluteJointDef.Initialize(axle2, wheel2, wheel2->GetWorldCenter());
	motor2 = (b2RevoluteJoint*)m_world->CreateJoint(&revoluteJointDef);
	
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Rider-hd.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Rider-hd.pv.plist");
    
    CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create("ctm_Rider-hd.pvr.ccz");
    m_CCLayer->addChild(spritesheet,2);
    char temp[128];
    const char *fireExt = "";
    if(g_PermanentFire)
        fireExt = "_Fire";
    
    sprintf(temp,"ctm_BikeRearWheel%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[0] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);
    
    sprintf(temp,"ctm_BikeFrontWheel%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[1] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);
    
    sprintf(temp,"ctm_BikeFrontSuspension%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[4] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);

    sprintf(temp,"ctm_BikeExhaust%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[5] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);

    sprintf(temp,"ctm_BikeBody%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[2] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);

    sprintf(temp,"ctm_BikeBackSuspension%s%s.png",SaveLoad::GetBikeExt(),fireExt);
    m_Texture[3] = new TextureObject(temp,spritesheet,0,true,kTexture2DPixelFormat_Default);

    m_Texture[2]->SetTextureOffset(-0.05f,-0.15f);
    cart->SetUserData(m_Texture[2]);
    
    if(g_bIsRetina)
    {
        m_Texture[0]->SetTextureScale(0.5f,0.5f);
        m_Texture[1]->SetTextureScale(0.5f,0.5f);
        m_Texture[2]->SetTextureScale(-0.5f,0.5f);
        m_Texture[3]->SetTextureScale(-0.5f,0.5f);
        m_Texture[4]->SetTextureScale(-0.5f,0.5f);
        m_Texture[5]->SetTextureScale(-0.5f,0.5f);
    }

	cart->SetAngularDamping(10.0f);
	
	m_TotalMass = cart->GetMass();
	
	change = 0.01f;
    
    s_Cart = cart;
    s_Wheel1 = wheel1;
    s_Wheel2 = wheel2;
}
CCSprite *DirtBike::GetWheelFrontSprite()
{
    return m_Texture[1]->GetSprite();
}
CCSprite *DirtBike::GetWheelBackSprite()
{
    return m_Texture[0]->GetSprite();
}

DirtBike::~DirtBike()
{
    //[Options RegisterEngineLoop:nil];
	delete m_Texture[0];
	delete m_Texture[1];
	delete m_Texture[2];
	delete m_Texture[3];
	delete m_Texture[4];
	delete m_Texture[5];
	delete m_GroundRayCastTest;
    s_Cart = NULL;
    s_Wheel1 = NULL;
    s_Wheel2 = NULL;
}
void DirtBike::Step(int loop)
{
	if(m_Crashed) return;
    
	if(Rider::g_inLoop)
	{
		m_bHitFrontWheel = false;
		m_bHitBackWheel = false;
	}

    if(m_iRiderHitRefCount)
    {
        if(m_fhitCountDelay<=0.0f)
        {
            if(m_RiderTest->GetBody()->GetTransform().q.c < 0.0f)
            {
                float yvel = cart->GetLinearVelocity().y;
                Rider::g_LauchDir.x = 0.0f;
                Rider::g_LauchDir.y = 16.0f - yvel/2.0f;
            }
            else
            {
                Rider::g_LauchDir.x = m_RiderTest->GetBody()->GetTransform().q.s * 17.0f;
                Rider::g_LauchDir.y = m_RiderTest->GetBody()->GetTransform().q.c * -17.0f;
            }
            
            Rider::g_DoLaunch = true;
            Rider::g_ScoreManager->AddScore(-100);
            
            m_fhitCountDelay = 0.3f;
        }
        else
        {
            m_fhitCountDelay -= (g_is60?1.0f/60.0f:1.0f/30.0f);
        }
    }
    
	if(spring1)
	{		
		float spring1Trans = spring1->GetJointTranslation();
		float spring2Trans = spring2->GetJointTranslation();
		float MAX_MOTOR_FORCE = 5000.0f;
		float MOTOR_SPEED = 15.0f;
		float CUTOFF_TRANSLATION = 0.10f;
		
		if(spring1Trans > CUTOFF_TRANSLATION)
		{
            float maxmul = 10.0f*spring1Trans;
			if(maxmul>3.0f)
				maxmul = 3.0f;
            if(spring1Trans>m_LastSprigTrans1)
                maxmul *= 2.0f;
			spring1->SetMaxMotorForce(MAX_MOTOR_FORCE*maxmul);
			spring1->SetMotorSpeed(-MOTOR_SPEED*maxmul);
            
            /*b2Transform xform = cart->GetTransform();
            
            b2Vec2 bVec = m_BackWheelColCenter;
            bVec.x += 0.2f;
            bVec.y += 0.2f;
            b2Vec2 bPos = b2Mul(xform,bVec);
            
            b2Body *bwheel = GetWheelBack();
            
            bwheel->SetTransform(bPos,bwheel->GetAngle());*/
            
		}
		else if (spring1Trans > 0.0f)
		{
			spring1->SetMaxMotorForce(MAX_MOTOR_FORCE*pow((spring1Trans*10.0f),2.0f));
			spring1->SetMotorSpeed(-MOTOR_SPEED*pow((spring1Trans*10.0f),2.0f));
		}
		else if (spring1Trans > -CUTOFF_TRANSLATION)
		{
			spring1->SetMaxMotorForce(MAX_MOTOR_FORCE*pow((spring1Trans*10.0f),2.0f));
			spring1->SetMotorSpeed(MOTOR_SPEED*pow((spring1Trans*10.0f),2.0f));
		}
		else
		{
            float maxmul = -10.0f*spring1Trans;
			if(maxmul>3.0f)
				maxmul = 3.0f;
            if(spring1Trans<m_LastSprigTrans1)
                maxmul *= 2.0f;
			spring1->SetMaxMotorForce(MAX_MOTOR_FORCE*maxmul);
			spring1->SetMotorSpeed(MOTOR_SPEED*maxmul);
            
            /*b2Transform xform = cart->GetTransform();
            
            b2Vec2 bVec = m_BackWheelColCenter;
            bVec.x += 0.2f;
            bVec.y += 0.2f;
            b2Vec2 bPos = b2Mul(xform,bVec);
            
            b2Body *bwheel = GetWheelBack();
            
            bwheel->SetTransform(bPos,bwheel->GetAngle());*/
		}
		m_LastSprigTrans1 = spring1Trans;

		if(spring2Trans > CUTOFF_TRANSLATION)
		{
			float maxmul = 10.0f*spring2Trans;
			if(maxmul>3.0f)
				maxmul = 3.0f;			
			
			spring2->SetMaxMotorForce(MAX_MOTOR_FORCE*maxmul);
			spring2->SetMotorSpeed(-MOTOR_SPEED*maxmul);
		}
		else if (spring2Trans > 0.0f)
		{
			spring2->SetMaxMotorForce(MAX_MOTOR_FORCE*pow((spring2Trans*10.0f),2.0f));
			spring2->SetMotorSpeed(-MOTOR_SPEED*pow((spring2Trans*10.0f),2.0f));
		}
		else if (spring2Trans > -CUTOFF_TRANSLATION)
		{
			spring2->SetMaxMotorForce(MAX_MOTOR_FORCE*pow((spring2Trans*10.0f),2.0f));
			spring2->SetMotorSpeed(MOTOR_SPEED*pow((spring2Trans*10.0f),2.0f));
		}
		else
		{
			float maxmul = -10.0f*spring2Trans;
			if(maxmul>3.0f)
				maxmul = 3.0f;			
			
			spring2->SetMaxMotorForce(MAX_MOTOR_FORCE*maxmul);
			spring2->SetMotorSpeed(MOTOR_SPEED*maxmul);
		}

	}
	
	m_Texture[0]->SetTextureRotation(wheel1->GetAngle());
	m_Texture[1]->SetTextureRotation(wheel2->GetAngle());
	
	if(m_bHitBackWheel)
	{
		m_BackWheelOffset.y += 0.04f;
		if(m_BackWheelOffset.y > 1.0f)
			m_BackWheelOffset.y = 1.0f;
	}
	else
	{
		m_BackWheelOffset.y -= 0.04f;
		if(m_BackWheelOffset.y < 0.0f)
			m_BackWheelOffset.y = 0.0f;
		
	}
	if(m_bHitFrontWheel)
	{
		m_FrontWheelOffset.y += 0.04f;
		if(m_FrontWheelOffset.y > 1.0f)
			m_FrontWheelOffset.y = 1.0f;
	}
	else
	{
		m_FrontWheelOffset.y -= 0.04f;
		if(m_FrontWheelOffset.y < 0.0f)
			m_FrontWheelOffset.y = 0.0f;
		
	}
	m_FrontWheelOffset.x = -m_FrontWheelOffset.y*0.55f;
	
	((b2CircleShape*)m_BackWheel->GetShape())->m_p = m_BackWheelStart + m_BackWheelOffset;
	((b2CircleShape*)m_FrontWheel->GetShape())->m_p = m_FrontWheelStart + m_FrontWheelOffset;
	
	b2Transform backTransform = m_BackWheel->GetBody()->GetTransform();
	b2Vec2 center = b2Mul(backTransform, ((b2CircleShape*)m_BackWheel->GetShape())->m_p);
	b2Vec2 backdownraystart = center;
	b2Vec2 backdownrayend = center + b2Vec2(0.0f, -2.5f);
	
	b2Transform frontTransform = m_FrontWheel->GetBody()->GetTransform();
	center = b2Mul(frontTransform, ((b2CircleShape*)m_FrontWheel->GetShape())->m_p);
	b2Vec2 frontdownraystart = center;
	b2Vec2 frontdownrayend = center + b2Vec2(0.0f, -2.5f);
	
	
    b2Transform xform = cart->GetTransform();
    b2Vec2 jointCompress;
    float jointTrans = spring1->GetJointTranslation();
    if(jointTrans>0.5f)jointTrans=0.5f;
    if(jointTrans<-0.5f)jointTrans=-0.5f;
    if(Rider::g_inLoop)
        jointTrans = 0.032f;
    jointCompress.Set(1.0f*jointTrans,1.0f*jointTrans);
    b2Vec2 bPos = b2Mul(xform,m_BackWheelColCenter+b2Vec2(0.65f,0.56f)+jointCompress);
	m_Texture[3]->SetTextureRotation(cart->GetAngle());
	m_Texture[3]->SetTexturePosition(bPos.x,bPos.y);
	
    bPos = b2Mul(xform,m_BackWheelColCenter+b2Vec2(-0.3f,2.0f));
	m_Texture[5]->SetTextureRotation(cart->GetAngle());
	m_Texture[5]->SetTexturePosition(bPos.x,bPos.y);
    
    jointTrans = spring2->GetJointTranslation();
    if(jointTrans>0.5f)jointTrans=0.5f;
    if(jointTrans<-0.25f)jointTrans=-0.25f;
    if(Rider::g_inLoop)
        jointTrans = 0.032f;
    jointCompress.Set(-1.0f*jointTrans,1.0f*jointTrans);
    b2Vec2 fPos = b2Mul(xform,m_FrontWheelColCenter+b2Vec2(-0.48f,0.6f)+jointCompress);
    m_Texture[4]->SetTextureRotation(cart->GetAngle());
	m_Texture[4]->SetTexturePosition(fPos.x,fPos.y);

	
    fPos = b2Mul(xform,m_FrontWheelColCenter);
    bPos = b2Mul(xform,m_BackWheelColCenter);
	b2Vec2 wheelClamp = wheel1->GetPosition()-bPos;
    if(wheelClamp.Normalize()>0.25f)
    {
        wheelClamp = bPos+(0.25f*wheelClamp);
        m_Texture[0]->SetTexturePosition(wheelClamp.x , wheelClamp.y);
    }
    else
        m_Texture[0]->SetTexturePosition(wheel1->GetPosition().x , wheel1->GetPosition().y);
	wheelClamp = wheel2->GetPosition()-fPos;
    if(wheelClamp.Normalize()>0.25f)
    {
        wheelClamp = fPos+(0.25f*wheelClamp);
        m_Texture[1]->SetTexturePosition(wheelClamp.x , wheelClamp.y);
    }
    else
        m_Texture[1]->SetTexturePosition(wheel2->GetPosition().x , wheel2->GetPosition().y);

	
	
	bool wasinAir = m_bInAir;
	m_bInAir = !((GroundTestCallback*)m_GroundRayCastTest)->m_bHitGround;
	
	if(wasinAir && !m_bInAir)
    {
        b2Vec2 linearVel = cart->GetLinearVelocity();
		
        if(!Rider::g_inLoop && linearVel.y < -20.0f)
        {
            m_bDustOnLanding = true;    
        }
        m_bTestTrickDone = true;
    }
    
	if(!m_bInAir && (m_BackWheelOffset.y!=0.0f || m_FrontWheelOffset.y!=0.0f))
	{
		b2Vec2 linearVel = cart->GetLinearVelocity();
		if(linearVel.y < -2.0f)
		{
			linearVel.y/=2.0f;
			cart->SetLinearVelocity(linearVel);
		}
	}
	
	
	((GroundTestCallback*)m_GroundRayCastTest)->m_bHitGround = false;
	//if(backdownraystart.x==backdownraystart.x && backdownraystart.y==backdownraystart.y)
		m_world->RayCast(m_GroundRayCastTest, backdownraystart, backdownrayend);
	//if(frontdownraystart.x==frontdownraystart.x && frontdownraystart.y==frontdownraystart.y)
		m_world->RayCast(m_GroundRayCastTest, frontdownraystart, frontdownrayend);

	float angularVelocity = cart->GetAngularVelocity();
	float floop = (float)loop;
	
	if(Rider::g_inLoop)
    {
        //if(Rider::g_TrickState)
        //    Rider::g_ScoreManager->SetTrick(Rider::g_TrickState);
        return;
    }
		
	//get an angle from 0 to pi or 0 to -pi
	float angle = cart->GetAngle();
	while(angle >= 2.0f*b2_pi)
		angle -= 2.0f*b2_pi;
	while(angle < 0.0f)
		angle += 2.0f*b2_pi;
	if(angle > b2_pi)
		angle -=  2.0f*b2_pi;
	
	bool wasUpSideDown = m_bIsUpsideDown;
	//are we upside down?
	if(cart->GetTransform().q.GetXAxis().y <= -0.85f)
	{
		m_bIsUpsideDown = true;
	}
	else
	{
		m_bIsUpsideDown = false;
	}
	
	if(wasUpSideDown && !m_bIsUpsideDown)
	{
		m_flipcount++;
        Rider::g_ScoreManager->SetFlips(m_flipcount);
	}
	
    //if(Rider::g_TrickState)
    //    Rider::g_ScoreManager->SetTrick(Rider::g_TrickState);
    
    if(m_bTestTrickDone)
    {
        if(Rider::s_bWheelsTouch)
        {
            Rider::g_TrickState = 0;
            m_flipcount = 0;
            Rider::g_ScoreManager->FinishTrickGood(true);
            m_bTestTrickDone = false;
        }
    }
	/*if(wasinAir && !m_bInAir)
	{
        Rider::g_TrickState = 0;
		m_flipcount = 0;
        [Rider::g_ScoreManager FinishTrickGood:YES];
	}
	if(!m_bInAir && m_flipcount)
    {
        m_flipcount = 0;
        [Rider::g_ScoreManager FinishTrickGood:YES];
    }*/
	if(m_bInAir && m_AirSpin != 0.0f)
	{
        float spinScale = 1.0f;
        if(SaveLoad::m_SaveData.flipLockLevel==1)
            spinScale = 0.5f;
        if(SaveLoad::m_SaveData.flipLockLevel==2)
            spinScale = 0.75f;
        
		if((m_AirSpin > 0.0f && angularVelocity < spinScale*m_AirSpin*9.28f) ||
		   (m_AirSpin < 0.0f && angularVelocity > spinScale*m_AirSpin*9.28f))
			cart->ApplyTorque(spinScale*m_AirSpin*m_TotalMass*200.0f/floop);
	}
	else if(m_bInAir || (angle < -b2_pi/4.0f) || (angle > b2_pi/4.0f))// right the ship
	{
		if(angle > 0.0f)
		{
			//if(angularVelocity > m_AirSpin*9.28f)
            float force = -angle*angle*m_TotalMass*100.0f;
            if(force<-10000)
                force=-10000.0f;
			cart->ApplyTorque(force);
		}
		else
		{
			//if(angularVelocity < m_AirSpin*9.28f)
            float force = angle*angle*m_TotalMass*100.0f;
            if(force > 10000)
                force = 10000.0f;
			cart->ApplyTorque(force);
		}
	}
	
	
	if(Rider::g_DoLaunch)
	{
		cart->SetLinearVelocity(Rider::g_LauchDir);
		Rider::g_DoLaunch = false;
        Rider::g_LauchDir.x = Rider::g_LauchDir.y = 0.0f;
	}
    if(Rider::g_isFinished)
    {
        cart->SetLinearDamping(1.0f);
		wheel1->SetAngularDamping(1.0f/10.0f);
		wheel2->SetAngularDamping(1.0f/10.0f);
    }
	
}
void DirtBike::Crash()
{
	if(!m_Crashed)
	{
        m_Crashed = true;
		if(m_LHJoint)
		{
			m_world->DestroyJoint(m_LHJoint);
			m_world->DestroyJoint(m_RHJoint);
			m_world->DestroyJoint(m_LLJoint);
			m_world->DestroyJoint(m_RLJoint);
			m_world->DestroyJoint(m_ButtJoint);
			m_LHJoint = NULL;
		}
		m_world->DestroyJoint(motor1);
		m_world->DestroyJoint(motor2);
		m_world->DestroyJoint(spring1);
		m_world->DestroyJoint(spring2);
		wheel1->SetUserData(m_Texture[0]);
		wheel2->SetUserData(m_Texture[1]);
		m_Texture[3]->ReleaseTexture();
		m_Texture[4]->ReleaseTexture();
		m_Texture[5]->ReleaseTexture();
		
        if(Rider::g_WaterCrash)
        {
            m_Texture[0]->GetSprite()->setVisible(false);
            m_Texture[1]->GetSprite()->setVisible(false);
            m_Texture[2]->GetSprite()->setVisible(false);
            AudioManager::PlayEffect(AUDIO_LAUGH_TRACK);
        }
        else
        {
            AudioManager::PlayEffect(AUDIO_CHAR_PAIN);
            AudioManager::PlayEffect(AUDIO_BIKE_CRASH);
            AudioManager::PlayEffect(AUDIO_LAUGH_TRACK);
        }
        
        if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                
/*        int bgID = [GameLevel getlevelDes]->bgID;
        if(bgID == 1)
            AudioManager::PlayEffect(AUDIO_FAIL_STINGER_CITY);
        if(bgID == 2)
            AudioManager::PlayEffect(AUDIO_FAIL_STINGER_NIGHT);
        if(bgID==0)
            AudioManager::PlayEffect(AUDIO_FAIL_STINGER_ISLAND);
        if(bgID==3)
            AudioManager::PlayEffect(AUDIO_FAIL_STINGER_SPACE);
 */       
		
        Rider::g_ScoreManager->FinishTrickGood(false);
	}
}
b2Body *DirtBike::GetMainBody()
{
	return cart;
}
void DirtBike::AttachBiped(Biped *pBiped)
{
	b2WeldJointDef jd;
	jd.bodyA = cart;
	jd.bodyB = pBiped->LHand;
	jd.localAnchorA = b2Vec2(TEST_SCALE*0.4f,TEST_SCALE*1.2f);
	jd.localAnchorB = b2Vec2(TEST_SCALE*0.0f,TEST_SCALE*0.0f);
	m_LHJoint = (b2WeldJoint*)m_world->CreateJoint(&jd);
	jd.bodyB = pBiped->RHand;
	m_RHJoint = (b2WeldJoint*)m_world->CreateJoint(&jd);
	jd.localAnchorA = b2Vec2(TEST_SCALE*-0.1f,TEST_SCALE*-0.5f);
	jd.bodyB = pBiped->LFoot;
	m_LLJoint = (b2WeldJoint*)m_world->CreateJoint(&jd);
	jd.bodyB = pBiped->RFoot;
	m_RLJoint = (b2WeldJoint*)m_world->CreateJoint(&jd);
	
	jd.localAnchorA = b2Vec2(TEST_SCALE*-1.5f,TEST_SCALE*0.3f);
	jd.bodyB = pBiped->Pelvis;
	m_ButtJoint = (b2WeldJoint*)m_world->CreateJoint(&jd);
	
	for(int i = 0; i < 17; i++)
	{
		((GroundTestCallback*)m_GroundRayCastTest)->addIgnoreFixture(pBiped->allPieces[i]->GetFixtureList());
	}
}
void DirtBike::AirSpin(float val)
{
    if(!SaveLoad::m_SaveData.flipLockLevel)return;
    
	if(val < 0.15f && val > -0.15f)
	{
		if(val > 0.14f || val < -0.14f)
			return;
		val = 0.0f;
	}
	else if (val < 0.0f)
		val = -1.0f;
	else
		val = 1.0f;
	m_AirSpin = val;	
}
void DirtBike::GasAndBrake(float val, bool preStart)
{
	if(m_Crashed) return;
    if(preStart) return;
    
	if(Rider::g_inLoop)return;
    
	/*if(val < -0.01f && cart->GetPosition().x <= Rider::g_startPos.x)
	{
		cart->SetLinearDamping(10.0f);
		wheel1->SetAngularDamping(1.0f);
		wheel2->SetAngularDamping(1.0f);
		return;
	}*/
	
	if(val <0.01f && val > -0.01f)
	{
		if(!m_bInAir)
		{
			cart->SetLinearDamping(0.5f);
			wheel1->SetAngularDamping(1.0f);
			wheel2->SetAngularDamping(1.0f);
            if(fabs(cart->GetLinearVelocity().x) > 1.0f)
                Rider::g_BikeAudio->PushState(BikeAudio::DECEL);
		}
		else
		{
			wheel1->SetAngularDamping(0.0f);
			wheel2->SetAngularDamping(0.0f);
			cart->SetLinearDamping(0.0f);
		}
	}
	else
	{        
		b2ContactEdge *contactEdges =  wheel1->GetContactList();
        m_Forward.x = 1.0f;
        m_Forward.y = 0.0f;
		if(contactEdges && !m_bInAir)
		{
			while (contactEdges)
			{
				if(contactEdges->contact 
                && contactEdges->contact->IsTouching() 
                && !contactEdges->other->GetFixtureList()->IsSensor())
				{
                    if(contactEdges->contact->GetManifold())
					{
						b2Vec2 normal = contactEdges->contact->GetManifold()->localNormal;
						m_Forward.x = normal.y;
						m_Forward.y = -normal.x;
					}
				}
				contactEdges = contactEdges->next;
			}
		}
		if((m_Forward.x != m_Forward.x) || m_Forward.x > 1.0f || m_Forward.x < -1.0f)
			m_Forward.x = 1.0f;
		if((m_Forward.y != m_Forward.y) || m_Forward.y > 1.0f || m_Forward.y < -1.0f)
			m_Forward.y = 0.0f;
        if(m_Forward.x < -0.01f || m_Forward.y < -0.01f)
        {
            m_Forward.x = 1.0f;
            m_Forward.y = 0.0f;
        }

		wheel1->SetAngularDamping(0.0f);
		wheel2->SetAngularDamping(0.0f);
		cart->SetLinearDamping(0.0f);
		b2Vec2 velocity = cart->GetLinearVelocity();
        
        bool isBraking = false;
        if(!m_bInAir)
        {
            if(velocity.x > 0.1f && val < -0.01f)
                isBraking = true;
            if(velocity.x < -0.1f && val > 0.01f)
                isBraking = true;
        }

        
		float scale = velocity.x*m_Forward.x+velocity.y*m_Forward.y;
		assert(scale==scale);
		scale *= 2.5f; 
		if(m_bInAir)
			scale *= 2.0f;
		if(scale > 100.0f)
			scale = 100.0f;
		if(scale > 0.0f)
		{
			scale = (100.0f-scale)/100.0f;
			scale *= 3.0f;
		}
		if(scale < -100.0f)
			scale = -100.0f;
		if(scale < 0.0f)
		{
			scale = (-100.0f-scale)/100.0f;
			scale *= -3.0f;
		}
		if((val < 0.0f && scale > 0.0f) ||
		   (val > 0.0f && scale < 0.0f) || isBraking)
			scale *= 3.0f;
        
        if(isBraking)
            scale *= 2.0f;
            
		b2Vec2 forceVec = m_Forward;
		float forceScale = (25.75f*m_TotalMass*val*scale);
		forceVec *= forceScale;
		cart->ApplyForce(forceVec,cart->GetWorldCenter());
        
        if(!m_bInAir)
        {
            if(val < -0.1f)
                Rider::g_BikeAudio->PushState(BikeAudio::REVERSE);
            if(val > 0.1f)
                Rider::g_BikeAudio->PushState(BikeAudio::ACCEL);
        }
        else
        {
            Rider::g_BikeAudio->PushState(BikeAudio::BOUNCE);
            Rider::s_bWheelsTouch = false;
        }
	}
}
void DirtBike::SetRiderMass(float val)
{
	m_TotalMass = cart->GetMass() + val;
}

void DirtBike::BeginContact(b2Contact* contact)
{
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();
	
	if((fixtureA == m_FrontWheel && !fixtureB->IsSensor()) || (fixtureB == m_FrontWheel && !fixtureA->IsSensor()))
	{
		m_bHitFrontWheel = true;
        Rider::s_bWheelsTouch = true;
        if(m_bDustOnLanding)
        {
            m_bDustOnLanding = false;
            createDustVFX(m_CCLayer,m_FrontWheel->GetBody()->GetPosition().x*PTM_RATIO,(m_FrontWheel->GetBody()->GetPosition().y-0.8f)*PTM_RATIO);
            AudioManager::PlayEffect(AUDIO_BIKE_LAND);
        }
		return;
	}
	
	if((fixtureA == m_BackWheel && !fixtureB->IsSensor()) || (fixtureB == m_BackWheel && !fixtureA->IsSensor()))
	{
		m_bHitBackWheel = true;
        Rider::s_bWheelsTouch = true;
        if(m_bDustOnLanding)
        {
            m_bDustOnLanding = false;
            createDustVFX(m_CCLayer,m_BackWheel->GetBody()->GetPosition().x*PTM_RATIO,(m_BackWheel->GetBody()->GetPosition().y-0.8f)*PTM_RATIO);
            AudioManager::PlayEffect(AUDIO_BIKE_LAND);
        }
		return;
	}
	if((fixtureA == m_RiderTest && !fixtureB->IsSensor()) || (fixtureB == m_RiderTest && !fixtureA->IsSensor()))
	{
        if(m_iRiderHitRefCount==0)
            m_fhitCountDelay = 0.3f;
        m_iRiderHitRefCount++;
        //NSLog(@"IN %d",m_iRiderHitRefCount);


        //down
        if(m_RiderTest->GetBody()->GetTransform().q.c < 0.0f)
        {
            float yvel = cart->GetLinearVelocity().y;
            
            if(yvel < -13.0f)
            {
                m_bHitRiderTest = true;
                return;
            }
            Rider::g_LauchDir.x = 0.0f;
            Rider::g_LauchDir.y = 16.0f - yvel/2.0f;
            Rider::g_DoLaunch = true;
            Rider::g_ScoreManager->AddScore(-100);
        }
        else
        {
            Rider::g_LauchDir.x = m_RiderTest->GetBody()->GetTransform().q.s * 17.0f;
            Rider::g_LauchDir.y = m_RiderTest->GetBody()->GetTransform().q.c * -17.0f;
            Rider::g_DoLaunch = true;
            Rider::g_ScoreManager->AddScore(-100);

        }

		return;
	}

}
void DirtBike::EndContact(b2Contact* contact)
{
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();
	
	if((fixtureA == m_FrontWheel && !fixtureB->IsSensor()) || (fixtureB == m_FrontWheel && !fixtureA->IsSensor()))
	{
		m_bHitFrontWheel = false;		
	}
	
	if((fixtureA == m_BackWheel && !fixtureB->IsSensor()) || (fixtureB == m_BackWheel && !fixtureA->IsSensor()))
	{
		m_bHitBackWheel = false;
	}
    if((fixtureA == m_RiderTest && !fixtureB->IsSensor()) || (fixtureB == m_RiderTest && !fixtureA->IsSensor()))
	{
        m_iRiderHitRefCount--;
        //NSLog(@"OUT %d",m_iRiderHitRefCount);
    }
}