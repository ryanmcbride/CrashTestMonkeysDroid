//
//  Store.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "StorePopup.h"
#import "Store.h"
#import "SaveManager.h"
#import "CCLabelFX.h"
#import <libkern/OSAtomic.h>
#import "AudioManager.h"

@implementation StorePopup

volatile int s_isStorePopupActive = 0;

+(BOOL) isActive
{
    return s_isStorePopupActive;
}


+(id) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	StorePopup *layer = [StorePopup node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

// initialize your instance here
-(id) init
{
	if( (self=[super init])) 
    {
		
		// enable touches
		self.isTouchEnabled = YES;
		
		
		CGSize screenSize = [CCDirector sharedDirector].winSize;
		CCLOG(@"Screen width %0.2f screen height %0.2f",screenSize.width,screenSize.height);
		
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
		CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
        sprite.position = ccp(screenSize.width/2, screenSize.height/2-30);
		[self addChild:sprite];
        
        
        CGSize dim;
        dim.width = 300.0f;
        dim.height = 25.0f;
        
        CCLabelFX *label = [CCLabelFX labelWithString:@"Need More Powerups!"
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
        
        label = [CCLabelFX labelWithString:@"Would you like to go to the Store?"
                                dimensions:dim
                                 alignment:CCTextAlignmentCenter
                                  fontName:@"Jacoby ICG Black.ttf"
                                  fontSize:15
                              shadowOffset:CGSizeMake(2,-2)
                                shadowBlur:1.0f
                               shadowColor:ccc4(0,0,0,255)
                                 fillColor:ccc4(230,230,230,255)];
        label.position = ccp(315.0f/2.0f,65);
        [sprite addChild:label];
        
        dim.width = 50.0f;
        dim.height = 35.0f;
        label = [CCLabelFX labelWithString:@"Yes"
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
                                               selector:@selector(yesbuttonPushed:)];
        
        label = [CCLabelFX labelWithString:@"No"
                                dimensions:dim
                                 alignment:CCTextAlignmentCenter
                                  fontName:@"Jacoby ICG Black.ttf"
                                  fontSize:30
                              shadowOffset:CGSizeMake(2,-2)
                                shadowBlur:1.0f
                               shadowColor:ccc4(0,0,0,255)
                                 fillColor:ccc4(237,188,0,255)];
        CCMenuItem *no = [CCMenuItemFont itemWithLabel:label
                                                target:self
                                              selector:@selector(nobuttonPushed:)];
        
        CCMenu *pop = [CCMenu menuWithItems:no, yes, nil];
        pop.position = ccp(315.0f/2.0f,110.0f/2.0f-25);
        [pop alignItemsHorizontallyWithPadding:30];
        
        [sprite addChild:pop];
        
        [sprite setPosition:ccp(sprite.position.x-250.0f,sprite.position.y)];
        [sprite runAction: [CCMoveBy actionWithDuration:0.1f position:ccp(250, 0)]];
        OSAtomicIncrement32(&s_isStorePopupActive);
        //CCLOG(@"PopUp ON");
	}
	return self;
}

-(void) yesbuttonPushed:(id)sender 
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    self.parent.visible = false;
    self.parent.position = ccp(self.parent.position.x-1000,self.parent.position.y);
    [StoreScene setReturnNodes:self.parent second:nil];
    
    [self.parent.parent addChild:[StoreScene node]];
    
    [self StopPopup];
}

-(void) nobuttonPushed:(id)sender
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    [self StopPopup];
}

-(void) StopPopup
{
    //CCLOG(@"PopUp STOP");
    OSAtomicDecrement32(&s_isStorePopupActive);
	id action = [CCSequence actions:
                 [CCMoveBy actionWithDuration:0.1f position:CGPointMake(-250, 0)],
				 [CCCallFuncND actionWithTarget:self selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                 nil];
	
	[self runAction:action ];	
}

-(void) draw
{
	
}

-(void) tick: (ccTime) dt
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
    //CCLOG(@"PopUp OFF");
	// don't forget to call "super dealloc"
	[super dealloc];
}
@end
