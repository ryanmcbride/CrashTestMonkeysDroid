#include "Biped.h"
#include "BipedDef.h"

Biped::Biped(b2World* w, const b2Vec2& position, b2Transform& xform, b2Vec2 *linearVel, float *angularVel)				
{
	m_world = w;

	BipedDef def;
	b2BodyDef bd;
	
	int i = 0;

	// create body parts
	bd = def.LFootDef;
	//bd.position += position;
	allPieces[i++] = LFoot = w->CreateBody(&bd);
	LFoot->CreateFixture(&def.LFootPolyfix);
	LFoot->ResetMassData();

	bd = def.RFootDef;
	//bd.position += position;
	allPieces[i++] = RFoot = w->CreateBody(&bd);
	RFoot->CreateFixture(&def.RFootPolyfix);
	RFoot->ResetMassData();

	bd = def.LCalfDef;
	//bd.position += position;
	allPieces[i++] = LCalf = w->CreateBody(&bd);
	LCalf->CreateFixture(&def.LCalfPolyfix);
	LCalf->ResetMassData();

	bd = def.RCalfDef;
	//bd.position += position;
	allPieces[i++] = RCalf = w->CreateBody(&bd);
	RCalf->CreateFixture(&def.RCalfPolyfix);
	RCalf->ResetMassData();

	bd = def.LThighDef;
	//bd.position += position;
	allPieces[i++] = LThigh = w->CreateBody(&bd);
	LThigh->CreateFixture(&def.LThighPolyfix);
	LThigh->ResetMassData();

	bd = def.RThighDef;
	//bd.position += position;
	allPieces[i++] = RThigh = w->CreateBody(&bd);
	RThigh->CreateFixture(&def.RThighPolyfix);
	RThigh->ResetMassData();

	bd = def.PelvisDef;
	//bd.position += position;
	allPieces[i++] = Pelvis = w->CreateBody(&bd);
	Pelvis->CreateFixture(&def.PelvisPolyfix);
	Pelvis->ResetMassData();

	bd = def.StomachDef;
	//bd.position += position;
	allPieces[i++] = Stomach = w->CreateBody(&bd);
	Stomach->CreateFixture(&def.StomachPolyfix);
	Stomach->ResetMassData();

	bd = def.ChestDef;
	//bd.position += position;
	allPieces[i++] = Chest = w->CreateBody(&bd);
	Chest->CreateFixture(&def.ChestPolyfix);
	Chest->ResetMassData();

	bd = def.NeckDef;
	//bd.position += position;
	allPieces[i++] = Neck = w->CreateBody(&bd);
	Neck->CreateFixture(&def.NeckPolyfix);
	Neck->ResetMassData();

	bd = def.HeadDef;
	//bd.position += position;
	allPieces[i++] = Head = w->CreateBody(&bd);
	Head->CreateFixture(&def.HeadCircfix);
	Head->ResetMassData();

	bd = def.LUpperArmDef;
	//bd.position += position;
	allPieces[i++] = LUpperArm = w->CreateBody(&bd);
	LUpperArm->CreateFixture(&def.LUpperArmPolyfix);
	LUpperArm->ResetMassData();

	bd = def.RUpperArmDef;
	//bd.position += position;
	allPieces[i++] = RUpperArm = w->CreateBody(&bd);
	RUpperArm->CreateFixture(&def.RUpperArmPolyfix);
	RUpperArm->ResetMassData();

	bd = def.LForearmDef;
	//bd.position += position;
	allPieces[i++] = LForearm = w->CreateBody(&bd);
	LForearm->CreateFixture(&def.LForearmPolyfix);
	LForearm->ResetMassData();

	bd = def.RForearmDef;
	//bd.position += position;
	allPieces[i++] = RForearm = w->CreateBody(&bd);
	RForearm->CreateFixture(&def.RForearmPolyfix);
	RForearm->ResetMassData();

	bd = def.LHandDef;
	//bd.position += position;
	allPieces[i++] = LHand = w->CreateBody(&bd);
	LHand->CreateFixture(&def.LHandPolyfix);
	LHand->ResetMassData();

	bd = def.RHandDef;
	//bd.position += position;
	allPieces[i++] = RHand = w->CreateBody(&bd);
	RHand->CreateFixture(&def.RHandPolyfix);
	RHand->ResetMassData();
	
	// link body parts
	def.LAnkleDef.bodyA		= LFoot;
	def.LAnkleDef.bodyB		= LCalf;
	def.RAnkleDef.bodyA		= RFoot;
	def.RAnkleDef.bodyB		= RCalf;
	def.LKneeDef.bodyA		= LCalf;
	def.LKneeDef.bodyB		= LThigh;
	def.RKneeDef.bodyA		= RCalf;
	def.RKneeDef.bodyB		= RThigh;
	def.LHipDef.bodyA		= LThigh;
	def.LHipDef.bodyB		= Pelvis;
	def.RHipDef.bodyA		= RThigh;
	def.RHipDef.bodyB		= Pelvis;
	def.LowerAbsDef.bodyA	= Pelvis;
	def.LowerAbsDef.bodyB	= Stomach;
	def.UpperAbsDef.bodyA	= Stomach;
	def.UpperAbsDef.bodyB	= Chest;
	def.LowerNeckDef.bodyA	= Chest;
	def.LowerNeckDef.bodyB	= Neck;
	def.UpperNeckDef.bodyA	= Neck;
	def.UpperNeckDef.bodyB	= Head;
	def.LShoulderDef.bodyA	= Chest;
	def.LShoulderDef.bodyB	= LUpperArm;
	def.RShoulderDef.bodyA	= Chest;
	def.RShoulderDef.bodyB	= RUpperArm;
	def.LElbowDef.bodyA		= LForearm;
	def.LElbowDef.bodyB		= LUpperArm;
	def.RElbowDef.bodyA		= RForearm;
	def.RElbowDef.bodyB		= RUpperArm;
	def.LWristDef.bodyA		= LHand;
	def.LWristDef.bodyB		= LForearm;
	def.RWristDef.bodyA		= RHand;
	def.RWristDef.bodyB		= RForearm;
	
	// create joints
	LAnkle		= (b2RevoluteJoint*)w->CreateJoint(&def.LAnkleDef);
	RAnkle		= (b2RevoluteJoint*)w->CreateJoint(&def.RAnkleDef);
	LKnee		= (b2RevoluteJoint*)w->CreateJoint(&def.LKneeDef);
	RKnee		= (b2RevoluteJoint*)w->CreateJoint(&def.RKneeDef);
	LHip		= (b2RevoluteJoint*)w->CreateJoint(&def.LHipDef);
	RHip		= (b2RevoluteJoint*)w->CreateJoint(&def.RHipDef);
	LowerAbs	= (b2RevoluteJoint*)w->CreateJoint(&def.LowerAbsDef);
	UpperAbs	= (b2RevoluteJoint*)w->CreateJoint(&def.UpperAbsDef);
	LowerNeck	= (b2RevoluteJoint*)w->CreateJoint(&def.LowerNeckDef);
	UpperNeck	= (b2RevoluteJoint*)w->CreateJoint(&def.UpperNeckDef);
	LShoulder	= (b2RevoluteJoint*)w->CreateJoint(&def.LShoulderDef);
	RShoulder	= (b2RevoluteJoint*)w->CreateJoint(&def.RShoulderDef);
	LElbow		= (b2RevoluteJoint*)w->CreateJoint(&def.LElbowDef);
	RElbow		= (b2RevoluteJoint*)w->CreateJoint(&def.RElbowDef);
	LWrist		= (b2RevoluteJoint*)w->CreateJoint(&def.LWristDef);
	RWrist		= (b2RevoluteJoint*)w->CreateJoint(&def.RWristDef);
    
    if(linearVel)
    {
        LFoot->SetLinearVelocity(*linearVel);
        RFoot->SetLinearVelocity(*linearVel); 
        LCalf->SetLinearVelocity(*linearVel); 
        RCalf->SetLinearVelocity(*linearVel); 
        LThigh->SetLinearVelocity(*linearVel); 
        RThigh->SetLinearVelocity(*linearVel);
        Pelvis->SetLinearVelocity(*linearVel); 
        Stomach->SetLinearVelocity(*linearVel); 
        Chest->SetLinearVelocity(*linearVel); 
        Neck->SetLinearVelocity(*linearVel); 
        Head->SetLinearVelocity(*linearVel);
        LUpperArm->SetLinearVelocity(*linearVel); 
        RUpperArm->SetLinearVelocity(*linearVel); 
        LForearm->SetLinearVelocity(*linearVel); 
        RForearm->SetLinearVelocity(*linearVel); 
        LHand->SetLinearVelocity(*linearVel); 
        RHand->SetLinearVelocity(*linearVel);
    }

    if(angularVel)
    {
        LFoot->SetAngularVelocity(*angularVel);
        RFoot->SetAngularVelocity(*angularVel); 
        LCalf->SetAngularVelocity(*angularVel); 
        RCalf->SetAngularVelocity(*angularVel); 
        LThigh->SetAngularVelocity(*angularVel); 
        RThigh->SetAngularVelocity(*angularVel);
        Pelvis->SetAngularVelocity(*angularVel); 
        Stomach->SetAngularVelocity(*angularVel); 
        Chest->SetAngularVelocity(*angularVel); 
        Neck->SetAngularVelocity(*angularVel); 
        Head->SetAngularVelocity(*angularVel);
        LUpperArm->SetAngularVelocity(*angularVel); 
        RUpperArm->SetAngularVelocity(*angularVel); 
        LForearm->SetAngularVelocity(*angularVel); 
        RForearm->SetAngularVelocity(*angularVel); 
        LHand->SetAngularVelocity(*angularVel); 
        RHand->SetAngularVelocity(*angularVel);
    }
	int piecesMax = i;
	for(i = 0; i < piecesMax; i++)
	{
		b2Vec2 newPos = b2Mul(xform.q,allPieces[i]->GetPosition());
		newPos += position;
		
		allPieces[i]->SetTransform(newPos, xform.q.GetAngle());
	}
}


Biped::~Biped(void)
{
	m_world->DestroyBody(LFoot);
	m_world->DestroyBody(RFoot);
	m_world->DestroyBody(LCalf);
	m_world->DestroyBody(RCalf);
	m_world->DestroyBody(LThigh);
	m_world->DestroyBody(RThigh);
	m_world->DestroyBody(Pelvis);
	m_world->DestroyBody(Stomach);
	m_world->DestroyBody(Chest);
	m_world->DestroyBody(Neck);
	m_world->DestroyBody(Head);
	m_world->DestroyBody(LUpperArm);
	m_world->DestroyBody(RUpperArm);
	m_world->DestroyBody(LForearm);
	m_world->DestroyBody(RForearm);
	m_world->DestroyBody(LHand);
	m_world->DestroyBody(RHand);
    
}
