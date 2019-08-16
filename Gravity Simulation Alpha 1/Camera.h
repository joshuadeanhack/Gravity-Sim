#pragma once
#include <GLEW\glew.h>
class Camera
{
public:
	Camera(double fov, double aspect, double near, double far);
	
	void init();
	void setView();

	//Setters
	void setCamX(float x);
	void setCamY(float y);
	void setCamZ(float z);

	void setRotX(float rx);
	void setRotY(float ry);
	void setRotZ(float rz);

private:
	double _fov;
	double _aspect;
	double _near;
	double _far;

	float camX;
	float camY;
	float camZ;

	float RotX;
	float RotY;
	float RotZ;
};

