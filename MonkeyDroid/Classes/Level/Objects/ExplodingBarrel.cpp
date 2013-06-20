//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "ExplodingBarrel.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../Rider/Monkey.h"
#include "../Rider/DirtBike.h"
#include "../Level.h"

using namespace cocos2d;


void createBarrelExplosion(CCNode *ccLayer, float x,float y)
{
    CCParticleSystemQuad *emitter = CCParticleSystemQuad::create("ctm_BarrelExplosion.plist");
    emitter->setPosition(ccp(x*ScreenHelper::getCameraZoom(),y*ScreenHelper::getCameraZoom()));
    ccLayer->addChild(emitter);
}


ExplodingBarrel::ExplodingBarrel(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
}
ExplodingBarrel::~ExplodingBarrel()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void ExplodingBarrel::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(0.8f, 1.0f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex = new TextureObject((char*)"ctm_Barrel.png",m_ccLayer,1,true,kTexture2DPixelFormat_Default);
	m_MainCollision->SetUserData(tex);
	tex->SetTextureOffset(0.0f, 0.55);
	m_Exploded = false;
}
void ExplodingBarrel::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}

bool ExplodingBarrel::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(myFixture == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(myFixture == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
		if(!Rider::g_isCrashed)
		{
			Rider::g_LauchDir.x = RandomFloat(-20.0f,20.0f);
			Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
			Rider::g_LauchDir.y = 50.0f;
			Rider::g_DoLaunch = true;
			Rider::g_ForceCrash = 0.2f;
            Level::ScreenShake(0.5f,10.0f,10.0f);
            Monkey::s_RandomXVel = 10.0f;
            Monkey::s_RandomYVel = 10.0f;
		}
        else
        {
            Level::ScreenShake(0.5f,10.0f,10.0f);
            Monkey::s_RandomXVel = 10.0f;
            Monkey::s_RandomYVel = 10.0f;

            b2Body *other = NULL;
            
            if(myFixture == fixtureA)
                other = fixtureB->GetBody();
            if(myFixture == fixtureB)
                other = fixtureA->GetBody();
            
            b2Vec2 away = Monkey::getMonkey()->getCenter()-myFixture->GetBody()->GetPosition();
            float length = away.Normalize();
            if(length<5.0f || other->GetFixtureList()->GetFilterData().categoryBits == 0x0004)
            {
                away *= 35.0f;
                Monkey::getMonkey()->SetVelocity(away);
            }
            away = DirtBike::s_Cart->GetPosition()-myFixture->GetBody()->GetPosition();
            length = away.Normalize();
            if(length<4.0f || other == DirtBike::s_Cart)
            {
                away *= 35.0f;
                DirtBike::s_Cart->SetLinearVelocity(away);
            }
            away = DirtBike::s_Wheel1->GetPosition()-myFixture->GetBody()->GetPosition();
            length = away.Normalize();
            if(length<4.0f || other == DirtBike::s_Wheel1)
            {
                away *= 35.0f;
                DirtBike::s_Wheel1->SetLinearVelocity(away);
            }
            away = DirtBike::s_Wheel2->GetPosition()-myFixture->GetBody()->GetPosition();
            length = away.Normalize();
            if(length<4.0f || other == DirtBike::s_Wheel2)
            {
                away *= 35.0f;
                DirtBike::s_Wheel2->SetLinearVelocity(away);
            }
            
        }
        Rider::g_OnFire = 5.0f;
		createBarrelExplosion(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO);
		//createExplosion([m_ccLayer parent],m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO);
		
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->GetSprite()->setVisible(false);
		m_Exploded = true;
		return false;
	}
	return false;
}