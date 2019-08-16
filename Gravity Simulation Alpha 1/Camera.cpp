#include "Camera.h"


Camera::Camera(double fov, double aspect, double near, double far)
{
	_fov = fov;
	_aspect = aspect;
	_near = near;
	_far = far;

	camX = 0;
	camY = 0;
	camZ = 0;
	RotX = 0;
	RotY = 0;
	RotZ = 0;

	init();
}

void Camera::init(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fov, _aspect, _near, _far);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setView(){

	glRotatef(RotX, 1, 0, 0); //Rotate Camera X angle = 0
	glRotatef(RotY, 0, 1, 0);	//Y
	glRotatef(RotZ, 0, 0, 1); //Z
	glTranslatef(camX, camY, camZ); //Camera Position

}

//Setters

void Camera::setCamX(float x){ camX = x; }
void Camera::setCamY(float y){ camY = y; }
void Camera::setCamZ(float z){ camZ = z; }

void Camera::setRotX(float rx){ RotX = rx; }
void Camera::setRotY(float ry){ RotY = ry; }
void Camera::setRotZ(float rz){ RotZ = rz; }


