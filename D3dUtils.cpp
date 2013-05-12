#include "D3dUtils.h"

//---------------------------------------------
// Generates random float.
//---------------------------------------------
float GetRandomFloat(float a, float b)
{
	if( a >= b ) // bad input
		return a;

	// Get random float in [0, 1] interval.
	float f = (rand()%10001) * 0.0001f;

	return (f*(b-a))+a;
}
//---------------------------------------------
// converts form degrees to radian.
//---------------------------------------------
float DegreeToRad(float degrees)
{
	return degrees*(D3DX_PI/180.0f);
}
float RadToDegree(float radian)
{
	return radian*(180.0f/D3DX_PI);
}
//---------------------------------------------