//Nhung Luu
//Exam 2
//lighting on pyramid

#include<windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<iostream>

//name the prototypes and variables in namespace
using namespace std;
int frame = 1;
//rotation, scale, and tranlation for pyramid
float theta = 0.0, scale = 1, dx = 0, dy = 0, dz = 0.0;
//arrays containing points for pyramid
float bx[5][4], by[5][4], z[5][4];
//array for normal vectors for pyramid
float nVector[5][3];
float light;
void SetupRC(void);
void RenderScene(void);
void calNormal(float[], float[], float[], float[]);
void loadIcon(float[][4], float[][4], float[][4], float[][3]);
void settrans1(void);
void drawIcon(float[][4], float[][4], float[][4], float[][3], float[], float[]);
void TimerFunction(int);

//main
int main(int argc, char** argv) {
	//name header of the window
	char header[] = "pyramid by Nhung Luu";
	//begin setting the window size and position
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(560, 440);
	glutInitWindowPosition(140, 20);
	//calling the methods for setup, renderscene, and timerfunction
	glutCreateWindow(header);
	SetupRC();
	//call loadicon
	loadIcon(bx, by, z, nVector);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
	return 0;
}

//setup method to choose clear color for the window: white
void SetupRC(void) {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	return;
}

//setup rendersene
void RenderScene(void) {
	//name the xdel and float arrays
	float xdel = 0.25;
	//array for light parameters
	float ambientLight[] = { 1.0, 0.0, 0.0, 1.0 };
	float difuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight[] = { 1.0, 0.0, 0.0, 1.0 };

	float ambientLight2[] = { 0.0, 1.0, 0.0, 1.0 };
	float difuseLight2[] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight2[] = { 0.0, 1.0, 0.0, 1.0 };
	//set light position
	float lightPos[] = { -7,8,4,1 };
	float lightPos2[] = { 7,8,4,1 };
	//set reflectant
	float specref[] = { 1,1,1,1 };
	//set spot the light will shine on
	float spotdir[] = { 7, -8, -4 };
	float spotdir2[] = { -7, -8, -4 };
	cout << "in renderscene" << endl;
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 540, 440);
	glOrtho(-10, 10, -10, 10, -10.0, 10.0);
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	//enable lighting
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CW);
	//switch to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//set light poistions
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 5);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdir);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 8);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir2);
	//define the color material of the light
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//make the spot light turn on and off
	int i = theta;
	if ((int(theta) / 90) % 2 == 0) {
		glDisable(GL_LIGHT1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_LIGHT0);
		light = 0;
	}
	else {
		light = 1;
		glDisable(GL_LIGHT0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_LIGHT1);
	}
	glFlush();
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//settans and draw icons
	settrans1();
	drawIcon(bx, by, z, nVector, lightPos, lightPos2);
	glFlush();
	glEnd();
	glutSwapBuffers();
	return;
}

//method to calculate the normal vector
void calNormal(float x[], float y[], float z[], float norm[]) {
	norm[0] = y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]);
	norm[1] = z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]);
	norm[2] = x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]);
	return;
}

//method to load icon with the coordinates
void loadIcon(float bx[][4], float by[][4], float z[][4], float nVector[][3]) {
	float normVec[3], xn[3], yn[3], zn[3];
	float normVec2[3];

	//coordinates for pyramid front
	bx[0][0] = 0; by[0][0] = 5; z[0][0] = 0;
	bx[0][1] = 2; by[0][1] = 0; z[0][1] = 2;
	bx[0][2] = -2; by[0][2] = 0; z[0][2] = 2;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[0][i];
		yn[i] = by[0][i];
		zn[i] = z[0][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[0][0] = normVec[0];
	nVector[0][1] = normVec[1];
	nVector[0][2] = normVec[2];


	//pyramid left
	bx[1][0] = 0; by[1][0] = 5; z[1][0] = 0;
	bx[1][1] = -2; by[1][1] = 0; z[1][1] = 2;
	bx[1][2] = -2; by[1][2] = 0; z[1][2] = -2;
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[1][i];
		yn[i] = by[1][i];
		zn[i] = z[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[1][0] = normVec[0];
	nVector[1][1] = normVec[1];
	nVector[1][2] = normVec[2];

	//pyramid back
	bx[2][0] = 0; by[2][0] = 5; z[2][0] = 0;
	bx[2][1] = -2; by[2][1] = 0; z[2][1] = -2;
	bx[2][2] = 2; by[2][2] = 0; z[2][2] = -2;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[2][i];
		yn[i] = by[2][i];
		zn[i] = z[2][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[2][0] = normVec[0];
	nVector[2][1] = normVec[1];
	nVector[2][2] = normVec[2];

	//pyramid right
	bx[3][0] = 0; by[3][0] = 5; z[3][0] = 0;
	bx[3][1] = 2; by[3][1] = 0; z[3][1] = -2;
	bx[3][2] = 2; by[3][2] = 0; z[3][2] = 2;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[3][i];
		yn[i] = by[3][i];
		zn[i] = z[3][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[3][0] = normVec[0];
	nVector[3][1] = normVec[1];
	nVector[3][2] = normVec[2];

	//pyramid bottom
	bx[4][0] = 2; by[4][0] = 0; z[4][0] = -2;
	bx[4][1] = -2; by[4][1] = 0; z[4][1] = -2;
	bx[4][2] = -2; by[4][2] = 0; z[4][2] = 2;
	bx[4][3] = 2; by[4][3] = 0; z[4][3] = 2;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[4][i];
		yn[i] = by[4][i];
		zn[i] = z[4][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[4][0] = normVec[0];
	nVector[4][1] = normVec[1];
	nVector[4][2] = normVec[2];

	return;
}

//settrans method for pyramid with matrix
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 1.0, 1.0, 0.0);
	return;
}

//method to draw the icons
void drawIcon(float bx[][4], float by[][4], float bz[][4], float nvector[][3], float lightPos[], float lightPos2[]) {
	int i;
	int face;

	//enable normalize
	glEnable(GL_NORMALIZE);

	//draw the shape for the polygon
	for (face = 0; face <= 4; face++) {
		//color for faces
		if (face == 0) glColor3f(1.0, 0.0, 0.0);
		else if (face == 3) glColor3f(0.0, 0.0, 1.0);
		else if (face == 2) glColor3f(1.0, 0.0, 0.0);
		else if (face == 1) glColor3f(0.0, 0.0, 1.0);
		else glColor3f(0.0, 1.0, 0.0);

		glShadeModel(GL_SMOOTH);
		if (face == 4) {
			glBegin(GL_POLYGON);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			for (i = 0; i <= 3; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
		else {
			glBegin(GL_POLYGON);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			for (i = 0; i <= 2; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
	}

	//draw light source
	if (light == 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		glutSolidSphere(0.5, 10, 10);
	}
	else {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
		glutSolidSphere(0.5, 10, 10);
	}

	return;
}

//timerfunction to switch frames
void TimerFunction(int value) {
	theta += 2;

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}