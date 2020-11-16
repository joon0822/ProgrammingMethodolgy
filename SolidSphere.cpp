#include "SolidSphere.h"

SolidSphere::SolidSphere(float r, int sl, int st) { radius = r; slice = sl; stack = st;}

void SolidSphere::setRadius(float r) { radius = r; }

float SolidSphere::getRadius() const { return radius; }

void SolidSphere::setSlice(float sl) { slice = sl; }

void SolidSphere::setStack(float st) { stack = st; }

void SolidSphere::setCenter(float x, float y, float z) { center[0] = x; center[1] = y; center[2] = z; }

const float* SolidSphere::getCenter() const { return center; }

void SolidSphere::setVelocity(float x, float y, float z) { velocity[0] = x; velocity[1] = y; velocity[2] = z; }

const float* SolidSphere::getVelocity() const { return velocity; }

void SolidSphere::move() {

	velocity[1] -= 0.00015;

	center[0] += velocity[0];
	center[1] += velocity[1];
	center[2] += velocity[2];

	//Boundary condition

	if (center[0] + radius >= 0.887 || center[0] - radius <= -0.887)
		velocity[0] = -velocity[0];
	if (center[1] - radius <= -0.411){
		if (radius > 0.19) velocity[1] = 0.015;
		else if (radius > 0.09) velocity[1] = 0.0125;
		else if (radius > 0.049) velocity[1] = 0.01;
	}
	if (center[2]+radius >= 1.0 || center[2] - radius <= -1.0)
		velocity[2] = -velocity[2];
}

void SolidSphere::setMTL(const Material& m) { mtl = m; }

void SolidSphere::draw() const {

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(radius, slice, stack);
	glPopMatrix();
}