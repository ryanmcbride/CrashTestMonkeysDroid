/*
 *  Monkey.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Monkey.h"
#include "cocos2d.h"
#include "../../ScreenHelper.h"
#include "../../FrontEnd/SaveLoad.h"

extern bool g_bIsRetina;

USING_NS_CC;

class MonkeyTextureObject : public TextureObject
{
public:
	MonkeyTextureObject(char *texturename,CCNode *layer):
	TextureObject(texturename,layer,0,true,kTexture2DPixelFormat_Default)
	{
        SetTextureScale(0.5f,0.5f);
	}
	virtual ~MonkeyTextureObject(){}
	virtual void Draw(b2Body *owner)
	{
        float zoom = ScreenHelper::getCameraZoom();
		
		CCSprite *myActor = (CCSprite*)m_Texture;
		myActor->setPosition(CCPointMake( owner->GetWorldCenter().x * PTM_RATIO * zoom, owner->GetWorldCenter().y * PTM_RATIO * zoom));
        
        SetTextureScale(m_scale[0],m_scale[1]);
        
		myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(owner->GetAngle()));
	}
	
};

Monkey* Monkey::s_Monkey = NULL;
float Monkey::s_RandomXVel = 0.0f;
float Monkey::s_RandomYVel = 0.0f;

Monkey* Monkey::getMonkey()
{
    return s_Monkey;
}


Monkey::Monkey(b2World* world, CCLayer *layer, const b2Vec2& position, b2Transform& xform, b2Vec2 *linearVel,float *angularVel):
Biped(world,position,xform,linearVel,angularVel)
{
    const char *bodyName = NULL;
    const char *ext = "";
    if(g_bIsRetina)
        ext = "-hd";
    int number = SaveLoad::GetRiderNumber();
    switch(number)
    {
        default:
        case 0:
            bodyName = "Default";
            break;
        case 1:
            bodyName = "Cop";
            break;
        case 2:
            bodyName = "Barb";
            break;
        case 3:
            bodyName = "Elvis";
            break;
        case 4:
            bodyName = "Sock";
            break;
    };
    char texName[64];
    char plistName[64];
    sprintf(texName,"CTM%s-hd.png",bodyName);
    sprintf(plistName,"CTM%s-hd.plist",bodyName);
    CCTextureCache::sharedTextureCache()->addImage(texName);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName);
    CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create(texName);
    layer->addChild(spritesheet,3);

    char temp[128];
    sprintf(temp,"ctm%s_BottomUparm.png",bodyName);
    m_Texture[11] = new MonkeyTextureObject(temp,spritesheet);
    LUpperArm->SetUserData(m_Texture[11]);
    
    sprintf(temp,"ctm%s_BottomLoarm.png",bodyName);
    m_Texture[12] = new MonkeyTextureObject(temp,spritesheet);
    LForearm->SetUserData(m_Texture[12]);
    
    sprintf(temp,"ctm%s_BottomHand.png",bodyName);
    m_Texture[13] = new MonkeyTextureObject(temp,spritesheet);
    LHand->SetUserData(m_Texture[13]);
    
    sprintf(temp,"ctm%s_BottomFoot.png",bodyName);
    m_Texture[9] = new MonkeyTextureObject(temp,spritesheet);
    LFoot->SetUserData(m_Texture[9]);
    
    sprintf(temp,"ctm%s_BottomCalf.png",bodyName);
    m_Texture[6] = new MonkeyTextureObject(temp,spritesheet);
    LCalf->SetUserData(m_Texture[6]);
	
    sprintf(temp,"ctm%s_BottomThigh.png",bodyName);
    m_Texture[5] = new MonkeyTextureObject(temp,spritesheet);
    LThigh->SetUserData(m_Texture[5]);

    sprintf(temp,"ctm%s_Torso.png",bodyName);
    m_Texture[3] = new MonkeyTextureObject(temp,spritesheet);
    Stomach->SetUserData(m_Texture[3]);
	
    sprintf(temp,"ctm%s_Pelvis.png",bodyName);
    m_Texture[4] = new MonkeyTextureObject(temp,spritesheet);
    Pelvis->SetUserData(m_Texture[4]);

    sprintf(temp,"ctm%s_Neck.png",bodyName);
    m_Texture[1] = new MonkeyTextureObject(temp,spritesheet);
    Neck->SetUserData(m_Texture[1]);
	
    sprintf(temp,"ctm%s_Chest.png",bodyName);
    m_Texture[2] = new MonkeyTextureObject(temp,spritesheet);
    Chest->SetUserData(m_Texture[2]);
	
	sprintf(temp,"ctm%s_Head.png",bodyName);
    m_Texture[0] = new MonkeyTextureObject(temp,spritesheet);
    Head->SetUserData(m_Texture[0]);
		
	sprintf(temp,"ctm%s_TopFoot.png",bodyName);
    m_Texture[10] = new MonkeyTextureObject(temp,spritesheet);
    RFoot->SetUserData(m_Texture[10]);

	sprintf(temp,"ctm%s_TopCalf.png",bodyName);
    m_Texture[8] = new MonkeyTextureObject(temp,spritesheet);
    RCalf->SetUserData(m_Texture[8]);
	
	sprintf(temp,"ctm%s_TopThigh.png",bodyName);
    m_Texture[7] = new MonkeyTextureObject(temp,spritesheet);
    RThigh->SetUserData(m_Texture[7]);

	sprintf(temp,"ctm%s_TopUparm.png",bodyName);
    m_Texture[14] = new MonkeyTextureObject(temp,spritesheet);
    RThigh->SetUserData(m_Texture[14]);
    
	sprintf(temp,"ctm%s_TopLoarm.png",bodyName);
    m_Texture[15] = new MonkeyTextureObject(temp,spritesheet);
    RForearm->SetUserData(m_Texture[15]);
	
	sprintf(temp,"ctm%s_TopHand.png",bodyName);
    m_Texture[16] = new MonkeyTextureObject(temp,spritesheet);
    RHand->SetUserData(m_Texture[16]);

    s_Monkey = this;
}
Monkey::~Monkey()
{
	for(int i = 0; i < 17; i++)
	{
		delete m_Texture[i];
	}
    s_Monkey = NULL;
    s_RandomXVel = 0.0f;
    s_RandomYVel = 0.0f;
}
void Monkey::SetVelocity(b2Vec2 velocity)
{
	for(int i = 0; i < 17; i++)
	{
        if(s_RandomXVel > 0.0f || s_RandomYVel > 0.0f)
        {
            b2Vec2 newVel;
            //newVel.x = RandomFloat(-s_RandomXVel, s_RandomXVel) + velocity.x;
            //newVel.y = RandomFloat(-s_RandomYVel, s_RandomYVel) + velocity.y;
            allPieces[i]->SetLinearVelocity(newVel);
        }
        else
        {
            allPieces[i]->SetLinearVelocity(velocity);
        }
	}
}
