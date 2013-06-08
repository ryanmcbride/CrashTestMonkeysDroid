#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "Box2D.h"

class Spline
{
public:
	Spline();
	Spline(b2Vec2 *points, int numPoints, bool newSpline=true);
	~Spline();
	b2Vec2 GetPosition(float t);
	void Transform(b2Transform *transform);
protected:
	void ComputeIntervals();
	float Blend(int k, int t, int *u, float v);
	b2Vec2 ComputePoint(float v);

	b2Vec2 *m_ControlPoints;
	b2Vec2 *m_ControlPointsOrig;
	int *m_Knots;
	int m_NumPoints;
	b2Transform *m_Transform;
	int m_degree;
	bool m_newSpline;
};
#endif