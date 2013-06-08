//
//  Pickup.mm
//  CTM
//
//  Created by Ryan McBride on 1/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

//
//  TurboStrip.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Pickup.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../Level.h"
#include "../../ScreenHelper.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../../AudioManager.h"

extern bool g_2XPeanuts;

using namespace cocos2d;

CCRotateRandom *CCRotateRandom::create(float one, float tow)
{
    return NULL;
}
/*@implementation CCRotateRandom
+(id) actionWithDuration: (ccTime) t angle:(float) a
{
	return [[[self alloc] initWithDuration:t angle:a ] autorelease];
}

-(id) initWithDuration: (ccTime) t angle:(float) a
{
	if( (self=[super initWithDuration: t]) )
		angle = a;
	
	return self;
}

-(id) copyWithZone: (NSZone*) zone
{
	CCAction *copy = [[[self class] allocWithZone: zone] initWithDuration: [self duration] angle: angle];
	return copy;
}

-(void) startWithTarget:(id)aTarget
{
	[super startWithTarget:aTarget];
	startAngle = [target_ rotation];
}

-(void) update: (ccTime) t
{
	// XXX: shall I add % 360
	[target_ setRotation: RandomFloat(0.0f, 360.0f)];
}

-(CCActionInterval*) reverse
{
	return [[self class] actionWithDuration:duration_ angle:-angle];
}

@end*/

CCSprite *Pickup::m_SpriteCache[50];
CCSprite *Pickup::m_BigSpriteCache[50];
int Pickup::m_SpriteCacheCount = 0;
int Pickup::m_BigSpriteCacheCount = 0;
static bool s_bPickupPoolCreated = false;

void Pickup::InitLevelPickups()
{
    if(s_bPickupPoolCreated)
        DestroyLevelPickups();
    int index = 0;
    char tempName[64];
    for(int j = 0; j < 10; j++)
    {
        for(int i = 1; i <= 5; i++)
        {
            sprintf(tempName, "ctm_glowRing_SmallPop_%03d.png",i);
            CCSprite *pop = CCSprite::createWithSpriteFrameName(tempName);
            pop->retain();
            pop->setScale(0.5f);
            m_SpriteCache[index] = pop;
            index++;
        }
    }
    index = 0;
    for(int j = 0; j < 10; j++)
    {
        for(int i = 1; i <= 5; i++)
        {
            sprintf(tempName, "ctm_glowRing_Pop_%03d.png",i);
            CCSprite *pop = CCSprite::createWithSpriteFrameName(tempName);
            pop->retain();
            m_BigSpriteCache[index] = pop;
            index++;
        }
    }
    m_SpriteCacheCount = 0;
    m_BigSpriteCacheCount = 0;
    s_bPickupPoolCreated = true;
}
void Pickup::DestroyLevelPickups()
{
    for(int i = 0; i < 50; i++)
    {
        m_BigSpriteCache[i]->release();
        m_BigSpriteCache[i] = NULL;
        m_SpriteCache[i]->release();
        m_SpriteCache[i] = NULL;
    }
    s_bPickupPoolCreated = false;
}


Pickup::Pickup(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_bPickedUp = false;
    m_Type = PEANUT;
    m_vfxTime = 0.0f;
    m_popInStagger = RandomFloat(-2.0f, 2.0f);
    for(int i = 0; i < 5; i++)
    {
        m_Popsprite[i] = NULL;
    }
}
Pickup::Pickup(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type itype):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_bPickedUp = false;
    m_Type = itype;
    m_vfxTime = 0.0f;
    m_popInStagger = RandomFloat(-2.0f, 2.0f);
    for(int i = 0; i < 5; i++)
    {
        m_Popsprite[i] = NULL;
    }
    if(m_Type==TIME && SaveLoad::m_SaveData.timeLockLevel==0)
    {
        m_bPickedUp = true;
    }
    if(m_Type==FIRE && SaveLoad::m_SaveData.fireLockLevel==0)
    {
        m_bPickedUp = true;
    }
}
Pickup::~Pickup()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
bool Pickup::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created || m_bPickedUp) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(myFixture == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(myFixture == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;

        DoPickup();
		return false;
	}
	return false;
}
void Pickup::DoPickupVFX()
{
    if(!m_MainCollision)return;

    int i;
    float zoom = ScreenHelper::getCameraZoom();
    
    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();

    
    for(i = 1; i <= 5; i++)
    {
        CCSprite *pop = m_SpriteCache[m_SpriteCacheCount*5+(i-1)];
        if(pop->getParent() == NULL)
        {
            m_ccLayer->addChild(pop,3,100+i);
        
            pop->setPosition(texObject->GetSprite()->getPosition());
            pop->setOpacity(0);

            m_Popsprite[i-1] = pop;
            m_PopspritePoint[i-1] = ccp(texObject->GetSprite()->getPosition().x/zoom,texObject->GetSprite()->getPosition().y/zoom);
        }
        else
        {
            pop->removeFromParentAndCleanup(false);
        }
    }
    m_SpriteCacheCount++;
    if(m_SpriteCacheCount>=10)
        m_SpriteCacheCount = 0;
}
void Pickup::DoPickupVFXBig()
{
    if(!m_MainCollision)return;

    float zoom = ScreenHelper::getCameraZoom();

    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
    
    for(int i = 1; i <= 5; i++)
    {
        CCSprite *pop = m_BigSpriteCache[m_BigSpriteCacheCount*5+(i-1)];
        if(pop->getParent() == NULL)
        {
            m_ccLayer->addChild(pop,3,100+i);
        
            pop->setPosition(texObject->GetSprite()->getPosition());
            pop->setOpacity(0);
            m_Popsprite[i-1] = pop;
            m_PopspritePoint[i-1] = ccp(texObject->GetSprite()->getPosition().x/zoom,texObject->GetSprite()->getPosition().y/zoom);
        }
        else
        {
            pop->removeFromParentAndCleanup(false);
        }
    }
    m_BigSpriteCacheCount++;
    if(m_BigSpriteCacheCount>=10)
        m_BigSpriteCacheCount = 0;

}
void Pickup::DoPickup()
{
    if(Rider::g_isCrashed)
        return;
    
    switch(m_Type)
    {
        default:
        case PEANUT:
        {
            if(g_2XPeanuts)
            {
                if(SaveLoad::m_SaveData.peanutLockLevel==0)
                    Rider::g_Pickups += 2;
                if(SaveLoad::m_SaveData.peanutLockLevel==1)
                    Rider::g_Pickups += 4;
                if(SaveLoad::m_SaveData.peanutLockLevel==2)
                    Rider::g_Pickups += 6;
                if(SaveLoad::m_SaveData.peanutLockLevel==3)
                    Rider::g_Pickups += 10;
                DoPickupVFXBig();
            }
            else
            {
                if(SaveLoad::m_SaveData.peanutLockLevel==0)
                    Rider::g_Pickups += 1;
                if(SaveLoad::m_SaveData.peanutLockLevel==1)
                    Rider::g_Pickups += 2;
                if(SaveLoad::m_SaveData.peanutLockLevel==2)
                    Rider::g_Pickups += 3;
                if(SaveLoad::m_SaveData.peanutLockLevel==3)
                    Rider::g_Pickups += 5;
                DoPickupVFX();
            }
            AudioManager::PlayEffect(AUDIO_COLLECT_ITEM);
        }
            break;
        case FIRE:
            if(SaveLoad::m_SaveData.fireLockLevel==1)
                Rider::g_OnFire = 5.0f;
            if(SaveLoad::m_SaveData.fireLockLevel==2)
                Rider::g_OnFire = 10.0f;
            if(SaveLoad::m_SaveData.fireLockLevel==3)
                Rider::g_OnFire = 20.0f;
            
            AudioManager::PlayEffect(AUDIO_COLLECT_ITEM);
            DoPickupVFX();
            break;
        case TIME:
        {
/*            if(SaveLoad::m_SaveData.timeLockLevel==0)
                [GameHUD SubtractTime:1.0f];
            if(SaveLoad::m_SaveData.timeLockLevel==1)
                [GameHUD SubtractTime:2.0f];
            if(SaveLoad::m_SaveData.timeLockLevel==2)
                [GameHUD SubtractTime:3.0f];
            if(SaveLoad::m_SaveData.timeLockLevel==3)
                [GameHUD SubtractTime:5.0f];*/
            AudioManager::PlayEffect(AUDIO_COLLECT_ITEM);
            DoPickupVFX();
        }
            break;
/*        case FIRE_WORKS:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case RED_SMOKE:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case WHITE_SMOKE:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case BLUE_SMOKE:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case TRICK1:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case TRICK2:
            [Rider::g_ScoreManager AddScore:50];
            break;
        case TRICK3:
            [Rider::g_ScoreManager AddScore:50];
            break;*/
    }
    
    m_bPickedUp = true;
    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
    texObject->GetSprite()->setVisible(false);
}
void Pickup::CreateSelf()
{
	if(m_created || m_bPickedUp) return;
	
    elec = NULL;
	m_created = true;

	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(15.0f/PTM_RATIO, 15.0f/PTM_RATIO);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0f);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex;
    switch(m_Type)
    {
        default:
        case PEANUT:
        {
            if(g_2XPeanuts)
            {
                tex = new TextureObject((char*)"ctm_Glow_Ring.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
                elec = CCSprite::createWithSpriteFrameName("ctm_Electric_Ring.png");
                elec->setPosition(ccp(28,28));
                tex->GetSprite()->addChild(elec);
            }
            else
            {
                tex = new TextureObject((char*)"ctm_Glow_Ringsmall_Peanut.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
            }
            CCSprite *peanut = CCSprite::createWithSpriteFrameName("ctm_Pickup_Peanut.png");
            peanut->setPosition(ccp(28,28));
            tex->GetSprite()->addChild(peanut);
            //"ctm_Pickup_Peanut.png"
        }
        break;
        case FIRE:
        {
            tex = new TextureObject((char*)"ctm_FireGlow_Ring.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
            //CCSprite *elec = [CCSprite spriteWithSpriteFrameName:@"ctm_FireRing.png"];
            //elec.position = ccp(28,28);
            //[elec runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCDelayTime actionWithDuration:0.05f],[CCRotateRandom actionWithDuration:1 angle:1], nil]]];
            CCSprite *peanut = CCSprite::createWithSpriteFrameName("ctm_Pickup_Fire.png");
            peanut->setPosition(ccp(28,28));
//            [tex->GetSprite() addChild:elec];
            tex->GetSprite()->addChild(peanut);
        }
            break;
        case TIME:
        {
            
            tex = new TextureObject((char*)"ctm_TimeGlow_Ring.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
            //CCSprite *elec = [CCSprite spriteWithSpriteFrameName:@"ctm_TimeRing.png"];
            //elec.position = ccp(28,28);
            //[elec runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCDelayTime actionWithDuration:0.05f],[CCRotateRandom actionWithDuration:1 angle:1], nil]]];
            CCSprite *peanut = CCSprite::createWithSpriteFrameName("ctm_Time_Pickup.png");
            peanut->setPosition(ccp(28,28));
//            [tex->GetSprite() addChild:elec];
            tex->GetSprite()->addChild(peanut);
            //"ctm_Pickup_Peanut.png"
        }
            break;
        case FIRE_WORKS:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case RED_SMOKE:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case WHITE_SMOKE:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case BLUE_SMOKE:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case TRICK1:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case TRICK2:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
        case TRICK3:
            tex = new TextureObject((char*)"ctm_Pickup_Coconut.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
            break;
    }
	m_MainCollision->SetUserData(tex);	
	tex->SetTexturePosition(m_StartPos.x, m_StartPos.y-1.0);
}
void Pickup::DestroySelf()
{
	if(m_created)
	{
        if(elec)
            elec = NULL;
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}
bool Pickup::InRange(float xpos)
{
    if(TrackObject::InRange(xpos+m_popInStagger))
    {
        float riderY = Rider::g_MainBody->GetPosition().y;
        if((m_StartPos.y-riderY) > -20 && (m_StartPos.y-riderY) < 15)
            return true;
    }
    return false;
}
void Pickup::Update(float xpos,float ypos)
{
	if(!m_created && InRange(xpos))
	{
		CreateSelf();
		return;
	}
	
    if(m_created && !InRange(xpos))
    {
		DestroySelf();
		m_created = false;
	    return;
	}
    else
    {
        if(!m_created) return;
        b2Vec2 pos = Rider::g_MainBody->GetPosition();
        pos.y -= 1.0f;
        if(!m_bPickedUp && (Rider::g_MainBody->GetPosition()-m_StartPos).LengthSquared() < 32.0f/PTM_RATIO)
            DoPickup();
        if(elec)
            elec->setRotation(RandomFloat(0.0f, 360.0f));
        
        float step = 0.05f;
        if(m_bPickedUp && m_vfxTime < (5.0f*step+0.01f))
        {
            float dt = (1.0f/60.0f);
            m_vfxTime += dt;
            
            
            if(m_vfxTime >= (5.0f*step+0.01f) && (m_vfxTime-dt) < (5.0f*step+0.01f))
            {
                if(m_Popsprite[4])
                    m_Popsprite[4]->removeFromParentAndCleanup(false);
                m_Popsprite[4] = NULL;
            }
            else if(m_vfxTime >= (4.0f*step+0.01f) && (m_vfxTime-dt) < (4.0f*step+0.01f))
            {
                if(m_Popsprite[4])
                    m_Popsprite[4]->setOpacity(255);
                if(m_Popsprite[3])
                    m_Popsprite[3]->removeFromParentAndCleanup(false);
                m_Popsprite[3] = NULL;
            }
            else if(m_vfxTime >= (3.0f*step+0.01f) && (m_vfxTime-dt) < (3.0f*step+0.01f))
            {
                if(m_Popsprite[3])
                    m_Popsprite[3]->setOpacity(255);
                if(m_Popsprite[2])
                    m_Popsprite[2]->removeFromParentAndCleanup(false);
                m_Popsprite[2] = NULL;
            }
            else if(m_vfxTime >= (2.0f*step+0.01f) && (m_vfxTime-dt) < (2.0f*step+0.01f))
            {
                if(m_Popsprite[2])
                    m_Popsprite[2]->setOpacity(255);
                if(m_Popsprite[1])
                    m_Popsprite[1]->removeFromParentAndCleanup(false);
                m_Popsprite[1] = NULL;
            }
            else if(m_vfxTime >= (1.0f*step+0.01f) && (m_vfxTime-dt) < (1.0f*step+0.01f))
            {
                if(m_Popsprite[1])
                    m_Popsprite[1]->setOpacity(255);
                if(m_Popsprite[0])
                    m_Popsprite[0]->removeFromParentAndCleanup(false);
                m_Popsprite[0] = NULL;
            }
            else if(m_vfxTime >= 0.01f && (m_vfxTime-dt) < 0.01f)
            {
                if(m_Popsprite[0])
                    m_Popsprite[0]->setOpacity(255);
            }
            for(int j = 0; j < 5; j++)
            {
                if(m_Popsprite[j])
                {
                    m_Popsprite[j]->setScale(ScreenHelper::getCameraZoom()*ScreenHelper::getTextureScale());
                    m_Popsprite[j]->setPosition(ccp(m_PopspritePoint[j].x*ScreenHelper::getCameraZoom(),m_PopspritePoint[j].y*ScreenHelper::getCameraZoom()));
                    break;
                }
            }
        }
    }
	
}

