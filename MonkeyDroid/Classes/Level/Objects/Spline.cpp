#include "Spline.h"

Spline::Spline()
{
	m_ControlPoints = NULL;
	m_NumPoints = 0;
	m_Transform = NULL;
	m_degree = 0;
	m_newSpline = false;
}

Spline::Spline(b2Vec2 *points, int numPoints, bool newSpline)
{	
	m_newSpline = newSpline;

	if(newSpline)
	{
		m_ControlPointsOrig = new b2Vec2[numPoints];
		memcpy(m_ControlPointsOrig,points,sizeof(b2Vec2)*numPoints);
	}
	else
	{
		m_ControlPointsOrig = points;
	}

	m_ControlPoints = new b2Vec2[numPoints];
	memcpy(m_ControlPoints,points,sizeof(b2Vec2)*numPoints);
			

	m_NumPoints = numPoints;

	m_Transform = NULL;
	m_degree = 3;

	m_Knots = new int[numPoints+m_degree];
	ComputeIntervals();
}

Spline::~Spline()
{
	if(m_newSpline)
		delete [] m_ControlPoints;

	delete [] m_Knots;
	delete [] m_ControlPointsOrig;

}

b2Vec2 Spline::GetPosition(float t)
{
	b2Vec2 out;
	float interval = t*((float)(m_NumPoints-m_degree+1));
	out = ComputePoint(interval);
    if(t==0.5f)
    {
        out.x /= 2.0f;
        out.y /= 2.0f;
    }
	return out;
}

void Spline::Transform(b2Transform *transform)
{
	m_Transform = transform;
	for(int i =0; i < m_NumPoints; i++)
	{
        m_ControlPoints[i] = b2Mul(*m_Transform,m_ControlPointsOrig[i]);
	}
}


float Spline::Blend(int k, int t, int *u, float v)  // calculate the blending value
{
  float value;

  if (t==1)			// base case for the recursion
  {
    if ((u[k]<=v) && (v<=u[k+1]))
      value=1;
    else
      value=0;
  }
  else
  {
    if ((u[k+t-1]==u[k]) && (u[k+t]==u[k+1]))  // check for divide by zero
      value = 0;
    else
    if (u[k+t-1]==u[k]) // if a term's denominator is zero,use just the other
      value = (u[k+t] - v) / (u[k+t] - u[k+1]) * Blend(k+1, t-1, u, v);
    else
    if (u[k+t]==u[k+1])
      value = (v - u[k]) / (u[k+t-1] - u[k]) * Blend(k, t-1, u, v);
    else
      value = (v - u[k]) / (u[k+t-1] - u[k]) * Blend(k, t-1, u, v) +
	      (u[k+t] - v) / (u[k+t] - u[k+1]) * Blend(k+1, t-1, u, v);
  }
  return value;
}

void Spline::ComputeIntervals()   // figure out the knots
{
  int n=m_NumPoints-1;
  int t=m_degree;
  int j;

  for (j=0; j<=n+t; j++)
  {
    if (j<t)
      m_Knots[j]=0;
    else
    if ((t<=j) && (j<=n))
      m_Knots[j]=j-t+1;
    else
    if (j>n)
      m_Knots[j]=n-t+2;  // if n-t=-2 then we're screwed, everything goes to 0
  }
}

b2Vec2 Spline::ComputePoint(float v)
{
  int k;
  float temp;
  b2Vec2 output;

  // initialize the variables that will hold our outputted point
  output.x=0;
  output.y=0;

  for (k=0; k<=m_NumPoints-1; k++)
  {
    temp = Blend(k,m_degree,m_Knots,v);  // same blend is used for each dimension coordinate
    output.x = output.x + (m_ControlPoints[k]).x * temp;
    output.y = output.y + (m_ControlPoints[k]).y * temp;
  }

  return output;
}
