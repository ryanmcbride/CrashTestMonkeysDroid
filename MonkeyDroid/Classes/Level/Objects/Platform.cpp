/*
 *  Ramp.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Platform.h"
#include "TextureObject.h"
#include "../../ScreenHelper.h"


using namespace cocos2d;

struct PlatformDef
{
	float yOffset;
    int verts;
	b2Vec2 points[8];
	char*	texturename;
};
static PlatformDef s_PlatformDefs[Platform::MAX_TYPES] = 
{
	{
		-11.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(120.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((120.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((120.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(120.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
		},
		(char*)"ctm_Platform_New_Long.png"
	},
	{
		-11.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(64.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((58.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((58.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(64.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Platform_New_Short.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_BlueCar_Back.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_2DoorCar_Orange_Front.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(35.0f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(40.0f/PTM_RATIO)),
			b2Vec2(-(35.0f/PTM_RATIO),(40.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_HotDog_Back.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_MailTruck_Back.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Police_Back.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Taxi_Back.png"
	},
	{
		37.0f/PTM_RATIO,
        5,
		{
			b2Vec2(-(100.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((100.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((100.5f/PTM_RATIO),(50.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(50.0f/PTM_RATIO)),
            b2Vec2(-(100.0f/PTM_RATIO),(0.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_SchoolBus_Left.png"
	},
	{
		44.0f/PTM_RATIO,
        5,
		{
			b2Vec2(-(230.0f/PTM_RATIO),-(30.0f/PTM_RATIO)),
			b2Vec2((235.0f/PTM_RATIO),-(30.0f/PTM_RATIO)),
			b2Vec2((235.0f/PTM_RATIO),(55.0f/PTM_RATIO)),
			b2Vec2((-120.0f/PTM_RATIO),(55.0f/PTM_RATIO)),
			b2Vec2(-(230.0f/PTM_RATIO),(30.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_SemiTruck_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_BlueCar_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_2DoorCar_Orange_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((90.5f/PTM_RATIO),(40.0f/PTM_RATIO)),
			b2Vec2(-(95.0f/PTM_RATIO),(40.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_HotDog_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_MailTruck_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Police_Left.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Taxi_Left.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_BlueCar_Back.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_2DoorCar_Orange_Front.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(35.0f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(40.0f/PTM_RATIO)),
			b2Vec2(-(35.0f/PTM_RATIO),(40.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_HotDog_Front.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_MailTruck_Front.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Police_Front.png"
	},
	{
		20.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(40.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(25.0f/PTM_RATIO)),
			b2Vec2(-(40.0f/PTM_RATIO),(25.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Taxi_Front.png"
	},
	{
		37.0f/PTM_RATIO,
        5,
		{
			b2Vec2(-(100.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((100.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((100.5f/PTM_RATIO),(0.0f/PTM_RATIO)),
            b2Vec2((75.5f/PTM_RATIO),(50.0f/PTM_RATIO)),
			b2Vec2(-(100.0f/PTM_RATIO),(50.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_SchoolBus_Right.png"
	},
	{
		44.0f/PTM_RATIO,
        5,
		{
			b2Vec2(-(230.0f/PTM_RATIO),-(30.0f/PTM_RATIO)),
			b2Vec2((235.0f/PTM_RATIO),-(30.0f/PTM_RATIO)),
			b2Vec2((235.0f/PTM_RATIO),(30.0f/PTM_RATIO)),
			b2Vec2((120.0f/PTM_RATIO),(55.0f/PTM_RATIO)),
			b2Vec2(-(230.0f/PTM_RATIO),(55.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_SemiTruck_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_BlueCar_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_2DoorCar_Orange_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(40.0f/PTM_RATIO)),
			b2Vec2((90.5f/PTM_RATIO),(40.0f/PTM_RATIO)),
			b2Vec2(-(95.0f/PTM_RATIO),(40.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_HotDog_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_MailTruck_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Police_Right.png"
	},
	{
		27.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(70.0f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),-(10.0f/PTM_RATIO)),
			b2Vec2((70.5f/PTM_RATIO),(10.0f/PTM_RATIO)),
			b2Vec2(-(70.0f/PTM_RATIO),(10.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Taxi_Right.png"
	},
	{
		100.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(20.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(120.0f/PTM_RATIO)),
			b2Vec2(-(20.0f/PTM_RATIO),(120.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Wall_01.png"
	},
	{
		100.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(20.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(120.0f/PTM_RATIO)),
			b2Vec2(-(20.0f/PTM_RATIO),(120.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Wall_02.png"
	},
	{
		100.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(20.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((40.5f/PTM_RATIO),(120.0f/PTM_RATIO)),
			b2Vec2(-(20.0f/PTM_RATIO),(120.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
        },
		(char*)"ctm_Wall_03.png"
	},
    {
		100.0f/PTM_RATIO,
        4,
		{
			b2Vec2(-(175.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((139.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2(-(145.0f/PTM_RATIO),(125.0f/PTM_RATIO)),
			b2Vec2(-(175.0f/PTM_RATIO),(125.0f/PTM_RATIO)),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
            b2Vec2(0.0f,0.0f),
		},
		(char*)"ctm_Wall_backramp_01.png"
	},

};
Platform::Platform(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type intype, int sort):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = 1.0f;
	m_Type = intype;
    m_backLayer = NULL;
    m_sort = sort;
}
Platform::Platform(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type intype, CCNode *backLayer, int sort):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = 1.0f;
	m_Type = intype;
    m_backLayer = backLayer;
    m_sort = sort;
}

Platform::~Platform()
{
	if(m_created)
	{
        if(post != NULL) post->removeFromParentAndCleanup(true);
        delete (TextureObject*)m_MainCollision->GetUserData();
    }
}
void Platform::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape triangle;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	triangle.Set(s_PlatformDefs[m_Type].points,s_PlatformDefs[m_Type].verts);
	
	
	fd.shape = &triangle;
    if(m_Type == HIGH_WALL)
        fd.friction = 0.0f;
    else
        fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+s_PlatformDefs[m_Type].yOffset);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex = new TextureObject(s_PlatformDefs[m_Type].texturename,m_ccLayer,m_sort,true,kTexture2DPixelFormat_Default);
    if(m_Type == LONG)
    {
        post = CCSprite::createWithSpriteFrameName("ctm_Platform_Lrg_Bracket.png");
        post->setPosition(ccp(m_StartPos.x*PTM_RATIO, (m_StartPos.y-2.0f)*PTM_RATIO));
        
        CCSprite *sprite  = CCSprite::createWithSpriteFrameName("ctm_Platform_Lrg_Post.png");
        float yposition = 30;
        yscale = 1.0f;
        yscale = (m_StartPos.y-2.0f) /(64.0f/PTM_RATIO);
        yposition *= 2.0f;
        yposition += -(yscale/2.0f)*64.0f;
        sprite->setScaleY(yscale);
        sprite->setPosition(ccp(56, yposition));
        post->addChild(sprite);
        
        m_backLayer->addChild(post,1);
    }
    else
    {
        post = NULL;
    }
    tex->SetTextureScale(m_Scale,m_Scale);
    
	m_MainCollision->SetUserData(tex);
	
}
void Platform::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    if(post != NULL)
    {
        float zoom = ScreenHelper::getCameraZoom();
        float scale = ScreenHelper::getTextureScale();
		post->setPosition(CCPointMake( m_StartPos.x * PTM_RATIO * zoom, (m_StartPos.y-2.0f) * PTM_RATIO * zoom));
        
		post->setScaleX(scale*zoom);
		post->setScaleY(scale*zoom);
    }
}
void Platform::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
        if(post != NULL)
        {
            post->removeFromParentAndCleanup(true);
            post = NULL;
        }
	}
}

