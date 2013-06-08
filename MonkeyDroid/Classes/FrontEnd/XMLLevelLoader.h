//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __XML_LEVEL_LOADER_H__
#define __XML_LEVEL_LOADER_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "../Level/Track.h"

class XMLLevelLoader : public cocos2d::CCSAXDelegator
{
public:
    virtual ~XMLLevelLoader();
    XMLLevelLoader(b2World *world, cocos2d::CCNode *layer, cocos2d::CCNode *frontLayer, cocos2d::CCNode *backLayer);
    
    bool parseXMLFile(const char *xmlFilename);    

    // implement pure virtual methods of CCSAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    Track *getTrack();
protected:
    enum
    {
        POSX = 0,
        POSY = 1,
        CLASS = 2,
        MEDAL_LOCK = 3,
        MEDAL_MAX = 4,
        SORT = 5,
        ROTATION = 6,
        TRIGGER = 7,
        OFFTRIGGER = 8,
        TRIGGER_ID = 9,
        MIN = 10,
        MAX = 11,
        SPEED = 12,
        TEXTURE = 13,
        SEGMENTS = 14,
        XOFFSET = 15,
        YOFFSET = 16,
        VERSION = 17,
    };
    char objClass[64];
    char texName[64];
    int version;
    int medalLock;
    int medalMax;
    int sort;
    int trigger;
    int triggerID;
    int offtrigger;
    int segments;
    float xpos;
    float ypos;
    float xoffset;
    float yoffset;
    float rotation;
    float min;
    float max;
    float speed;
    int m_Type;
    float xObjectoffset;
    float yObjectoffset;

    Track* m_Track;
    b2World *m_world;
    cocos2d::CCNode *m_layer;
    cocos2d::CCNode *m_frontLayer;
    cocos2d::CCNode *m_backLayer;
    cocos2d::CCNode *m_spritesheet;
    void startObject();
    void finishObject();
};

#endif // __HELLO_WORLD_H__
