//
//  Store.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Store.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "../CCScrollingMenu.h"
#include "GetPeanuts.h"
//#include "PeanutsPopup.h"
#include "../SaveLoad.h"
#include "../MainMenu.h"
#include "../../AudioManager.h"
#include "../../ScreenHelper.h"
#include "../Achievements.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

#define NUM_BIKE_ITEMS 8
static const char *s_BikeItemImg[NUM_BIKE_ITEMS] =
{
    "ctm_icon_08_Old_Yeller_Bike.png",//@"Old Yeller",
    "ctm_icon_07_Dirt_Bike.png",//@"Dirt Bike",
    "ctm_icon_06_CompanyBike.png",//@"McAcme",
    "ctm_icon_05_TikiBike.png",//@"Island",
    "ctm_icon_01_SCi_fi_Bike.png",//@"Sci-Fi",
    "ctm_icon_04_ElectricBike.png",//@"Electric",
    "ctm_icon_03_PizzaBike.png",//@"Pizza",
    "ctm_icon_02_PoliceBike.png",//@"C.H.I.M.P.s",
};

static const char *s_BikeItemName[NUM_BIKE_ITEMS] =
{
    "Old Yeller",
    "Dirt Bike",
    "McAcme",
    "Island",
    "Sci-Fi",
    "Electric",
    "Pizza",
    "C.H.I.M.P.s",
};

static int s_BikeItemCost[NUM_BIKE_ITEMS] =
{
    10000,
    10000,
    10000,
    25000,
    25000,
    25000,
    25000,
    25000,
};
#define NUM_CHARACTER_ITEMS 5
static const char *s_CharacterItemImg[NUM_CHARACTER_ITEMS] =
{
   //Characters
    "ctm_icon_Character_20_Jack_Chimp.png",//@"Biker",
    "ctm_icon_Character_24_Police_Chimp.png",//@"Chimps",
    "ctm_icon_Character_21_Barb_Chimp.png",//@"Character 3",
    "ctm_icon_Character_23_King_Chimp.png",//@"Biker",
    "ctm_icon_Character_22_Sock_Chimp.png",//@"Character 3",
};
static const char *s_CharacterItemName[NUM_CHARACTER_ITEMS] =
{
    //Characters
    "Jack Macaque",
    "C.H.I.M.P.S.",
    "Barbara Mandrill",
    "King Song",
    "Sock",
};
static int s_CharacterItemCost[NUM_CHARACTER_ITEMS] =
{
    //Characters
    10000,
    25000,
    15000,
    10000,
    25000,
};
#define NUM_POWERUP_ITEMS 3
static const char *s_PowerUpItemName[NUM_POWERUP_ITEMS] =
{
    //Powerups
    "Fire",
    "Slow Clock",
    "2X Peanuts",
};
static const char *s_PowerUpItemImg[NUM_POWERUP_ITEMS] =
{
    //Powerups
    "ctm_icon_Store_18_Fire.png",//@"Fire",
    "ctm_icon_Store_16_Slow-Clock.png",//@"Slow Clock",
    "ctm_icon_Store_17_2X-peanuts.png",//@"2X Peanuts",
};
static int s_PowerUpItemCost[NUM_POWERUP_ITEMS] =
{
    //Powerups
    6000,
    6000,
    6000,
};
static const char *s_PowerUpItemDesc[NUM_POWERUP_ITEMS] =
{
    //Powerups
    "lasts all level",
    "lasts all level",
    "lasts all level",
};
#define NUM_UPGRADE_ITEMS 7
static const char *s_UpgradeItemName[NUM_UPGRADE_ITEMS] =
{
    //Upgrades
    "Turbo Strips",
    "Armadillos",
    "Time Pickups",
    "Peanut Pickups",
    "Tricks",
    "Flips",
    "Fire Pickups",
};
static const char *s_UpgradeItemImg[NUM_UPGRADE_ITEMS] =
{
    //Upgrades
    "ctm_icon_Store_12_Turbo-Strips.png",//@"Turbo Strips",
    "ctm_icon_30_Blue_Armidillios.png",//@"Armadillos",
    "ctm_icon_Store_14_Remove-1-sec.png",//@"Time Pickups",
    "ctm_icon_Store_17_2X-peanuts.png",//@"Peanut Pickups",
    "ctm_icon_Store_15_Better-Tricks.png",//@"Tricks",
    "ctm_icon_Store_flip.png",//@"Flips",
    "ctm_icon_Store_Fire_Pickup.png",//@"Fire Pickups",
};
static int s_UpgradeItemCost[NUM_UPGRADE_ITEMS][4] =
{
    {250,1500,7000,-1},
    {200,1000,6000,-1},
    {250,1500,7000,-1},
    {400,4000,10000,-1},
    {300,3000,8000,-1},
    {350,3500,9000,-1},
    {225,1200,6500,-1},
};
static const char* s_UpgradeItemDesc[NUM_UPGRADE_ITEMS][4] =
{
    {"speed boost","bigger boost","biggest boost",""},
    {"launch you into air","launches you higher","highest",""},
    {"takes time off clock","remove 3 seconds","remove 5 seconds",""},
    {"2x peanuts","3x peanuts","5x peantus",""},
    {"200 point tricks","300 point tricks","500 point tricks",""},
    {"improves tricks","faster flips","fastest flips",""},
    {"improves tricks","fire lasts longer","fire lasts longest",""},
};

#define ICON_X 32
#define ICON_Y 33
#define NAME_X 162
#define NAME_Y 39
#define DESC_X 263
#define DESC_Y 24
#define COST_X (262+35)
#define COST_Y 31
#define POWER_UP_BAR_OFFSET 40
#define POWER_UP_BAR_OFFSET_Y 11
#define CATEGORY_OFFSET 65



/*static CCNode *s_node1 = NULL;
static CCNode *s_node2 = NULL;

static float s_StoreMenuLastY = -10000.0f;
+(void) setReturnNodes:(CCNode*)node1 second:(CCNode*)node2
{
    s_node1 = node1;
    s_node2 = node2;
}*/
int Store::numItemsCanBuy()
{
    int itemCount = 0;
    int currency = SaveLoad::m_SaveData.currency;
    int i;
    int unlockLevel[NUM_UPGRADE_ITEMS];
    unlockLevel[0] = SaveLoad::m_SaveData.turboLockLevel;
    unlockLevel[1] = SaveLoad::m_SaveData.trampLockLevel;
    unlockLevel[2] = SaveLoad::m_SaveData.timeLockLevel;
    unlockLevel[3] = SaveLoad::m_SaveData.peanutLockLevel;
    unlockLevel[4] = SaveLoad::m_SaveData.trickLockLevel;
    unlockLevel[5] = SaveLoad::m_SaveData.flipLockLevel;
    unlockLevel[6] = SaveLoad::m_SaveData.fireLockLevel;
    for(i = 0; i < NUM_UPGRADE_ITEMS; i++)
    {
        if(currency >= s_UpgradeItemCost[i][unlockLevel[i]] && s_UpgradeItemCost[i][unlockLevel[i]] > 0)
            itemCount++;
    }
    for(i=0; i < NUM_POWERUP_ITEMS; i++)
    {
        if(currency >= s_PowerUpItemCost[i])
            itemCount++;
    }
    for(i=0; i < NUM_CHARACTER_ITEMS; i++)
    {
        if(currency >= s_CharacterItemCost[i])
        {
            if(!(SaveLoad::m_SaveData.characters[i] & SaveLoad::UNLOCKED))
                itemCount++;
        }
    }
    for(i = 0; i < NUM_BIKE_ITEMS; i++)
    {
        if(currency >= s_BikeItemCost[i])
        {
            if(!(SaveLoad::m_SaveData.bikes[i] & SaveLoad::UNLOCKED))
                itemCount++;
        }
    }
    
    return itemCount;
}

CCScene* Store::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new Store();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}


// initialize your instance here
Store::Store()
{
	
    //SaveLoad::m_SaveData.currency = 300000;
    //SaveLoad::SaveGame();
    // enable touches
    setTouchEnabled( true );
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    CCSprite *sprite = CCSprite::create("MainBackFiller.png");
    sprite->setScaleX(scaleX*1.2f);
    sprite->setScaleY(scaleY*1.2f);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-32.0f));
    addChild(sprite);
    
    sprite = CCSprite::create("ctm_UI_topOverlayA_ver1.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite,2);
    
    CCLabelTTF *label = CCLabelTTF::create("STORE", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(0,0,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,2.0f,-52.0f));
    
    label = CCLabelTTF::create("STORE", "impact.ttf", 42*scale);
    addChild(label, 2);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER,0.0f,-50.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(Store::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,50.0f,-50.0f));
    ReturnButton = BackButton;
    
   
    CCSprite *spritePeanut = CCSprite::createWithSpriteFrameName("ctm_UI_Peanuts_Btn_ver1.png");
    CCSprite *spritePeanutDown = CCSprite::createWithSpriteFrameName("ctm_UI_Peanuts_Btn_Down.png");
    sprite = CCSprite::createWithSpriteFrameName("ctm_UI_PeanutsGlow_Btn_ver1.png");
    sprite->setPosition(ccp(136/2, 104/2));
    spritePeanut->addChild(sprite);
        
    CCMenuItem *PeanutsButton = CCMenuItemSprite::create(spritePeanut,spritePeanutDown,this,menu_selector(Store::peanutButtonTapped));
    
    PeanutsButton->setScale(scale);
    PeanutsButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,90.0f,130.0f));
    
    CCMenu* backmenu = CCMenu::create(BackButton, NULL);
    backmenu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(backmenu,4);
    
    m_slideControl = CCNode::create();
    addChild(m_slideControl);
    
    CCMenu* peanutmenu = CCMenu::create(PeanutsButton, NULL);
    peanutmenu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    m_slideControl->addChild(peanutmenu,4);
    
    
    CCScrollingMenu *screenMenu = CCScrollingMenu::create();
    screenMenu->setPosition(0,0);
    
    BuildUpgrades(screenMenu);
    BuildPowerUps(screenMenu);
    BuildCharacters(screenMenu);
    BuildBikes(screenMenu);
  
    screenMenu->alignItemsVerticallyWithPadding(-10*scaleY);
    CCSize viewSize;
    viewSize.width = 320.0f*scaleX;
    viewSize.height = 1450.0f*scaleY/(scaleY/scale);
    CCScrollView *scrollView = CCScrollView::create(viewSize,screenMenu);
    //scrollView->setBounceable(false);
    //temp = ComingSoonButton->getPositionX()/scaleX-480.0f;
    //temp += (ComingSoonButton->getContentSize().width)/scale;
    scrollView->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,160,275.0f*(scaleY/scale)-(viewSize.height/((scaleY+scale)/2.0f))/2.0f));
    scrollView->setContentSize(screenMenu->getContentSize());
    
    scrollView->setContentOffset(ccp(312.0f/2.0f*scaleX,0.0f));
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    
    m_slideControl->addChild(scrollView);

    
    char currencyStr[32];
    sprintf(currencyStr,"$%d",SaveLoad::m_SaveData.currency);
    
    CCSize dim;
    dim.width = 100.0f;
    dim.height = 25.0f;
    
    m_currency = CCLabelBMFont::create(currencyStr,"JacobyICGBlack22pnt.fnt");
    m_currency->setScale(scale);
    m_currency->setAnchorPoint(ccp(1.0f,0.5f));
    m_currency->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,456, 238));
    addChild(m_currency,10);
    
    
    if(SaveLoad::m_SaveData.beenToStore==0)
    {
        SaveLoad::m_SaveData.beenToStore=1;
        SaveLoad::Save();
    //    [TestFlight passCheckpoint:@"STORE_VISIT"];
    }
    
    scheduleUpdate();
}

Store::~Store()
{
}

void Store::update(float dt)
{
    char currencyStr[32];
    sprintf(currencyStr,"$%d",SaveLoad::m_SaveData.currency);
    m_currency->setString(currencyStr);
        
    if(SaveLoad::m_SaveData.objectives[SaveLoad::IN_SOVIET_RUSSIA]==0)
    {
        int unlockLevel[NUM_UPGRADE_ITEMS];
        unlockLevel[0] = SaveLoad::m_SaveData.turboLockLevel;
        unlockLevel[1] = SaveLoad::m_SaveData.trampLockLevel;
        unlockLevel[2] = SaveLoad::m_SaveData.timeLockLevel;
        unlockLevel[3] = SaveLoad::m_SaveData.peanutLockLevel;
        unlockLevel[4] = SaveLoad::m_SaveData.trickLockLevel;
        unlockLevel[5] = SaveLoad::m_SaveData.flipLockLevel;
        unlockLevel[6] = SaveLoad::m_SaveData.fireLockLevel;
        int itemCount = 0;
        int i;
        for(i = 0; i < NUM_UPGRADE_ITEMS; i++)
        {
            if(s_UpgradeItemCost[i][unlockLevel[i]] > 0)
                itemCount++;
        }
        for(i=0; i < NUM_CHARACTER_ITEMS; i++)
        {
            if(!(SaveLoad::m_SaveData.characters[i] & SaveLoad::UNLOCKED))
                itemCount++;
        }
        for(i = 0; i < NUM_BIKE_ITEMS; i++)
        {
            if(!(SaveLoad::m_SaveData.bikes[i] & SaveLoad::UNLOCKED))
                itemCount++;
        }
        
        if(itemCount==0)
        {
            Achievements::EarnAchievement(this->getParent(),SaveLoad::IN_SOVIET_RUSSIA);
        }
    }
}

void Store::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->popScene();
    //CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
void Store::peanutButtonTapped(CCObject*object)
{
    //if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    StartGetPeanuts();
}
void Store::nullButtonTapped(CCObject*object)
{
}

void Store::StartGetPeanuts()
{
    float scaleX = ScreenHelper::getTextureScaleX();
    ReturnButton->setEnabled(false);
    ReturnButton->setVisible(false);
    m_getPeanuts = new GetPeanuts();
    addChild(m_getPeanuts);
    m_slideControl->runAction(CCMoveBy::create(0.15f,CCPointMake(480*scaleX, 0)));
}
void Store::StopGetPeanuts()
{
    float scaleX = ScreenHelper::getTextureScaleX();
    m_getPeanuts = NULL;
    m_slideControl->runAction(CCMoveBy::create(0.15f,CCPointMake(-480*scaleX, 0)));
    ReturnButton->setEnabled(true);
    ReturnButton->setVisible(true);
}

void Store::BuildUpgrades(cocos2d::CCMenu* menu)
{
    float scale = ScreenHelper::getTextureScale();
    
	CCMenuItemImage *topBar = CCMenuItemImage::create("ctm_UI_TransparentButton.png","ctm_UI_TransparentButton.png",this,menu_selector(Store::nullButtonTapped));
	
    topBar->setScale(scale);
    CCLabelTTF* label1 = CCLabelTTF::create("UPGRADES","Jacoby ICG Black.ttf",20);
    label1->setColor(ccc3(43,197,231));
	label1->setPosition(ccp(-150+CATEGORY_OFFSET,17));
	topBar->addChild(label1);
    
	menu->addChild(topBar);
	int unlockLevel[NUM_UPGRADE_ITEMS];
    unlockLevel[0] = SaveLoad::m_SaveData.turboLockLevel;
    unlockLevel[1] = SaveLoad::m_SaveData.trampLockLevel;
    unlockLevel[2] = SaveLoad::m_SaveData.timeLockLevel;
    unlockLevel[3] = SaveLoad::m_SaveData.peanutLockLevel;
    unlockLevel[4] = SaveLoad::m_SaveData.trickLockLevel;
    unlockLevel[5] = SaveLoad::m_SaveData.flipLockLevel;
    unlockLevel[6] = SaveLoad::m_SaveData.fireLockLevel;
	
	for(int i = 0; i < NUM_UPGRADE_ITEMS; i++)
	{
		CCMenuItem *temp = CCMenuItemImage::create("ctm_Store_GrayStrip.png","ctm_Store_GrayStrip.png","ctm_Store_LitStrip.png",this,menu_selector(Store::buyUpgradeButtonTapped) );
        
        CCSprite *sprite;
        
        sprite = CCSprite::create("ctm_Store_PurchaseBars.png");
        sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+302-120,POWER_UP_BAR_OFFSET_Y+21));
        temp->addChild(sprite);
        
		if(unlockLevel[i]>=1)
        {
            sprite = CCSprite::create("ctm_Store_LitPurchaseBar.png");
            sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+290-120,POWER_UP_BAR_OFFSET_Y+20));
            temp->addChild(sprite);
		}
		if(unlockLevel[i]>=2)
        {
            sprite = CCSprite::create("ctm_Store_LitPurchaseBar.png");
            sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+305-120,POWER_UP_BAR_OFFSET_Y+20));
            temp->addChild(sprite);
        }
		if(unlockLevel[i]>=3)
        {
            sprite = CCSprite::create("ctm_Store_LitPurchaseBar.png");
            sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+320-120,POWER_UP_BAR_OFFSET_Y+20));
            temp->addChild(sprite);
		}
		sprite = CCSprite::createWithSpriteFrameName(s_UpgradeItemImg[i]);
		sprite->setPosition(ccp(ICON_X,ICON_Y));
		temp->addChild(sprite);
        
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 25.0f;
        
        CCLabelTTF *label = CCLabelTTF::create(s_UpgradeItemName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(NAME_X,NAME_Y));
        temp->addChild(label);
        
		
        dim.width = 400.0f;
        dim.height = 18.0f;
        label = CCLabelTTF::create(s_UpgradeItemDesc[i][unlockLevel[i]],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(230,230,230));        
        label->setPosition(ccp(DESC_X,DESC_Y));
        temp->addChild(label,0,15);
        
        
		//CGSize dim;
		dim.width = 50.0f;
		dim.height = 20.0f;
        char currencyStr[32];
        if(s_UpgradeItemCost[i][unlockLevel[i]] > 0)
            sprintf(currencyStr,"$%d",s_UpgradeItemCost[i][unlockLevel[i]]);
        else
            sprintf(currencyStr,"Max");
        
        CCLabelBMFont *BMfontLabel = CCLabelBMFont::create(currencyStr,"JacobyICGBlack18pnt.fnt");
        BMfontLabel->setAnchorPoint(ccp(1.0f,0.5f));
        BMfontLabel->setPosition(ccp(COST_X,COST_Y));
        m_UpgradeCosts[i] = BMfontLabel;
		temp->addChild(BMfontLabel);
		
        temp->setScale(scale);
		menu->addChild(temp);
        
        m_UpgradeButtons[i] = temp;
	}
}

void Store::BuildPowerUps(cocos2d::CCMenu* menu)
{
    float scale = ScreenHelper::getTextureScale();
    
	CCMenuItemImage *topBar = CCMenuItemImage::create("ctm_UI_TransparentButton.png","ctm_UI_TransparentButton.png",this,menu_selector(Store::nullButtonTapped));
	
    topBar->setScale(scale);
    CCLabelTTF* label1 = CCLabelTTF::create("POWERUPS","Jacoby ICG Black.ttf",20);
    label1->setColor(ccc3(43,197,231));
	label1->setPosition(ccp(-148+CATEGORY_OFFSET,17));
	topBar->addChild(label1);
    
    
	menu->addChild(topBar);
	
	for(int i = 0; i < NUM_POWERUP_ITEMS; i++)
	{
        CCMenuItem *temp = CCMenuItemImage::create("ctm_Store_GrayStrip.png","ctm_Store_GrayStrip.png","ctm_Store_LitStrip.png",this,menu_selector(Store::powerupButtonTapped) );
        
		
		CCSprite *sprite = CCSprite::createWithSpriteFrameName(s_PowerUpItemImg[i]);
		sprite->setPosition(ccp(ICON_X,ICON_Y));
		temp->addChild(sprite);

        char labelString[32];
        if(i==0)
        {
            if(SaveLoad::m_SaveData.numLevelFire)
                sprintf(labelString,"%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numLevelFire);
            else
                sprintf(labelString,"%s",s_PowerUpItemName[i]);
        }
        if(i==1)
        {
            if(SaveLoad::m_SaveData.numTimeSlow)
                sprintf(labelString,"%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numTimeSlow);
            else
                sprintf(labelString,"%s",s_PowerUpItemName[i]);
        }
        if(i==2)
        {
            if(SaveLoad::m_SaveData.numDoubleNuts)
                sprintf(labelString,"%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numDoubleNuts);
            else
                sprintf(labelString,"%s",s_PowerUpItemName[i]);
        }
        
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 25.0f;
        
        
        CCLabelTTF *label = CCLabelTTF::create(labelString,"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(NAME_X,NAME_Y));
        temp->addChild(label);
        
        m_PowerUpNames[i] = label;
        
        dim.width = 400.0f;
        dim.height = 18.0f;
        label = CCLabelTTF::create(s_PowerUpItemDesc[i],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(DESC_X,DESC_Y));
        temp->addChild(label,0,15);
        
		//CGSize dim;
		dim.width = 50.0f;
		dim.height = 20.0f;
        
        char currencyStr[32];
        sprintf(currencyStr,"$%d",s_PowerUpItemCost[i]);
        
        CCLabelBMFont *BMfontLabel = CCLabelBMFont::create(currencyStr,"JacobyICGBlack18pnt.fnt");
        BMfontLabel->setAnchorPoint(ccp(1.0f,0.5f));
        BMfontLabel->setPosition(ccp(COST_X,COST_Y));
		temp->addChild(BMfontLabel);
		
        temp->setScale(scale);
		
		menu->addChild(temp);
        m_PowerUpbuttons[i] = temp;
	}
	
}

void Store::BuildCharacters(cocos2d::CCMenu* menu)
{
    
    float scale = ScreenHelper::getTextureScale();
    
	CCMenuItemImage *topBar = CCMenuItemImage::create("ctm_UI_TransparentButton.png","ctm_UI_TransparentButton.png",this,menu_selector(Store::nullButtonTapped));
	
    topBar->setScale(scale);
    CCLabelTTF* label1 = CCLabelTTF::create("CHARACTERS","Jacoby ICG Black.ttf",20);
    label1->setColor(ccc3(43,197,231));
	label1->setPosition(ccp(-137+CATEGORY_OFFSET,17));
	topBar->addChild(label1);
    
    
	menu->addChild(topBar);
    
    for(int i = 0; i < NUM_CHARACTER_ITEMS; i++)
	{
		CCMenuItem *temp = CCMenuItemImage::create("ctm_Store_GrayStrip.png","ctm_Store_GrayStrip.png","ctm_Store_LitStrip.png",this,menu_selector(Store::charButtonTapped) );
		
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(s_CharacterItemImg[i]);
		sprite->setPosition(ccp(ICON_X,ICON_Y));
		temp->addChild(sprite);
        
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 25.0f;
        
        CCLabelTTF *label = CCLabelTTF::create(s_CharacterItemName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(NAME_X,NAME_Y));
        temp->addChild(label);
        
        dim.width = 400.0f;
        dim.height = 18.0f;
        
        const char *status = NULL;
        if(SaveLoad::m_SaveData.characters[i] & SaveLoad::SELECTED)
            status = "Selected";
        else if(SaveLoad::m_SaveData.characters[i] & SaveLoad::UNLOCKED)
		    status = "Unlocked";
        else
            status = "Locked";

        label = CCLabelTTF::create(status,"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(DESC_X,DESC_Y));
        temp->addChild(label,0,15);
                
        m_CharDescriptions[i] = label;
        
        if(SaveLoad::m_SaveData.characters[i]==0)
        {
            dim.width = 50.0f;
            dim.height = 20.0f;
                        
            char currencyStr[32];
            sprintf(currencyStr,"$%d",s_CharacterItemCost[i]);
            
            CCLabelBMFont *BMfontLabel = CCLabelBMFont::create(currencyStr,"JacobyICGBlack18pnt.fnt");
            BMfontLabel->setAnchorPoint(ccp(1.0f,0.5f));
            BMfontLabel->setPosition(ccp(COST_X,COST_Y));
            temp->addChild(BMfontLabel,0,42);
            
        }
		
		temp->setScale(scale);
		
		menu->addChild(temp);
        m_Charbuttons[i] = temp;
	}
}

void Store::BuildBikes(cocos2d::CCMenu* menu)
{
    float scale = ScreenHelper::getTextureScale();
    
	CCMenuItemImage *topBar = CCMenuItemImage::create("ctm_UI_TransparentButton.png","ctm_UI_TransparentButton.png",this,menu_selector(Store::nullButtonTapped));
	
    topBar->setScale(scale);
    CCLabelTTF* label1 = CCLabelTTF::create("BIKES","Jacoby ICG Black.ttf",20);
    label1->setColor(ccc3(43,197,231));
	label1->setPosition(ccp(-170+CATEGORY_OFFSET,17));
	topBar->addChild(label1);
    
	menu->addChild(topBar);
    
	for(int i = 0; i < NUM_BIKE_ITEMS; i++)
	{
        CCMenuItem *temp = CCMenuItemImage::create("ctm_Store_GrayStrip.png","ctm_Store_GrayStrip.png","ctm_Store_LitStrip.png",this,menu_selector(Store::bikeButtonTapped) );
		
        CCSprite *sprite = CCSprite::createWithSpriteFrameName(s_BikeItemImg[i]);
		sprite->setPosition(ccp(ICON_X,ICON_Y));
		temp->addChild(sprite);
		
        CCSize dim;
        dim.width = 200.0f;
        dim.height = 25.0f;
        
        CCLabelTTF *label = CCLabelTTF::create(s_BikeItemName[i],"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(NAME_X,NAME_Y));
        temp->addChild(label);
        
		const char *status = NULL;
        if(SaveLoad::m_SaveData.bikes[i] & SaveLoad::SELECTED)
            status = "Selected";
        else if(SaveLoad::m_SaveData.bikes[i] & SaveLoad::UNLOCKED)
		    status = "Unlocked";
        else
            status = "Locked";
        
        dim.width = 400.0f;
        dim.height = 18.0f;
        label = CCLabelTTF::create(status,"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(DESC_X,DESC_Y));
        temp->addChild(label,0,15);
        
        m_BikeDescriptions[i] = label;
		
        if(SaveLoad::m_SaveData.bikes[i]==0)
        {
            //CGSize dim;
            dim.width = 50.0f;
            dim.height = 20.0f;
            
            char currencyStr[32];
            sprintf(currencyStr,"$%d",s_BikeItemCost[i]);
            
            CCLabelBMFont *BMfontLabel = CCLabelBMFont::create(currencyStr,"JacobyICGBlack18pnt.fnt");
            BMfontLabel->setAnchorPoint(ccp(1.0f,0.5f));
            BMfontLabel->setPosition(ccp(COST_X,COST_Y));
            temp->addChild(BMfontLabel,0,42);
		}
		
        temp->setScale(scale);
        
		menu->addChild(temp);
        m_Bikebuttons[i] = temp;
	}
	
    //add a bottom bar to push things up
    topBar = CCMenuItemImage::create("ctm_UI_TransparentButton.png","ctm_UI_TransparentButton.png",this,menu_selector(Store::nullButtonTapped));
    topBar->setScale(scale);
	menu->addChild(topBar);
}

void Store::addUpgradeBar(CCNode* sender,int level, int num)
{
    CCSprite *sprite;
    sprite = CCSprite::create("ctm_Store_LitPurchaseBar.png");
    if(level==1)
        sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+290-120,POWER_UP_BAR_OFFSET_Y+20));
        if(level==2)
            sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+305-120,POWER_UP_BAR_OFFSET_Y+20));
            if(level==3)
                sprite->setPosition(ccp(POWER_UP_BAR_OFFSET+320-120,POWER_UP_BAR_OFFSET_Y+20));
    sender->addChild(sprite);
    
    m_UpgradeCosts[num]->removeFromParentAndCleanup(true);
    CCSize dim;
    dim.width = 50.0f;
    dim.height = 20.0f;
    
    char currencyStr[32];
    
    if(s_UpgradeItemCost[num][level] > 0)
        sprintf(currencyStr,"$%d", s_UpgradeItemCost[num][level]);
    else
        sprintf(currencyStr,"Max");
    
    dim.width = 400.0f;
    dim.height = 18.0f;
            
    sender->removeChildByTag(15,true);
    
    
    CCLabelTTF* label = CCLabelTTF::create(s_UpgradeItemDesc[num][level],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
    label->setColor(ccc3(230,230,230));
    label->setPosition(ccp(DESC_X,DESC_Y));
    sender->addChild(label,0,15);
        
    
    CCLabelBMFont *BMfontLabel = CCLabelBMFont::create(currencyStr,"JacobyICGBlack18pnt.fnt");
    BMfontLabel->setAnchorPoint(ccp(1.0f,0.5f));
    BMfontLabel->setPosition(ccp(COST_X,COST_Y));
    sender->addChild(BMfontLabel);
    m_UpgradeCosts[num] = BMfontLabel;
}
void Store::buyUpgradeButtonTapped(CCObject*object)
{
//    if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    CCNode *buttonNode = (CCNode*)object;
    //CCPoint position = [buttonNode convertToWorldSpace:ccp(0,0)];
    //if(position.y>190.0f || position.y < -5.0f)return;
    
    //[self doItemSelect:sender];
    
    for(int i = 0; i < 7; i++)
    {
        if(m_UpgradeButtons[i] == object)
        {
            switch(i)
            {
                case 0://turbo
                    if(SaveLoad::m_SaveData.turboLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[0][SaveLoad::m_SaveData.turboLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[0][SaveLoad::m_SaveData.turboLockLevel];
                            SaveLoad::m_SaveData.turboLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.turboLockLevel,i);
                        }
                        else
                        {
                          //  [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 1://tramps
                    if(SaveLoad::m_SaveData.trampLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[1][SaveLoad::m_SaveData.trampLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[1][SaveLoad::m_SaveData.trampLockLevel];
                            SaveLoad::m_SaveData.trampLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.trampLockLevel,i);
                        }
                        else
                        {
                         //   [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 2://time
                    if(SaveLoad::m_SaveData.timeLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[2][SaveLoad::m_SaveData.timeLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[2][SaveLoad::m_SaveData.timeLockLevel];
                            SaveLoad::m_SaveData.timeLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.timeLockLevel,i);
                        }
                        else
                        {
                         //   [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 3://peanut
                    if(SaveLoad::m_SaveData.peanutLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[3][SaveLoad::m_SaveData.peanutLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[3][SaveLoad::m_SaveData.peanutLockLevel];
                            SaveLoad::m_SaveData.peanutLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.peanutLockLevel,i);
                        }
                        else
                        {
                         //   [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 4://tricks
                    if(SaveLoad::m_SaveData.trickLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[4][SaveLoad::m_SaveData.trickLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[4][SaveLoad::m_SaveData.trickLockLevel];
                            SaveLoad::m_SaveData.trickLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.trickLockLevel,i);
                        }
                        else
                        {
                        //    [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 5://flips
                    if(SaveLoad::m_SaveData.flipLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[5][SaveLoad::m_SaveData.flipLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[5][SaveLoad::m_SaveData.flipLockLevel];
                            SaveLoad::m_SaveData.flipLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.flipLockLevel,i);
                            
//                            if(SaveLoad::m_SaveData.flipLockLevel == 1)
//                                [self addChild:[FlipPopup node]];
                        }
                        else
                        {
                        //    [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
                case 6://fire pickup
                    if(SaveLoad::m_SaveData.fireLockLevel < 3)
                    {
                        if(SaveLoad::m_SaveData.currency >= s_UpgradeItemCost[6][SaveLoad::m_SaveData.fireLockLevel])
                        {
                            SaveLoad::m_SaveData.currency -= s_UpgradeItemCost[6][SaveLoad::m_SaveData.fireLockLevel];
                            SaveLoad::m_SaveData.fireLockLevel++;
                            addUpgradeBar(buttonNode,SaveLoad::m_SaveData.fireLockLevel,i);
                        }
                        else
                        {
                         //   [self addChild:[PeanutsPopup node]];
                        }
                    }
                    break;
            }
        }
    }
    SaveLoad::Save();
}

void Store::powerupButtonTapped(CCObject*object)
{
 //   if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    CCNode *buttonNode = (CCNode*)object;
    //CGPoint position = [buttonNode convertToWorldSpace:ccp(0,0)];
    //if(position.y>190.0f || position.y < -5.0f)return;
    
    //[self doItemSelect:sender];
    
    for(int i = 0; i < NUM_POWERUP_ITEMS; i++)
    {
        if(m_PowerUpbuttons[i] == buttonNode)
        {
            CCSize dim;
            dim.width = 200.0f;
            dim.height = 25.0f;
            m_PowerUpNames[i]->removeFromParentAndCleanup(true);

            if(i==0)
            {
                //fire
                if(SaveLoad::m_SaveData.currency >= s_PowerUpItemCost[i])
                {
                    SaveLoad::m_SaveData.numLevelFire++;
                    SaveLoad::m_SaveData.currency -= s_PowerUpItemCost[i];
                    
                    char labelString[32];
                    sprintf(labelString, "%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numLevelFire);
                    
                    CCLabelTTF* label = CCLabelTTF::create(labelString,"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
                    label->setColor(ccc3(237,188,0));
                    label->setPosition(ccp(NAME_X,NAME_Y));
                    
                    buttonNode->addChild(label);
                    m_PowerUpNames[i] = label;
                }
                else
                {
                    //[self addChild:[PeanutsPopup node]];
                }
            }
            else if (i==1)
            {
                //slow clock
                if(SaveLoad::m_SaveData.currency >= s_PowerUpItemCost[i])
                {
                    SaveLoad::m_SaveData.numTimeSlow++;
                    SaveLoad::m_SaveData.currency -= s_PowerUpItemCost[i];
                    
                    
                    char labelString[32];
                    sprintf(labelString, "%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numTimeSlow);
                    
                    
                    CCLabelTTF* label = CCLabelTTF::create(labelString,"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
                    label->setColor(ccc3(237,188,0));
                    label->setPosition(ccp(NAME_X,NAME_Y));
                    
                    buttonNode->addChild(label);
                    m_PowerUpNames[i] = label;
                }
                else
                {
                    //[self addChild:[PeanutsPopup node]];
                }
            }
            else
            {
                //peanuts
                if(SaveLoad::m_SaveData.currency >= s_PowerUpItemCost[i])
                {
                    SaveLoad::m_SaveData.numDoubleNuts++;
                    SaveLoad::m_SaveData.currency -= s_PowerUpItemCost[i];
                    
                    
                    char labelString[32];
                    sprintf(labelString, "%s(%d)",s_PowerUpItemName[i],SaveLoad::m_SaveData.numDoubleNuts);
                    
                    CCLabelTTF* label = CCLabelTTF::create(labelString,"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentLeft);
                    label->setColor(ccc3(237,188,0));
                    label->setPosition(ccp(NAME_X,NAME_Y));
                    
                    buttonNode->addChild(label);
                    m_PowerUpNames[i] = label;
                }
                else
                {
                    //[self addChild:[PeanutsPopup node]];
                }
            }
            SaveLoad::Save();
        }
    }
}

void Store::charButtonTapped(CCObject*object)
{
 //   if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    CCNode *buttonNode = (CCNode*)object;
//    CGPoint position = [buttonNode convertToWorldSpace:ccp(0,0)];
//    if(position.y>190.0f || position.y < -5.0f)return;
    
//    [self doItemSelect:sender];
    
    CCSize dim;
    for(int i = 0; i < NUM_CHARACTER_ITEMS; i++)
    {
        if(m_Charbuttons[i] == buttonNode)
        {
            if(SaveLoad::m_SaveData.characters[i] & SaveLoad::SELECTED)
                return;
            if(SaveLoad::m_SaveData.characters[i] & SaveLoad::UNLOCKED)
            {
                for(int j = 0; j < NUM_CHARACTER_ITEMS; j++)
                {
                    if(SaveLoad::m_SaveData.characters[j] & SaveLoad::SELECTED)
                    {
                        m_CharDescriptions[j]->removeFromParentAndCleanup(true);
                        
                        dim.width = 400.0f;
                        dim.height = 18.0f;
                        
                        CCLabelTTF* label = CCLabelTTF::create("Unlocked","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                        label->setColor(ccc3(230,230,230));
                        label->setPosition(ccp(DESC_X,DESC_Y));
                        m_Charbuttons[j]->addChild(label);
                        m_CharDescriptions[j] = label;
                        
                        SaveLoad::m_SaveData.characters[j] &= ~SaveLoad::SELECTED;
                    }
                }
                
                m_CharDescriptions[i]->removeFromParentAndCleanup(true);
                
                dim.width = 400.0f;
                dim.height = 18.0f;
                
                CCLabelTTF* label = CCLabelTTF::create("Selected","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                label->setColor(ccc3(230,230,230));
                label->setPosition(ccp(DESC_X,DESC_Y));
                m_Charbuttons[i]->addChild(label);
                m_CharDescriptions[i] = label;
                
                SaveLoad::m_SaveData.characters[i] |= SaveLoad::SELECTED;
            }
            else
            {
                if(SaveLoad::m_SaveData.currency >= s_CharacterItemCost[i])
                {
                    for(int j = 0; j < NUM_CHARACTER_ITEMS; j++)
                    {
                        if(SaveLoad::m_SaveData.characters[j] & SaveLoad::SELECTED)
                        {
                            m_CharDescriptions[j]->removeFromParentAndCleanup(true);
                            
                            dim.width = 400.0f;
                            dim.height = 18.0f;
                            
                            CCLabelTTF* label = CCLabelTTF::create("Unlocked","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                            label->setColor(ccc3(230,230,230));
                            label->setPosition(ccp(DESC_X,DESC_Y));
                            m_Charbuttons[j]->addChild(label);
                            m_CharDescriptions[j] = label;
                            
                            SaveLoad::m_SaveData.characters[j] &= ~SaveLoad::SELECTED;
                        }
                    }
                    SaveLoad::m_SaveData.characters[i] |= SaveLoad::UNLOCKED;
                    SaveLoad::m_SaveData.characters[i] |= SaveLoad::SELECTED;
                    SaveLoad::m_SaveData.currency -= s_CharacterItemCost[i];
                    m_Charbuttons[i]->getChildByTag(42)->removeFromParentAndCleanup(true);
                    
                    m_CharDescriptions[i]->removeFromParentAndCleanup(true);
                    
                    dim.width = 400.0f;
                    dim.height = 18.0f;
                    CCLabelTTF* label = CCLabelTTF::create("Selected","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                    label->setColor(ccc3(230,230,230));
                    label->setPosition(ccp(DESC_X,DESC_Y));
                    m_Charbuttons[i]->addChild(label);
                    m_CharDescriptions[i] = label;
                    
                    if(i==2)
                    {
                        if(SaveLoad::m_SaveData.objectives[SaveLoad::HOT_COFFEE_MOD]==0)
                        {
                            Achievements::EarnAchievement(this->getParent(),SaveLoad::HOT_COFFEE_MOD);
                        }
                    }
                }
                else
                {
                    //[self addChild:[PeanutsPopup node]];
                }
            }
            SaveLoad::Save();
        }
    }
}

void Store::bikeButtonTapped(CCObject*object)
{
    //if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    CCNode *buttonNode = (CCNode*)object;
    //CGPoint position = [buttonNode convertToWorldSpace:ccp(0,0)];
    //if(position.y>190.0f || position.y < -5.0f)return;
    
    //[self doItemSelect:sender];
    
    CCSize dim;
    for(int i = 0; i < NUM_BIKE_ITEMS; i++)
    {
        if(m_Bikebuttons[i] == buttonNode)
        {
            if(SaveLoad::m_SaveData.bikes[i] & SaveLoad::SELECTED)
                return;
            if(SaveLoad::m_SaveData.bikes[i] & SaveLoad::UNLOCKED)
            {
                for(int j = 0; j < NUM_BIKE_ITEMS; j++)
                {
                    if(SaveLoad::m_SaveData.bikes[j] & SaveLoad::SELECTED)
                    {
                        m_BikeDescriptions[j]->removeFromParentAndCleanup(true);
                        
                        dim.width = 400.0f;
                        dim.height = 18.0f;
                        CCLabelTTF* label = CCLabelTTF::create("Unlocked","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                        label->setColor(ccc3(230,230,230));
                        label->setPosition(ccp(DESC_X,DESC_Y));
                        
                        m_Bikebuttons[j]->addChild(label);
                        m_BikeDescriptions[j] = label;
                        
                        SaveLoad::m_SaveData.bikes[j] &= ~SaveLoad::SELECTED;
                    }
                }
                
                m_BikeDescriptions[i]->removeFromParentAndCleanup(true);
                
                dim.width = 400.0f;
                dim.height = 18.0f;
                CCLabelTTF* label = CCLabelTTF::create("Selected","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                label->setColor(ccc3(230,230,230));
                label->setPosition(ccp(DESC_X,DESC_Y));
                
                m_Bikebuttons[i]->addChild(label);
                m_BikeDescriptions[i] = label;
                SaveLoad::m_SaveData.bikes[i] |= SaveLoad::SELECTED;
            }
            else
            {
                if(SaveLoad::m_SaveData.currency >= s_BikeItemCost[i])
                {
                    for(int j = 0; j < NUM_BIKE_ITEMS; j++)
                    {
                        if(SaveLoad::m_SaveData.bikes[j] & SaveLoad::SELECTED)
                        {
                            m_BikeDescriptions[j]->removeFromParentAndCleanup(true);
                            
                            dim.width = 400.0f;
                            dim.height = 18.0f;
                            CCLabelTTF* label = CCLabelTTF::create("Unlocked","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                            label->setColor(ccc3(230,230,230));
                            label->setPosition(ccp(DESC_X,DESC_Y));
                            
                            m_Bikebuttons[j]->addChild(label);
                            m_BikeDescriptions[j] = label;
                            
                            SaveLoad::m_SaveData.bikes[j] &= ~SaveLoad::SELECTED;
                        }
                    }
                    SaveLoad::m_SaveData.bikes[i] |= SaveLoad::UNLOCKED;
                    SaveLoad::m_SaveData.bikes[i] |= SaveLoad::SELECTED;
                    SaveLoad::m_SaveData.currency -= s_BikeItemCost[i];
                    m_Bikebuttons[i]->getChildByTag(42)->removeFromParentAndCleanup(true);
                    
                    m_BikeDescriptions[i]->removeFromParentAndCleanup(true);
                    
                    dim.width = 400.0f;
                    dim.height = 18.0f;
                    CCLabelTTF* label = CCLabelTTF::create("Selected","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
                    label->setColor(ccc3(230,230,230));
                    label->setPosition(ccp(DESC_X,DESC_Y));
                    m_Bikebuttons[i]->addChild(label);
                    m_BikeDescriptions[i] = label;
                }
                else
                {
//                    [self addChild:[PeanutsPopup node]];
                }
            }
            SaveLoad::Save();
        }
    }
}


/*
-(void) doubleCheck:(CCMenuItem*) item
{
    if(!item.isEnabled)
       [item setIsEnabled:YES];
}
-(void) doItemSelect:(CCMenuItem*) item
{
    [item setIsEnabled:NO];
    [item runAction:[CCSequence actions:[CCDelayTime actionWithDuration:0.1f],
                    [CCCallFuncND actionWithTarget:item selector:@selector(setIsEnabled:) data:(void*)YES],
                    [CCCallFuncND actionWithTarget:self selector:@selector(doubleCheck:) data:(void*)item],
                     nil]];
}


-(void) returnButtonTapped:(id)sender
{
    if([PeanutsPopup isActive])return;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    SaveLoad::SaveGame();
	
    if(s_node1 != nil)
    {
        s_node1.visible = true;
        s_node1.position = ccp(s_node1.position.x+1000,s_node1.position.y);
    }
    if(s_node2 != nil)
    {
        s_node2.visible = true;
        s_node2.position = ccp(s_node2.position.x+1000,s_node2.position.y);
        
        [[s_node2 getChildByTag:0xf00d] doStoreAlertButton];
    }
    else
    {
        [s_node1 doStoreAlertButton];
    }
    
    [self removeFromParentAndCleanup:YES];
    
    //[[CCDirector sharedDirector] replaceScene: [MainMenu scene]];
}



-(void) nullButtonTapped:(id)sender
{
}

-(void) buyButtonTapped:(id)sender 
{
}

-(void) draw
{
	
}



- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	//Add a new body/atlas sprite at the touched location
	for( UITouch *touch in touches ) 
	{
		CGPoint location = [touch locationInView: [touch view]];
		
		location = [[CCDirector sharedDirector] convertToGL: location];		
	}
}


// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
    s_StoreMenuLastY = m_Menu.position.y;
	// don't forget to call "super dealloc"
	[super dealloc];
}
@end*/
