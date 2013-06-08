//
//  Bridge.mm
//  CTM
//
//  Created by Ryan McBride on 4/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Bridge.h"
#include "TextureObject.h"
#include "../../ScreenHelper.h"

using namespace cocos2d;


Bridge::Bridge(b2World *world, CCNode *layer, b2Body *ground, b2Vec2 *position, int segments, float xoffset, float yoffset, int sort):
TrackObject(position->x, 10.0f)
{
	m_world = world;
	m_ccLayer = layer;
	m_ground = ground;
	m_StartPos = *position;
    m_segments = segments;
    m_sort = sort;
    m_yOffset = yoffset;
    m_xOffset = xoffset;
}
Bridge::~Bridge()
{
	if(m_created)
	{
		for (int32 i = 0; i < m_segments; ++i)
		{
			TextureObject *tex = (TextureObject *)m_Bridge[i]->GetUserData();
			delete tex;
		}
	}
}
void Bridge::CreateSelf()
{
	if(m_created) return;
	
	float scalex = 3.0f;
	float scaley = 1.0f;
	float widthx = 0.5f*scalex;
	float heighty = 0.125f*scaley;
	float fCount = m_segments;
	
	float heightFromGround = m_StartPos.y-heighty;
	float xoffset = m_StartPos.x;
	
	{
		b2PolygonShape shape;
		shape.SetAsBox(widthx, heighty);
		
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 20.0f;
		fd.friction = 0.2f;
		
		b2RevoluteJointDef jd;
		
		b2Body* prevBody = m_ground;
		for (int32 i = 0; i < m_segments; ++i)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-(fCount*scalex/2.0f-widthx) + (2.0f*widthx) * i + xoffset, heightFromGround);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
			
			b2Vec2 anchor(-(fCount*scalex/2.0f) + (2.0f*widthx) * i + xoffset, heightFromGround);
			jd.Initialize(prevBody, body, anchor);
			m_world->CreateJoint(&jd);
			
			if (i == (m_segments >> 1))
			{
				m_middle = body;
			}
			prevBody = body;
			m_Bridge[i] = body;
			
			TextureObject *tex;
            switch (i%4)
            {
                default:
                case 0:
                    tex = new TextureObject((char*)"ctm_Bridge01.png",m_ccLayer,3,true);
                    break;
                case 1:
                    tex = new TextureObject((char*)"ctm_Bridge02.png",m_ccLayer,3,true);
                    break;
                case 2:
                    tex = new TextureObject((char*)"ctm_Bridge03.png",m_ccLayer,3,true);
                    break;
                case 3:
                    tex = new TextureObject((char*)"ctm_Bridge04.png",m_ccLayer,3,true);
                    break;
                    
            }
			tex->SetTextureScale(1.0f,1.0f);
			body->SetUserData(tex);
            
            CCSprite *ropes = CCSprite::createWithSpriteFrameName("ctm_BridgeRopes.png");
            ropes->setScaleY(0.5f);
            ropes->setPosition(ccp(57,8));
            tex->GetSprite()->addChild(ropes);
            
            if(i==0)
            {
                ropes = CCSprite::createWithSpriteFrameName("ctm_BridgeRopes.png");
                ropes->setScaleY(0.5f);
                ropes->setPosition(ccp(8,8));
                tex->GetSprite()->addChild(ropes);
            }
            
		}
		{
            b2PolygonShape box;
            b2FixtureDef fd;
            b2BodyDef bd;
            
            box.SetAsBox(15.0f/PTM_RATIO, 15.0f/PTM_RATIO);
            
            fd.shape = &box;
            fd.friction = 0.62f;
            fd.filter.groupIndex = -1;
            fd.isSensor = true;
            
            bd.position.Set(-(fCount*scalex/2.0f) + (2.0f*widthx) * (m_segments) + xoffset, heightFromGround);
            
            b2Body *rightSide = m_world->CreateBody(&bd);
            rightSide->CreateFixture(&fd);
            
            b2Vec2 anchor(-(fCount*scalex/2.0f) + (2.0f*widthx) * m_segments + xoffset, heightFromGround);
            jd.Initialize(prevBody, rightSide, anchor);
            m_world->CreateJoint(&jd);
            b2Vec2 p = rightSide->GetPosition();
            p.y += m_yOffset;
            p.x += m_xOffset;
            rightSide->SetTransform(p, 0);
        }
	}
}
void Bridge::DestroySelf()
{
	if(m_created)
	{
		for (int32 i = 0; i < m_segments; ++i)
		{
			TextureObject* texObject = (TextureObject*)m_Bridge[i]->GetUserData();
			texObject->ReleaseTexture();
			delete texObject;
			m_world->DestroyBody(m_Bridge[i]);
		}
	}
}
