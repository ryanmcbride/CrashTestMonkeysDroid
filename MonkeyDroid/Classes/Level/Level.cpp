//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Level.h"
#include "SimpleAudioEngine.h"
#include "../FrontEnd/MainMenu.h"
#include "../ScreenHelper.h"
#include "../FrontEnd/LevelSelect.h"
#include "../FrontEnd/XMLLevelLoader.h"
#include "HUD.h"
#include "../FrontEnd/Pause.h"
#include "Rider/Rider.h"
#include "BackGrounds/BackGround.h"
#include "../AudioManager.h"
#include "Objects/Pickup.h"

using namespace cocos2d;
using namespace CocosDenshion;
float g_DeltaTime;
bool g_is60 = true;
bool g_bIsRetina = true;
int g_TutorialState = 0;
bool g_2XPeanuts = false;
bool g_PermanentFire = false;
bool g_SlowClock = false;

class DebugDrawLayer : public CCLayer
{
public:
    virtual ~DebugDrawLayer(){delete m_debugDraw;}
    DebugDrawLayer(b2World *world, CCLayer* layer)
    {
        m_debugDraw = new GLESDebugDraw( PTM_RATIO );
        world->SetDebugDraw(m_debugDraw);
        
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        //        flags += b2Draw::e_jointBit;
        //        flags += b2Draw::e_aabbBit;
        //        flags += b2Draw::e_pairBit;
        //        flags += b2Draw::e_centerOfMassBit;
        m_debugDraw->SetFlags(flags);
        m_world = world;
        m_layer = layer;
    }
    
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene(b2World *world);
    
    virtual void draw()
    {
        float zoom = PTM_RATIO;
        
        //if(Rider::g_MainBody->GetPosition().y>5.0f)
        {
            zoom *= ScreenHelper::getCameraZoom();
        }
        m_debugDraw->mRatio = zoom;
        //
        // IMPORTANT:
        // This is only for debug purposes
        // It is recommend to disable it
        //
        CCLayer::draw();
        
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
        
        kmGLPushMatrix();
        
        m_world->DrawDebugData();
        
        kmGLPopMatrix();

    }
    
protected:
    CCLayer *m_layer;
    b2World *m_world;
    GLESDebugDraw *m_debugDraw;
};

#define MIDDLE_LAYER 69
#define BIKE_LAYER 70

Level *Level::Me = NULL;
float Level::m_ShakeDuration = 0.0f;
float Level::m_ShakeMagnitude = 0.0f;
float Level::m_ShakeSpeed = 0.0f;

void Level::ScreenShake(float duration, float magnitude, float speed)
{
    m_ShakeDuration = duration;
    m_ShakeMagnitude = magnitude;
    m_ShakeSpeed = speed;
}

Level::Level()
{
    Me = this;
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    CCLayer *backLayer = CCLayer::create();
    CCLayer *frontLayer = CCLayer::create();
    CCLayer *middleLayer = CCLayer::create();
    CCLayer *objectLayer = CCLayer::create();
    CCLayer *bikeLayer = CCLayer::create();
    middleLayer->addChild(objectLayer,2);
    middleLayer->addChild(bikeLayer,3,BIKE_LAYER);
    addChild(backLayer,-1);
    addChild(middleLayer,1,MIDDLE_LAYER);
    addChild(frontLayer,10);
    
    m_BackGround = BackGround::create(backLayer);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Objects.plist");
    
    XMLLevelLoader loader(world,objectLayer,frontLayer,backLayer);
    
    loader.parseXMLFile(LevelSelect::getLevelXMLName());
    
    m_Track = loader.getTrack();
    
    //m_Track = new Track(world,middleLayer,frontLayer);
    
    m_DebugDraw = NULL;
    
    Pickup::InitLevelPickups();
    ScreenHelper::setCameraZoom(1.0f,false);
    
    m_ZoomedOut = false;
    m_idleTime = 5.0f;

    
    scheduleUpdate();
}
Level::~Level()
{
    if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    Pickup::DestroyLevelPickups();
    m_BackGround->release();
    Me = NULL;
    delete m_Rider;
    m_Rider = NULL;
    delete m_Track;
    m_Track = NULL;
    delete world;
    world = NULL;
    delete m_Listener;
}

void Level::FinalizeLevel()
{
    CCNode *bikelayer = getChildByTag(MIDDLE_LAYER)->getChildByTag(BIKE_LAYER);
    m_Rider = new Rider(world,bikelayer);
    
    m_Listener = new LevelContactListener();
    world->SetContactListener(m_Listener);
    m_Listener->AddListener(m_Rider);
    m_Listener->AddListener(m_Track);
    
    ((HUD*)m_HUD)->SetRider(m_Rider);
    
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMIslandMusic.3gp", true);

}

void Level::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    if(Rider::g_isCrashed)
        ((HUD*)m_HUD)->startCrashSequence();
    if(Rider::g_isFinished)
        ((HUD*)m_HUD)->startFinishSequence();
    
    if(!Pause::s_bIsPaused)
	{
        if(!(Rider::g_isCrashed || Rider::g_isFinished))
        {
            float zoom = ScreenHelper::getCameraZoom();
            float playerVel = Rider::g_MainBody->GetLinearVelocity().Length();
            if(playerVel > 5.0f)
            {
                zoom = 0.8f;
                m_idleTime = 0.0f;
            }
            else
                m_idleTime += dt;
            if(m_idleTime > 5.0f)
                zoom = 1.0f;
            
            ScreenHelper::setCameraZoom(zoom);
        }
        
        float cameraZoom = ScreenHelper::getCameraZoom();
        
        
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		
		
        //int loops = 6;
        //float dtDivide = 4.0f;
        //dt = 1.0f/30.0f;
        
        //if(g_is60)
        //{
        if(dt > 1.0f/30.0f)
            dt = 1.0f/30.0f;
        int loops = 3;
        float dtDivide = 2.0f;
        //}
		g_DeltaTime = dt;
        
        for(int i = 0; i < loops; i++)
		{
            if(i==(loops-1))
            {
                b2Vec2 carPos;
                m_Rider->GetCameraPosition(carPos);
                m_Track->Step(carPos.x,carPos.y);
                m_Rider->GetCameraPosition(carPos);
                
                m_BackGround->Step(carPos.x*cameraZoom,carPos.y*cameraZoom);
                
                
                if(m_ShakeDuration > 0.0f)
                {
                    carPos.x += RandomFloat(-m_ShakeMagnitude, m_ShakeMagnitude);
                    carPos.y += RandomFloat(-m_ShakeMagnitude, m_ShakeMagnitude);
                    m_ShakeDuration -= dt;
                }
                
                float targetX,targetY,targetZ;
                float eyetargetX,eyetargetY,eyetargetZ;
                
                getCamera()->getCenterXYZ(&targetX, &targetY, &targetZ);
                getCamera()->getEyeXYZ(&eyetargetX, &eyetargetY, &eyetargetZ);
                
                getCamera()->setCenterXYZ(carPos.x*cameraZoom, carPos.y*cameraZoom, 0.0f);
                getCamera()->setEyeXYZ(carPos.x*cameraZoom, carPos.y*cameraZoom, 10.0f);
                
                if(m_DebugDraw)
                {
                    m_DebugDraw->getCamera()->setCenterXYZ(carPos.x*cameraZoom, carPos.y*cameraZoom, 0.0f);
                    m_DebugDraw->getCamera()->setEyeXYZ(carPos.x*cameraZoom, carPos.y*cameraZoom, 10.0f);
                }
                
                //Iterate over the bodies in the physics world
                for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
                {
                    if (b->GetUserData() != NULL)
                    {
                        ((TextureObject*)b->GetUserData())->Draw(b);
                    }
                }
/*                if(!g_is60 && i == 2)
                {
                    m_Rider->GasAndBrake(m_LastGas);
                }
 */
            }
            
            m_Rider->Step(2);
            
			// Instruct the world to perform a single step of simulation. It is
			// generally best to keep the time step and iterations fixed.
			world->Step(dt/dtDivide, velocityIterations, positionIterations);
        }
        //centerMarker.position = ccp(m_Rider->g_MainBody->GetWorldCenter().x*PTM_RATIO,m_Rider->g_MainBody->GetWorldCenter().y*PTM_RATIO);
	}
    if(Rider::g_BikeAudio)
    {
        Rider::g_BikeAudio->Pause(Pause::s_bIsPaused);
        
        if(!Pause::s_bIsPaused)
            Rider::g_BikeAudio->Update(dt);
    }
    AudioManager::UpdateAudio(dt);
}
CCScene* Level::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    Level* level = new Level();
    
    
    level->m_HUD = new HUD();
    
    
    //level->m_DebugDraw = new DebugDrawLayer(level->world,level);
    
    
    scene->addChild(level);
    if(level->m_DebugDraw)
        scene->addChild(level->m_DebugDraw);
    scene->addChild(level->m_HUD);
    
    level->FinalizeLevel();
    
    level->release();
    if(level->m_DebugDraw)
        level->m_DebugDraw->release();
    level->m_HUD->release();
    
    CCTextureCache::sharedTextureCache()->addImageAsync("ctm_WinScreen.pvr.ccz",NULL,NULL);
    CCTextureCache::sharedTextureCache()->addImageAsync("particleTexture.png",NULL,NULL);
    return scene;
}
