#pragma once

#include <GL/glut.h>
#include "Material.h"

class SolidSphere {
	
public:
	SolidSphere(float r, int sl, int st);
	void setRadius(float r); 
	float getRadius() const; 
	void setSlice(float sl);
	void setStack(float st);
	void setCenter(float x, float y, float z); 
	const float* getCenter() const; 
	void setVelocity(float x, float y, float z); 
	const float* getVelocity() const; 
	void move(); 
	void setMTL(const Material& m);
	void draw() const;

private:
	float radius; 
	int slice; 
	int stack;
	float center[3];
	float velocity[3];
	Material mtl;
};