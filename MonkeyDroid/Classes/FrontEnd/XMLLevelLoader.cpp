//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "XMLLevelLoader.h"
#include "../Level/Objects/Ramp.h"
#include "../Level/Objects/TurboStrip.h"
#include "../Level/Objects/Platform.h"
#include "../Level/Objects/SpawnPoint.h"
#include "../Level/Objects/FinishLine.h"
#include "../Level/Objects/Trampoline.h"
#include "../Level/Objects/Bridge.h"
#include "../Level/Objects/Barrier.h"
#include "../Level/Objects/AirBoost.h"
#include "../Level/Objects/Porcupine.h"
#include "../Level/Objects/RotatingAirBoost.h"
#include "../Level/Objects/Kittens.h"
#include "../Level/Objects/ExplodingBarrel.h"
#include "../Level/Objects/Crate.h"
#include "../Level/Objects/Trigger.h"
#include "../Level/Objects/Pickup.h"
#include "../Level/Objects/Swing.h"
#include "../Level/Objects/ManHole.h"
#include "../Level/Objects/SpaceOrb.h"
#include "../Level/Objects/SingleLoop.h"
#include "../Level/Objects/DoubleLoop.h"
#include "../Level/Objects/TripleLoop.h"
#include "../Level/Objects/WaterTank.h"
#include "../Level/Objects/TutorialManager1.h"
#include "../Level/Objects/TutorialManager2.h"
#include "../Level/Objects/TutorialManager3.h"
#include "../Level/Objects/TutorialManager4.h"
#include "../Level/Objects/TutorialManager5.h"
#include "../Level/Objects/TutorialManager6.h"
#include "../Level/Objects/TutorialManager7.h"
#include "../Level/Objects/TutorialManager8.h"





using namespace cocos2d;

XMLLevelLoader::XMLLevelLoader(b2World *world, CCNode *layer, CCNode *frontLayer, CCNode *backLayer)
{
    m_world = world;
    m_layer =  layer;
    m_frontLayer =  frontLayer;
    m_backLayer =  backLayer;
    m_spritesheet = CCSpriteBatchNode::create("ctm_Objects.png");
    m_layer->addChild(m_spritesheet);
    m_Track = new Track(m_world,(CCLayer*)m_layer,(CCLayer*)m_frontLayer);
}
XMLLevelLoader::~XMLLevelLoader()
{
}
Track *XMLLevelLoader::getTrack()
{
    return m_Track;
}

bool XMLLevelLoader::parseXMLFile(const char *xmlFilename)
{
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    xObjectoffset = 0.0f;
    yObjectoffset = 0.0f;

    return parser.parse(xmlFilename);
}

void XMLLevelLoader::startElement(void *ctx, const char *name, const char **atts)
{
    //CCLOG("start %s",name);
    
    if(strcmp("Object",name)==0)
    {
        startObject();
    }
    else if (strcmp("class",name)==0)
    {
        m_Type = CLASS;
    }
    else if (strcmp("medalLock",name)==0)
    {
        m_Type = MEDAL_LOCK;
    }
    else if (strcmp("medalMax",name)==0)
    {
        m_Type = MEDAL_MAX;
    }
    else if (strcmp("positionx",name)==0)
    {
        m_Type = POSX;
    }
    else if (strcmp("positiony",name)==0)
    {
        m_Type = POSY;
    }
    else if (strcmp("sort",name)==0)
    {
        m_Type = SORT;        
    }
    else if (strcmp("rotation",name)==0)
    {
        m_Type = ROTATION;
    }
    else if (strcmp("trigger",name)==0)
    {
        m_Type = TRIGGER;
    }
    else if (strcmp("offtrigger",name)==0)
    {
        m_Type = OFFTRIGGER;
    }
    else if (strcmp("triggerID",name)==0)
    {
        m_Type = TRIGGER_ID;
    }
    else if (strcmp("min",name)==0)
    {
        m_Type = MIN;
    }
    else if (strcmp("max",name)==0)
    {
        m_Type = MAX;
    }
    else if (strcmp("speed",name)==0)
    {
        m_Type = SPEED;
    }
    else if (strcmp("version",name)==0)
    {
        m_Type = VERSION;
    }
    else if (strcmp("texture",name)==0)
    {
        m_Type = TEXTURE;
    }
    else if (strcmp("segments",name)==0)
    {
        m_Type = SEGMENTS;
    }
    else if (strcmp("xoffset",name)==0)
    {
        m_Type = XOFFSET;
    }
    else if (strcmp("yoffset",name)==0)
    {
        m_Type = YOFFSET;
    }
    else
    {
        m_Type = -1;
    }
}
void XMLLevelLoader::endElement(void *ctx, const char *name)
{
    //CCLOG("end %s",name);
    
    if(strcmp("Object",name)==0)
    {
        finishObject();
    }
}
void XMLLevelLoader::textHandler(void *ctx, const char *ch, int len)
{
    if(isspace(ch[0]))return;
    
    char temp[256];
    for(int i = 0; i < len; i++)
    {
        temp[i] = ch[i];
    }
    temp[len] = '\0';
    //CCLOG("handler %s",temp);
    switch(m_Type)
    {
        default:
            break;
        case POSX:
            xpos = atof(temp);
            break;
        case POSY:
            ypos = atof(temp);
            break;
        case CLASS:
            sprintf(objClass,"%s",temp);
            break;
        case MEDAL_LOCK:
            medalLock = atoi(temp);
            break;
        case MEDAL_MAX:
            medalMax = atoi(temp);
            break;
        case SORT:
            sort = atoi(temp);
            break;
        case ROTATION:
            rotation = atof(temp);
            break;
        case TRIGGER:
            trigger = atoi(temp);
            break;
        case OFFTRIGGER:
            offtrigger = atoi(temp);
            break;
        case TRIGGER_ID:
            triggerID = atoi(temp);
            break;
        case MIN:
            min = atof(temp);
            break;
        case MAX:
            max = atof(temp);
            break;
        case SPEED:
            speed = atof(temp);
            break;
        case TEXTURE:
            sprintf(texName,"%s",temp);
            break;
        case SEGMENTS:
            segments = atoi(temp);
            break;
        case XOFFSET:
            xoffset = atof(temp);
            break;
        case YOFFSET:
            yoffset = atof(temp);
            break;
        case VERSION:
            version = atoi(temp);
            break;
    }
}

void XMLLevelLoader::startObject()
{
    objClass[0] = '\0';
    texName[0] = '\0';
    version = 0;
    medalLock = 0;
    medalMax = 0;
    sort = 0;
    trigger = 0;
    triggerID = 0;
    offtrigger = 0;
    segments = 10;
    xpos = 0.0f;
    ypos = 0.0f;
    xoffset = 0.0f;
    yoffset = 0.0f;
    rotation = 0.0f;
    min = 0.0f;
    max = 0.0f;
    speed = 0.0f;

    m_Type = 0;
}
void XMLLevelLoader::finishObject()
{
    if(strcmp(objClass,"ObjectOffset")==0)
    {
        xObjectoffset = xpos;
        yObjectoffset = ypos;
    }
    else if(strcmp(objClass,"TurboStrip")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new TurboStrip(m_world,m_spritesheet,&pos,1.0f));
    }
    else if(strcmp(objClass,"RevTurboStrip")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new TurboStrip(m_world,m_spritesheet,&pos,1.0f,true));
    }
    else if(strcmp(objClass,"Ramp")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::ORIGINAL,sort));
    }
    else if(strcmp(objClass, "TopRampFWD")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_FWD,sort));
    }
    else if(strcmp(objClass, "TopRampFWDLow")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_FWD_LOW,sort));
    }
    else if(strcmp(objClass, "TopRampFWDSteep")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_FWD_STEEP,sort));
    }
    else if(strcmp(objClass, "TopRampREV")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_REV,sort));
    }
    else if(strcmp(objClass, "TopRampREVLow")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_REV_LOW,sort));
    }
    else if(strcmp(objClass, "TopRampREVSteep")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::TOP_REV_STEEP,sort));
    }
    else if(strcmp(objClass, "RampFWD")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::FWD,sort));
    }
    else if(strcmp(objClass, "RampFWDLow")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::FWD_LOW,sort));
    }
    else if(strcmp(objClass, "RampFWDSteep")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::FWD_STEEP,sort));
    }
    else if(strcmp(objClass, "RampREV")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::REV,sort));
    }
    else if(strcmp(objClass, "RampREVLow")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::REV_LOW,sort));
    }
    else if(strcmp(objClass, "RampREVSteep")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::REV_STEEP,sort));
    }
    else if(strcmp(objClass, "RampArchSmall")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::ARCH_SMALL,sort));
    }
    else if(strcmp(objClass, "RampWallFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Ramp(m_world,m_spritesheet,&pos,Ramp::WALL_FRONT,m_frontLayer,sort));
    }
    else if(strcmp(objClass, "RampWallBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::BACK_WALL_RAMP,sort));
    }
    else if(strcmp(objClass, "PlatformLong")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::LONG,m_backLayer,sort));
    }
    else if(strcmp(objClass, "PlatformShort")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::SHORT,m_backLayer,sort));
    }
    else if(strcmp(objClass, "BlueCarBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::BLUE_CAR_BACK,sort));
    }
    else if(strcmp(objClass, "OrangeCarBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::ORANGE_CAR_BACK,sort));
    }
    else if(strcmp(objClass, "HotDogBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HOT_DOG_BACK,sort));
    }
    else if(strcmp(objClass, "HighWall")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HIGH_WALL,sort));
    }
    else if(strcmp(objClass, "HighWall2")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HIGH_WALL2,sort));
    }
    else if(strcmp(objClass, "HighWall3")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HIGH_WALL3,sort));
    }
    else if(strcmp(objClass, "MailTruckBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::MAIL_TRUCK_BACK,sort));
    }
    else if(strcmp(objClass, "PoliceBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::POLICE_BACK,sort));
    }
    else if(strcmp(objClass, "TaxiBack")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::TAXI_BACK,sort));
    }
    else if(strcmp(objClass, "SchoolBusLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::SCHOOLBUS_LEFT,sort));
    }
    else if(strcmp(objClass, "SemiTruckLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::SEMITRUCK_LEFT,sort));
    }
    else if(strcmp(objClass, "BlueCarLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::BLUE_CAR_LEFT,sort));
    }
    else if(strcmp(objClass, "OrangeCarLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::ORANGE_CAR_LEFT,sort));
    }
    else if(strcmp(objClass, "HotDogLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HOT_DOG_LEFT,sort));
    }
    else if(strcmp(objClass, "MailTruckLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::MAIL_TRUCK_LEFT,sort));
    }
    else if(strcmp(objClass, "PoliceLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::POLICE_LEFT,sort));
    }
    else if(strcmp(objClass, "TaxiLeft")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::TAXI_LEFT,sort));
    }
    else if(strcmp(objClass, "BlueCarFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::BLUE_CAR_FRONT,sort));
    }
    else if(strcmp(objClass, "OrangeCarFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::ORANGE_CAR_FRONT,sort));
    }
    else if(strcmp(objClass, "HotDogFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HOT_DOG_FRONT,sort));
    }
    else if(strcmp(objClass, "MailTruckFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::MAIL_TRUCK_FRONT,sort));
    }
    else if(strcmp(objClass, "PoliceFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::POLICE_FRONT,sort));
    }
    else if(strcmp(objClass, "TaxiFront")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::TAXI_FRONT,sort));
    }
    else if(strcmp(objClass, "SchoolBusRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::SCHOOLBUS_RIGHT,sort));
    }
    else if(strcmp(objClass, "SemiTruckRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::SEMITRUCK_RIGHT,sort));
    }
    else if(strcmp(objClass, "BlueCarRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::BLUE_CAR_RIGHT,sort));
    }
    else if(strcmp(objClass, "OrangeCarRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::ORANGE_CAR_RIGHT,sort));
    }
    else if(strcmp(objClass, "HotDogRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::HOT_DOG_RIGHT,sort));
    }
    else if(strcmp(objClass, "MailTruckRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::MAIL_TRUCK_RIGHT,sort));
    }
    else if(strcmp(objClass, "PoliceRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::POLICE_RIGHT,sort));
    }
    else if(strcmp(objClass, "TaxiRight")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Platform(m_world,m_spritesheet,&pos,Platform::TAXI_RIGHT,sort));
    }
    else if(strcmp(objClass, "StartStrip")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new SpawnPoint(m_world,m_spritesheet,&pos,1.0f));
        Rider::g_startPos = pos;
    }
    else if(strcmp(objClass, "FinishLine")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new FinishLine(m_world,m_spritesheet,&pos,1.0f));
    }
    else if(strcmp(objClass, "Trampoline")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Trampoline(m_world,m_spritesheet,&pos,1.0f,version));
    }
    else if(strcmp(objClass, "Porcupine")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Porcupine(m_world,m_spritesheet,&pos,1.0f));
    }
    else if(strcmp(objClass, "Barrier")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Barrier(m_world,m_spritesheet,m_frontLayer,&pos,false));
    }
    else if(strcmp(objClass, "Bridge")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Bridge(m_world,m_spritesheet,m_Track->GetMainCollision(),&pos,segments,xoffset,yoffset,sort));
    }
    else if(strcmp(objClass, "AirBoost")==0)
    {
        rotation = (rotation * b2_pi/180.0f);
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new AirBoost(m_world,m_spritesheet,&pos,rotation));
    }
    else if(strcmp(objClass, "RotatingAirBoost")==0)
    {
        speed = (speed * b2_pi/180.0f);
        min = (min * b2_pi/180.0f);
        max = (max * b2_pi/180.0f);
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new RotatingAirBoost(m_world,m_layer,&pos,min,max,speed));
    }
    else if(strcmp(objClass, "ExplodingBarrel")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new ExplodingBarrel(m_world,m_spritesheet,&pos,1.0f));
    }
    else if(strcmp(objClass, "Kittens")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Kittens(m_world,m_spritesheet,m_frontLayer,&pos,Kittens::KITTENS));
    }
    else if(strcmp(objClass, "Cows")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Kittens(m_world,m_spritesheet,m_frontLayer,&pos,Kittens::COWS));
    }
    else if(strcmp(objClass, "Chickens")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Kittens(m_world,m_spritesheet,m_frontLayer,&pos,Kittens::CHICKENS));
    }
    else if(strcmp(objClass, "Crate")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Crate(m_world,m_spritesheet,&pos,1.0f));
    }
    else if(strcmp(objClass, "Beachball")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Crate(m_world,m_frontLayer,&pos,Crate::BEACH_BALL,3));
    }
    else if(strcmp(objClass, "Trigger")==0)
    {
        if (triggerID > 0)
        {
            triggerID = 1<<(triggerID-1);
        }
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Trigger(m_world,m_spritesheet,&pos,triggerID));
    }
    else if(strcmp(objClass, "TimePickup")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Pickup(m_world,m_spritesheet,&pos,Pickup::TIME));
    }
    else if(strcmp(objClass, "PeanutPickup")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Pickup(m_world,m_spritesheet,&pos,Pickup::PEANUT));
    }
    else if(strcmp(objClass, "FirePickup")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Pickup(m_world,m_spritesheet,&pos,Pickup::FIRE));
    }
    else if(strcmp(objClass, "ManHole")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new ManHole(m_world,m_spritesheet,m_frontLayer,&pos));
    }
    else if(strcmp(objClass, "SpaceOrb")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new SpaceOrb(m_world,m_spritesheet,m_frontLayer,&pos));
    }
    else if(strcmp(objClass, "Swing")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new Swing(m_world,m_frontLayer,&pos,5));
    }
    else if(strcmp(objClass, "SingleLoop")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new SingleLoop(m_world,m_spritesheet,(CCLayer*)m_frontLayer,&pos));
    }
    else if(strcmp(objClass, "DoubleLoop")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new DoubleLoop(m_world,m_spritesheet,(CCLayer*)m_frontLayer,&pos));
    }
    else if(strcmp(objClass, "TripleLoop")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new TripleLoop(m_world,m_spritesheet,(CCLayer*)m_frontLayer,&pos));
    }
    else if(strcmp(objClass, "SharkWaterTank")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new WaterTank(m_world,m_spritesheet,m_frontLayer,&pos,WaterTank::SHARK));
    }
    else if(strcmp(objClass, "AcidWaterTank")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new WaterTank(m_world,m_spritesheet,m_frontLayer,&pos,WaterTank::ACID));
    }
    else if(strcmp(objClass, "SpaceWaterTank")==0)
    {
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        m_Track->AddObject(new WaterTank(m_world,m_spritesheet,m_frontLayer,&pos,WaterTank::SPACE));
    }
    else if(strcmp(objClass, "TutorialManager")==0)
    {
        
        b2Vec2 pos(xpos+xObjectoffset,ypos+yObjectoffset);
        switch(version)
        {
            default:
                m_Track->AddObject(new TutorialManager1(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 1:
                m_Track->AddObject(new TutorialManager1(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 2:
                m_Track->AddObject(new TutorialManager2(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 3:
                m_Track->AddObject(new TutorialManager3(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 4:
                m_Track->AddObject(new TutorialManager4(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 5:
                m_Track->AddObject(new TutorialManager5(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 6:
                m_Track->AddObject(new TutorialManager6(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 7:
                m_Track->AddObject(new TutorialManager7(m_Track,m_spritesheet,m_world,&pos));
                break;
            case 8:
                m_Track->AddObject(new TutorialManager8(m_Track,m_spritesheet,m_world,&pos));
                break;
        }
    }
    
    
    if(m_Track->GetCurrent() != NULL)
    {
        if(strcmp(objClass,"ObjectOffset")!=0)
        {
            if (trigger > 0)
            {
                trigger = 1<<(trigger-1);
            }
            if (offtrigger > 0)
            {
                offtrigger = 1<<(offtrigger-1);
            }
            m_Track->GetCurrent()->m_trigger = trigger;
            m_Track->GetCurrent()->m_offtrigger = offtrigger;
        }
    }
}
