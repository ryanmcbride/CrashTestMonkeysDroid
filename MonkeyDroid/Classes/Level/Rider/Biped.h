#ifndef BIPED_H
#define BIPED_H
#ifdef __cplusplus

#include "box2d.h"

// Ragdoll class thanks to darkzerox.
class Biped
{
public:
	Biped(b2World *world, const b2Vec2& position, b2Transform& xform, b2Vec2 *linearVel=NULL,float *angularVel=NULL);
    ~Biped();

//private:
	b2World* m_world;

	b2Body				*LFoot, *RFoot, *LCalf, *RCalf, *LThigh, *RThigh,
						*Pelvis, *Stomach, *Chest, *Neck, *Head,
						*LUpperArm, *RUpperArm, *LForearm, *RForearm, *LHand, *RHand;
	b2Body				*allPieces[17];

	b2RevoluteJoint		*LAnkle, *RAnkle, *LKnee, *RKnee, *LHip, *RHip, 
						*LowerAbs, *UpperAbs, *LowerNeck, *UpperNeck,
						*LShoulder, *RShoulder, *LElbow, *RElbow, *LWrist, *RWrist;
};

#endif
#endif
