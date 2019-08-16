#pragma once
class Calculate
{
public:
	Calculate();

	// Gravity Return Force value
	long double Gravity(
		double m1,double m2, double Gravity, 
		double deltaX, double deltaY, double deltaZ );

	// Resolve 3D vector to 2D 
	// Resolve 2D to 1D + change vector position due to x/y/z being negative
	void ResolveForces(double& xForce, double& yForce, double& zForce, double GravityForce,
		double x1, double x2, double y1, double y2, double z1, double z2);

	//Collison Detection return bool
	bool DetectCollision(double RadiusOne, double RadiusTwo, double deltaX, double deltaY, double deltaZ);

	//Collision Responce
	void CollisionResponce(double& xVel, double& yVel, double& zVel,
		double& x2Vel, double& y2Vel, double& z2Vel,
		double e, double mass1, double mass2);

private:
	long double _distance; 

	long double _ForceXY;
	long double _ForceYZ;
	long double _ForceXZ;
	double _deltaX;
	double _deltaY;
	double _deltaZ;
	long double _xTemp;
	long double _yTemp;
	long double _zTemp;
	int _xSign, _ySign, _zSign;
	long double _registerx; 

	double _px, _py, _pz;
	double k;
	double XVelFinal, YVelFinal, ZVelFinal;
	double X2VelFinal, Y2VelFinal, Z2VelFinal;

};

