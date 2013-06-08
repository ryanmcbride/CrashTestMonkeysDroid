//
//  Store.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "GetPeanuts.h"
#include "../SaveLoad.h"
#include "Store.h"
#include "../../AudioManager.h"
#include "../../ScreenHelper.h"
#include "../Achievements.h"

using namespace cocos2d;

GetPeanuts::~GetPeanuts()
{
}
GetPeanuts::GetPeanuts()
{
        // enable touches
    setTouchEnabled( true );
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
		
    
    CCSprite *spriteReturn = CCSprite::createWithSpriteFrameName("ctm_Store_Shopping_Btn.png");
    CCSprite *spriteReturnDown = CCSprite::createWithSpriteFrameName("ctm_Store_Shopping_Btn_Down.png");
    
    CCMenuItem *returnButton = CCMenuItemSprite::create(spriteReturn,spriteReturnDown,this,menu_selector(GetPeanuts::returnButtonTapped));
    returnButton->setScale(scale);
    returnButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,90.0f,130.0f));
    
    CCMenu* backmenu = CCMenu::create(returnButton, NULL);
    backmenu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(backmenu,4);
    
    setPosition(CCPointMake(-480*scaleX, 0));
    runAction(CCMoveBy::create(0.15f,CCPointMake(480*scaleX, 0)));
        
    bMenuBuilt = false;
    isReturning = false;
        
    if(SaveLoad::m_SaveData.beenToPeanuts==0)
    {
        SaveLoad::m_SaveData.beenToPeanuts=1;
        SaveLoad::Save();
        // [TestFlight passCheckpoint:@"PEANUT_VISIT"];
    }

    scheduleUpdate();
}

void GetPeanuts::update(float dt)
{
    if(!bMenuBuilt)
    {
        BuildMenu();
        bMenuBuilt = true;
    }
    
    if(SaveLoad::m_SaveData.currency > 30000 && SaveLoad::m_SaveData.objectives[SaveLoad::MEH]==0)
    {
        Achievements::EarnAchievement(this->getParent(),SaveLoad::MEH);
    }
}

void GetPeanuts::StopPeanuts()
{
    CCSequence *sequence = CCSequence::create(CCMoveBy::create(0.15f,CCPointMake(-480, 0)),CCCallFuncN::create(this, callfuncN_selector(CCNode::removeFromParentAndCleanup)),NULL);
    runAction(sequence);
}
void GetPeanuts::returnButtonTapped(CCObject*object)
{
    //if([self isFinishingPurchase])return;
    
    isReturning = true;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    SaveLoad::Save();
    StopPeanuts();
    ((Store*)getParent())->StopGetPeanuts();
}

void GetPeanuts::BuildMenu()
{
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCMenu *screenMenu = CCMenu::create();
    
    CCSize dim;
    dim.width = 200.0f;
    dim.height = 35.0f;
    
    for(int i = 0; i < 4; i++)
    {
        
        CCMenuItem *temp = CCMenuItemImage::create("ctm_Store_GrayStrip.png","ctm_Store_LitStrip.png","ctm_Store_LitStrip.png",this,menu_selector(GetPeanuts::buyButtonTapped) );
        
        
        CCSprite *sprite = NULL;
        switch(i)
        {
            case 0:
                sprite = CCSprite::createWithSpriteFrameName("ctm_PeanutGraphic_A.png");
                break;
            case 1:
                sprite = CCSprite::createWithSpriteFrameName("ctm_PeanutGraphic_B.png");
                break;
            case 2:
                sprite = CCSprite::createWithSpriteFrameName("ctm_PeanutGraphic_C.png");
                break;
            case 3:
                sprite = CCSprite::createWithSpriteFrameName("ctm_PeanutGraphic_D.png");
                break;
        }
        sprite->setPosition(ccp(312/2-16,33));
        temp->addChild(sprite);
        
        const char *amount;
        const char *cost;
        switch(i)
        {
            case 0:
                amount = "3,000";
                cost = "$1.99";
                break;
            case 1:
                amount = "35,000";
                cost = "$7.99";
                break;
            case 2:
                amount = "100,000";
                cost = "$14.99";
                break;
            case 3:
                amount = "300,000";
                cost = "$24.99";
                break;
        }
        CCLabelTTF *label = CCLabelTTF::create(amount,"Jacoby ICG Black.ttf",30,dim,kCCTextAlignmentRight);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ccp(200,46));
        temp->addChild(label);
        
        
        CCSize dim;
        dim.width = 70.0f;
        dim.height = 20.0f;
        
        label = CCLabelTTF::create(cost,"Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentRight);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(260,23));
        temp->addChild(label);
        
        temp->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-250.0f,-i*50));
        temp->setScale(scale);
        screenMenu->addChild(temp);
        m_MenuItems[i] = temp;
    }
    screenMenu->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,86,-119));
    addChild(screenMenu);
}
void GetPeanuts::buyButtonTapped(CCObject*object)
{
    if(object == m_MenuItems[0])
    {
        SaveLoad::m_SaveData.currency += 3000;
    }
    if(object == m_MenuItems[1])
    {
        SaveLoad::m_SaveData.currency += 35000;
    }
    if(object == m_MenuItems[2])
    {
        SaveLoad::m_SaveData.currency += 100000;
    }
    if(object == m_MenuItems[3])
    {
        SaveLoad::m_SaveData.currency += 300000;
    }
    SaveLoad::Save();

}
/*
-(void) buyButtonTapped:(id)sender
{
    if(isReturning) return;
    AudioManager::PlayEffect(AUDIO_SELECT);
    [self doItemSelect:sender];
    
    
    
}

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
    if([self isFinishingPurchase])return;
    
    isReturning = true;
    
    AudioManager::PlayEffect(AUDIO_SELECT);
    
    SaveLoad::Save();
    [self StopPeanuts];
    [(StoreScene*)self.parent StopGetPeanuts];
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

-(void) loadingStorePopup
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2+50, screenSize.height/2-70);
    CCSprite *wheel = [CCSprite spriteWithFile:@"ctm_Loading_Wheel.png"];
    wheel.scale = 0.9f;
    wheel.position = ccp(315.0f/2.0f,35);
    [sprite addChild:wheel];
    [wheel runAction:[CCRepeatForever actionWithAction:[CCRotateBy actionWithDuration:1.0f angle:360]]];
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 50.0f;
    
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"Loading Store"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:32
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,75);
    [sprite addChild:label];
    
    [spriteBG addChild:sprite z:1 tag:1];
    
    
}
-(void) processingPaymentPopup
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2+50, screenSize.height/2-70);
    CCSprite *wheel = [CCSprite spriteWithFile:@"ctm_Loading_Wheel.png"];
    wheel.scale = 0.9f;
    wheel.position = ccp(315.0f/2.0f,35);
    [sprite addChild:wheel];
    [wheel runAction:[CCRepeatForever actionWithAction:[CCRotateBy actionWithDuration:1.0f angle:360]]];
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 50.0f;
    
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"Contacting Store"
                                       dimensions:dim
                                        alignment:CCTextAlignmentCenter
                                         fontName:@"Jacoby ICG Black.ttf"
                                         fontSize:28
                                     shadowOffset:CGSizeMake(2,-2)
                                       shadowBlur:1.0f
                                      shadowColor:ccc4(0,0,0,255)
                                        fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,75);
    [sprite addChild:label];
    
    [spriteBG addChild:sprite z:1 tag:2];
    
    ((CCLayer*)self.parent).isTouchEnabled = NO;
}
-(void) unableToPurchasePopup
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2+50, screenSize.height/2-70);
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 50.0f;
    
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"Unable to Purchase"
                                       dimensions:dim
                                        alignment:CCTextAlignmentCenter
                                         fontName:@"Jacoby ICG Black.ttf"
                                         fontSize:28
                                     shadowOffset:CGSizeMake(2,-2)
                                       shadowBlur:1.0f
                                      shadowColor:ccc4(0,0,0,255)
                                        fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,55);
    [sprite addChild:label];
    [sprite runAction:[CCSequence actions:[CCDelayTime actionWithDuration:3.0f],
                     [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                     [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                     nil]];
    
    
    [spriteBG addChild:sprite z:1 tag:1];
    
    
}
-(void) noInternetPopup
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2+50, screenSize.height/2-70);
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 25.0f;
    
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"No Internet Connection"
                                       dimensions:dim
                                        alignment:CCTextAlignmentCenter
                                         fontName:@"Jacoby ICG Black.ttf"
                                         fontSize:20
                                     shadowOffset:CGSizeMake(2,-2)
                                       shadowBlur:1.0f
                                      shadowColor:ccc4(0,0,0,255)
                                        fillColor:ccc4(237,188,0,255)];
    label.position = ccp(315.0f/2.0f,85);
    [sprite addChild:label];
    dim.height = 35.0f;
    label = [CCLabelFX labelWithString:@"Cannot connect to store. Make sure your internet connection is available."
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:15
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,60);
    [sprite addChild:label];
    
    dim.width = 50.0f;
    dim.height = 35.0f;
    label = [CCLabelFX labelWithString:@"OK"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:30
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(237,188,0,255)];
    
    CCMenuItem *yes = [CCMenuItemFont itemWithLabel:label
                                             target:self
                                           selector:@selector(returnButtonTapped:)];
    
    CCMenu *pop = [CCMenu menuWithItems:yes, nil];
    pop.position = ccp(315.0f/2.0f,110.0f/2.0f-25);
    [pop alignItemsHorizontallyWithPadding:30];
    
    [sprite addChild:pop];
    
    [spriteBG addChild:sprite z:1 tag:1];
    
    
}
-(BOOL) isFinishingPurchase
{
    if([spriteBG getChildByTag:2] == nil)
        return NO;
    return YES;
}

// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
    [s_iapMan release];
	// don't forget to call "super dealloc"
	[super dealloc];
}
@end*/
