#include "Calculate.h"
#include <math.h>

Calculate::Calculate()
{
}

long double Calculate::Gravity(
	double m1, double m2, double Gravity,
	double deltaX, double deltaY, double deltaZ)
{
	_distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
	return (m1*m2*Gravity) / _distance;
}

void Calculate::ResolveForces(double& xForce, double& yForce, double& zForce, double GravityForce,
	double x1, double x2, double y1, double y2, double z1, double z2)
{
	_registerx = 0;
	_xTemp = 0;
	_yTemp = 0;
	_zTemp = 0;
	_ForceXY = _ForceXZ = _ForceYZ = 0;
	_xSign = _ySign = _zSign = 0;

	//Calculate change in disatnces
	_deltaX = x2 - x1;
	_deltaY = y2 - y1;
	_deltaZ = z2 - z1;
	//Resolve in XY plane
	_registerx = atan2(fabs(_deltaZ),sqrt(pow(_deltaX,2) + pow(_deltaY,2)));
	_ForceXY = GravityForce * cos(_registerx);
	//Resolve in YZ plane
	_registerx = atan2(fabs(_deltaX), sqrt(pow(_deltaY, 2) + pow(_deltaZ, 2)));
	_ForceYZ = GravityForce * cos(_registerx);
	//Resolve in XZ plane
	_registerx = atan2(fabs(_deltaY), sqrt(pow(_deltaX, 2) + pow(_deltaZ, 2)));
	_ForceXZ = GravityForce * cos(_registerx);

	if (x1 - x2 > 0){ _xSign = -1; } 
	else { _xSign = 1; }
	if (y1 - y2 > 0){ _ySign = -1; }
	else { _ySign = 1; }
	if (z1 - z2 > 0){ _zSign = -1; }
	else { _zSign = 1; }
	//Resolve Plane Forces into XYZ forces
	_registerx = atan2(fabs(_deltaY) , fabs(_deltaX));
	_xTemp = _xSign * (_ForceXY * cos(_registerx));
	_yTemp = _ySign * (_ForceXY * sin(_registerx));

	_registerx = atan2(fabs(_deltaY), fabs(_deltaZ));
	_yTemp = _yTemp + _ySign * (_ForceYZ * sin(_registerx));
	_zTemp = _zTemp + _zSign * (_ForceYZ * cos(_registerx));

	_registerx = atan2(fabs(_deltaZ), fabs(_deltaX));
	_xTemp = _xTemp + _xSign * (_ForceXZ * cos(_registerx));
	_zTemp = _zTemp + _zSign * (_ForceXZ * sin(_registerx));

	//Assign X Y Z Force

	xForce = _xTemp;
	yForce = _yTemp;
	zForce = _zTemp;

	// 
	// ADD IN OTHERS !!!! 
	//
}

bool Calculate::DetectCollision(double RadiusOne, double RadiusTwo, double deltaX, double deltaY, double deltaZ)
{
	long double d = 0;
	d = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
	if (d <= (RadiusOne + RadiusTwo))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Calculate::CollisionResponce(double& xVel, double& yVel, double& zVel,
	double& x2Vel, double& y2Vel,double& z2Vel, 
	double e, double mass1, double mass2)
{
	k = 0;
	_px = _py = _pz = 0;
	XVelFinal = YVelFinal = ZVelFinal = 0;
	X2VelFinal = Y2VelFinal = Z2VelFinal = 0;

	_px = xVel*mass1 + x2Vel*mass2;
	_py = yVel*mass1 + y2Vel*mass2;
	_pz = zVel*mass1 + z2Vel*mass2;

	k = e*(xVel - x2Vel);

	XVelFinal = (_px - k*mass2) / (mass1 + mass2);
	X2VelFinal = k + XVelFinal;

	k = e*(yVel - y2Vel);

	YVelFinal = (_py - k*mass2) / (mass1 + mass2);
	Y2VelFinal = k + YVelFinal;

	k = e*(zVel - z2Vel);

	ZVelFinal = (_pz - k*mass2) / (mass1 + mass2);
	Z2VelFinal = k + ZVelFinal;

	xVel = XVelFinal;
	yVel = YVelFinal;
	zVel = ZVelFinal;

	x2Vel = X2VelFinal;
	y2Vel = Y2VelFinal;
	z2Vel = Z2VelFinal;

}
