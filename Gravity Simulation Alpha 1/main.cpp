#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <GLEW\glew.h>
#include <SDL2\SDL.h>
#undef main
#include "Display.h"
#include "Camera.h"
#include "InputManager.h"
#include "Calculate.h"

using namespace std;

//Particle Structure
struct Particle
{
	int ParticleID;
	double Mass;
	double Radius;
	float R, G, B;
	double xPos, yPos, zPos;
	double xVel, yVel, zVel;
	double xAcc, yAcc, zAcc;
};

int main()
{
	int WIDTH = 1200;
	int HIEGHT = 720;
	int NumofParticles = 2;
	long double mRegister = 0;
	double gravity = 6.67E-11;
	double e = 1;
	long double xForceSum = 0;
	long double yForceSum = 0;
	long double zForceSum = 0;
	double xForce = 0;
	double yForce = 0;
	double zForce = 0;
	bool WindowOpen = false;
	bool MenuOpen = true;
	vector<Particle> _particles;
	Particle tempParticle = {1,200000,0.1,0.0,0.0,1.0,0,0,0,0,0,0,0,0,0};
	
	Display _display(1200, 720, "Sup");
	InputManager _inputManager;
	Calculate _calculate;
	WindowOpen = _display.IsOpen();

	//Create particle vector/array
	
	Camera cam(65, (double)WIDTH / (double)HIEGHT, 0.3f, 1000);
	
	// Insert Menu Stuff here 

	//Load Background image
	//Process input
	//draw text change colour depending on hover over
	//

	//Create particles loop

	for (int i = 0; i < NumofParticles; i++)
	{
		tempParticle.ParticleID = i;
		tempParticle.xPos = (i * 4) - 2;
		//tempParticle.yPos = (i * 1) - 3;
		tempParticle.zPos = -5;
		_particles.push_back(tempParticle);
	}

	_particles[1].G = 0.6;
	//_particles[1].xPos = -1;
	//_particles[1].zPos = -4;

	GLUquadricObj* quad = gluNewQuadric();
	while (WindowOpen == true)
	{
		//Main sim process loop
		//Process Input
		//Check if window has been closed
		if (_inputManager.SimProcessInput() == 0){ WindowOpen = false; }
		
		glLoadIdentity();
		cam.setView();

		//Main for loop that calculates new velocities
		for (auto &i : _particles)
		{

			xForceSum = 0;
			yForceSum = 0;
			zForceSum = 0;
			// loop through every other particle
			for (auto &j : _particles)
			{
				// check if particle is the same
				if (i.ParticleID != j.ParticleID)
				{
					//Check if colliding DetectColision()
					if (_calculate.DetectCollision(i.Radius, j.Radius,
						i.xPos - j.xPos,
						i.yPos - j.yPos,
						i.zPos - j.zPos))
					{
						//Resolve the collision
						_calculate.CollisionResponce(i.xVel, i.yVel, i.zVel,
							j.xVel, j.yVel, j.zVel, e, i.Mass, j.Mass);
						//Update positions
						i.xPos += i.xVel;
						i.yPos += i.yVel;
						i.zPos += i.zVel;

						j.xPos += j.xVel;
						j.yPos += j.yVel;
						j.zPos += j.zVel;
					}
					else
					{
						// Cal particle gravity
						mRegister = _calculate.Gravity(i.Mass, j.Mass, gravity,
							i.xPos - j.xPos,
							i.yPos - j.yPos,
							i.zPos - j.zPos);
						// Cal particle velocity
						_calculate.ResolveForces(xForce, yForce, zForce, mRegister,
							i.xPos, j.xPos,
							i.yPos, j.yPos,
							i.zPos, j.zPos);
						xForceSum = xForceSum + xForce;
						yForceSum = yForceSum + yForce;
						zForceSum = zForceSum + zForce;
					}
				}	
			}

			//Update positions from acc
			
			// Acc = Force / Mass
			// Velocity = Velocity + Acc
			// Position = Position + Velocity
			
			i.xAcc = xForceSum / i.Mass;
			i.yAcc = yForceSum / i.Mass;
			i.zAcc = zForceSum / i.Mass;

			i.xVel += i.xAcc;
			i.yVel += i.yAcc;
			i.zVel += i.zAcc;

		}
		
		for (auto &i : _particles)
		{
			i.xPos += i.xVel;
			i.yPos += i.yVel;
			i.zPos += i.zVel;

			//Set sphere colour
			glColor4f(i.R, i.G, i.B, 1.0f);
			//Draw the particle
			glPushMatrix();
			glTranslatef((float)i.xPos, (float)i.yPos, (float)i.zPos);
			gluSphere(quad, i.Radius, 20, 5);
			glPopMatrix();

			//Print the force
			if (i.ParticleID == 1)
			{
				cout << i.zAcc << endl;
			}
			else { cout << i.zAcc << "  "; }
		}

		_display.ChangeBuffer();

	}
	return 0;
}