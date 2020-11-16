#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/FreeImage.h>
#include "Light.h"
#include "Material.h"
#include "SolidSphere.h"

using namespace std;

#define WIDTH 640
#define HEIGHT 640

static GLuint textureID;
GLubyte* textureData;
int imageWidth, imageHeight;

vector<SolidSphere> solidsphere;
Light light(-30, 30, -30, GL_LIGHT0);

FIBITMAP* createBitMap(char const* filename) {

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	FIBITMAP* bitmap = FreeImage_Load(format, filename);

	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32; if (bitsPerPixel == 32) {
		bitmap32 = bitmap;
	}
	else {
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;

}

void generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void initTexture() {
	FIBITMAP* bitmap32 = createBitMap("inner.png");
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();
}

void drawSquareWithTexture() {

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -0.5, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(1.0, -0.5, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void drawCharacters(void* font, const char* c, float x, float y) {
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(c); i++)
		glutBitmapCharacter(font, c[i]);
}

void initialize() {

	SolidSphere sol1(0.2, 100, 100), sol2(0.1, 100, 100), sol3(0.05, 100, 100);

	sol1.setCenter(0.3, 0.5, 0);
	sol1.setVelocity(0.003, 0.003, 0);
	sol2.setCenter(0, 0, 0);
	sol2.setVelocity(0.001, 0.006, 0);
	sol3.setCenter(-0.2, -0.1, 0);
	sol3.setVelocity(0.006, 0.003, 0);

	Material mtl1, mtl2, mtl3;
	mtl1.setAmbient(0.5, 0.0, 0.0, 0.0);
	mtl1.setDiffuse(1.0, 1.0, 1.0, 1.0);
	mtl1.setEmission(0.0, 0.0, 0.0, 1.0);
	mtl1.setSpecular(1.0, 1.0, 1.0, 1.0);
	mtl1.setShininess(32);
	sol1.setMTL(mtl1);
	mtl2.setAmbient(0.0, 0.5, 0.0, 0.0);
	mtl2.setDiffuse(1.0, 1.0, 1.0, 1.0);
	mtl2.setEmission(0.0, 0.0, 0.0, 1.0);
	mtl2.setSpecular(1.0, 1.0, 1.0, 1.0);
	mtl2.setShininess(32);
	sol2.setMTL(mtl2);
	mtl3.setAmbient(0.0, 0.0, 0.5, 0.0);
	mtl3.setDiffuse(1.0, 1.0, 1.0, 1.0);
	mtl3.setEmission(0.0, 0.0, 0.0, 1.0);
	mtl3.setSpecular(1.0, 1.0, 1.0, 1.0);
	mtl3.setShininess(32);
	sol3.setMTL(mtl3);

	solidsphere.push_back(sol1);
	solidsphere.push_back(sol2);
	solidsphere.push_back(sol3);
}

void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	initTexture();

	drawSquareWithTexture();

	drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "2016-15182 MIN JOONKI", -0.75, -0.75);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();

	solidsphere[0].draw();
	solidsphere[1].draw();
	solidsphere[2].draw();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void idle() {
	solidsphere[0].move();
	solidsphere[1].move();
	solidsphere[2].move();

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Draw three bouncing spheres");

	initialize();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
}