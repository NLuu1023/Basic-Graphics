//Nhung Luu
//final project

#include<windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include"External Libraries\SOIL2\include\SOIL2.h"

//name the prototypes and variables in namespace
using namespace std;
int frame = 1;
//rotation, scale, and tranlation for polyman and polywoman
float theta = 180, scale = 3, dx = 10, dy = -4, dz = 1.0;
float thetaw = 0, scalew = 0.0, dxw = -2, dyw = -5, dzw = 1.0;
//transformations for the present box
float thetap = 0.0, scalep = 1.0, dxp = -2, dyp = -5, dzp = 1.0;
//transformations for present lid
float thetal = 0.0, scalel = 1.0, dxl = -2, dyl = -4.5, dzl = 1.0;
//transformation for star
float thetas = 0.0, scales = 0.0, dxs = -2, dys = -5, dzs = 1.0;
//bezier control points
float xcontrol[10], ycontrol[10], Uval = 0.0;
//arrays containing points for polyman
float bx[6][33], by[6][33], bz[6][33];
//array for polywoman
float wbx[6][33], wby[6][33], wz[6][33];
//array for normal vectors
float nVector[12][3];
float light;
void setStage(void);
void loadPresent(float[][4], float[][4], float[][4]);
void settrans1(void);
void settrans2(void);
void settrans3(void);
void settrans4(void);
void settrans5(void);
void drawStar(float[][4], float[][4], float[][4], float[][3]);
void drawPresent(float[][4], float[][4], float[][4], float[][3]);
void drawPresentLid(float[][4], float[][4], float[][4], float[][3]);
void drawIcon(float[][33], float[][33], float[][33]);
void drawIcon2(float[][33], float[][33], float[][33]);
void loadIcon(float[][33], float[][33], float[][33], float[][33], float[][33], float[][33]);
float calculateBezier(float, int, float[]);
int fact(int);
void SetupRC(void);
void RenderScene(void);
void TimerFunction(int);
//array to hold texture pictures
GLuint textures[6];

//main
int main(int argc, char** argv) {
	//name header of the window
	char header[] = "A Christmas Present";
	//begin setting the window size and position
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(560, 440);
	glutInitWindowPosition(140, 20);
	//calling the methods for setup, renderscene, and timerfunction
	glutCreateWindow(header);
	SetupRC();
	//include all the picture texture
	textures[0] = SOIL_load_OGL_texture("fireplace.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
	textures[1] = SOIL_load_OGL_texture("floor.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
	textures[2] = SOIL_load_OGL_texture("wrapper.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
	textures[3] = SOIL_load_OGL_texture("bow.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
	textures[4] = SOIL_load_OGL_texture("decor.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
	textures[5] = SOIL_load_OGL_texture("star.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);

	//enable 2D texture
	glEnable(GL_TEXTURE_2D);
	//clamp the texture in direction s and t
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//blend in to the nearest pixel at the edges
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//draw the snow mountain
	glutDisplayFunc(RenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
	return 0;
}

//setup method to choose clear color for the window: white
void SetupRC(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	return;
}

//setup rendersene
void RenderScene(void) {
	//name the xdel and float arrays
	float xdel = 0.25;
	//u value for x(u) and y(u)
	float uval;
	//set the control points
	xcontrol[0] = -2; ycontrol[0] = -5;
	xcontrol[1] = -4; ycontrol[1] = 7;
	xcontrol[2] = 4; ycontrol[2] =7;
	xcontrol[3] = 5; ycontrol[3] = -4;
	//points for present and present lid
	float x[12][4], y[12][4], z[12][4];
	//array for light parameters for lamp light:white
	float ambientLight[] = { 1.0, 1.0, 1.0, 1.0 };
	float difuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	//array for the light from star: gold-yellow
	float ambientLight2[] = { 1, 1, 0.0, 1.0 };
	float difuseLight2[] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight2[] = { 1, 1, 0.0, 1.0 };
	//set light position
	float lightPos[] = { 8,7.5,0.5,1 };
	float lightPos2[] = { 7,-6.7,0.5,1 };
	//set reflectant
	float specref[] = { 1,1,1,1 };
	//set spot the light will shine on
	float spotdir[] = { -8, -7.5, -0.5 };
	float spotdir2[] = { -7, 6.7, -0.5 };
	cout << "in renderscene" << endl;
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 540, 440);
	glOrtho(-10, 10, -10, 10, -11.0, 11.0);
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
	glEnable(GL_LIGHT0);
	int i = frame;
	if (i >= 4) {
		glDisable(GL_LIGHT0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_LIGHT1);
		light = 0;
	}
	else {
		light = 1;
		glDisable(GL_LIGHT1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_LIGHT0);
	}
	glFlush();
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//settans and draw icons
	//call loadicon
	loadPresent(x, y, z);
	loadIcon(wbx, wby, wz, bx, by, bz);
	setStage();
	settrans1();
	drawPresent(x, y, z, nVector);
	settrans2();
	drawPresentLid(x, y, z, nVector);
	settrans3();
	drawIcon(wbx, wby, wz);
	if (frame >= 4) {
		settrans4();
		drawIcon2(wbx, wby, wz);
	}
	settrans5();
	drawStar(x, y, z, nVector);
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

//method to set the stage including the background and props
void setStage(void) {
	float normVec[3], xn[3], yn[3], zn[3];
	//points for the wall and floor
	float x[8][11], y[8][11], z[8][11];
	x[0][0] = 10; y[0][0] = 10; z[0][0] = -10;
	x[0][1] = 10; y[0][1] = -3; z[0][1] = -10;
	x[0][2] = -10; y[0][2] = -3; z[0][2] = -10;
	x[0][3] = -10; y[0][3] = 10; z[0][3] = -10;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[0][i];
		yn[i] = y[0][i];
		zn[i] = z[0][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[0][0] = normVec[0];
	nVector[0][1] = normVec[1];
	nVector[0][2] = normVec[2];
	x[1][0] = 10; y[1][0] = -3; z[1][0] = -10;
	x[1][1] = 10; y[1][1] = -10; z[1][1] = 10;
	x[1][2] = -10; y[1][2] = -10; z[1][2] = 10;
	x[1][3] = -10; y[1][3] = -3; z[1][3] = -10;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[1][i];
		yn[i] = y[1][i];
		zn[i] = z[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[1][0] = normVec[0];
	nVector[1][1] = normVec[1];
	nVector[1][2] = normVec[2];

	//points for the christmas tree
	//trunk
	x[2][0] = -6.5; y[2][0] = -3; z[2][0] = 0.0;
	x[2][1] = -6.5; y[2][1] = -5; z[2][1] = 0.0;
	x[2][2] = -7.5; y[2][2] = -5; z[2][2] = 0.0;
	x[2][3] = -7.5; y[2][3] = -3; z[2][3] = 0.0;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[2][i];
		yn[i] = y[2][i];
		zn[i] = z[2][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[2][0] = normVec[0];
	nVector[2][1] = normVec[1];
	nVector[2][2] = normVec[2];
	//tree
	x[3][0] = -10; y[3][0] = -3; z[3][0] = 0.0;
	x[3][1] = -7; y[3][1] = 7; z[3][1] = 0.0;
	x[3][2] = -6.5; y[3][2] = 7; z[3][2] = 0.0;
	x[3][3] = -4; y[3][3] = -3; z[3][3] = 0.0;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[3][i];
		yn[i] = y[3][i];
		zn[i] = z[3][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[3][0] = normVec[0];
	nVector[3][1] = normVec[1];
	nVector[3][2] = normVec[2];

	//points for the lamp
	//base
	x[4][0] = 10; y[4][0] = -3; z[4][0] = 0;
	x[4][1] = 10; y[4][1] = -3.5; z[4][1] = 0;
	x[4][2] = 8; y[4][2] = -3.5; z[4][2] = 0;
	x[4][3] = 8; y[4][3] = -3; z[4][3] = 0;
	//stand
	x[4][4] = 9; y[4][4] = -3; z[4][4] = 0.0;
	x[4][5] = 9; y[4][5] = 9; z[4][5] = 0.0;
	x[4][6] = 8; y[4][6] = 7.5; z[4][6] = 0.0;
	//head
	x[4][7] = 8; y[4][7] = 7.5; z[4][7] = 0.5;
	x[4][8] = 8.5; y[4][8] = 6; z[4][8] = 0.5;
	x[4][9] = 6.5; y[4][9] = 7.5; z[4][9] = 0.5;

	float s[4] = { 1.0, 1.0, 0.0, 0.0 }, t[4] = { 0.0, 1.0, 1.0, 0.0 };

	//enable normalize
	glEnable(GL_NORMALIZE);

	//draw the wall and floor
	for (int i = 0; i <= 2; i++) {
		if (i == 0) {
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		}
		else if (i == 1) {
			glColor3f(0.5, 0.5, 0.5);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		}
		else if (i == 2) {
			glColor3f(0.0, 0.0, 0.0);
		}
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 3; j++) {
			glNormal3f(nVector[i][0], nVector[i][1], nVector[i][2]);
			glTexCoord2f(s[j], t[j]);
			glVertex3f(x[i][j], y[i][j], z[i][j]);
		}
		glEnd();
	}

	//draw the christmas tree
	glColor3f(0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (int j = 0; j <= 3; j++) {
		glNormal3f(nVector[3][0], nVector[3][1], nVector[3][2]);
		glTexCoord2f(s[j], t[j]);
		glVertex3f(x[3][j], y[3][j], z[3][j]);
	}
	glEnd();

	//draw the lamp
	glColor3f(1.0, 1, 0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (int j = 0; j <= 3; j++) {
		glNormal3f(nVector[4][0], nVector[4][1], nVector[4][2]);
		glVertex3f(x[4][j], y[4][j], z[4][j]);
	}
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (int j = 4; j <= 6; j++) {
		glVertex3f(x[4][j], y[4][j], z[4][j]);
	}
	glEnd();
	glColor3f(1,1,0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (int j = 7; j <= 9; j++) {
		glNormal3f(nVector[4][0], nVector[4][1], nVector[4][2]);
		glVertex3f(x[4][j], y[4][j], z[4][j]);
	}
	glEnd();
	
	return;
}

//method to load present points
void loadPresent(float x[][4], float y[][4], float z[][4]) {
	float normVec[3], xn[3], yn[3], zn[3];
	//load present
	//front
	x[0][0] = 1; y[0][0] = 1; z[0][0] = 1.0;
	x[0][1] = 1; y[0][1] = -1; z[0][1] = 1.0;
	x[0][2] = -1; y[0][2] = -1; z[0][2] = 1.0;
	x[0][3] = -1; y[0][3] = 1; z[0][3] = 1.0;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[0][i];
		yn[i] = y[0][i];
		zn[i] = z[0][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[0][0] = normVec[0];
	nVector[0][1] = normVec[1];
	nVector[0][2] = normVec[2];
	//left
	x[1][0] = -1; y[1][0] = 1; z[1][0] = 1;
	x[1][1] = -1; y[1][1] = -1; z[1][1] = 1;
	x[1][2] = -1; y[1][2] = -1; z[1][2] = -1;
	x[1][3] = -1; y[1][3] = 1; z[1][3] = -1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[1][i];
		yn[i] = y[1][i];
		zn[i] = z[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[1][0] = normVec[0];
	nVector[1][1] = normVec[1];
	nVector[1][2] = normVec[2];
	//back
	x[2][0] = -1; y[2][0] = 1; z[2][0] = -1;
	x[2][1] = -1; y[2][1] = -1; z[2][1] = -1;
	x[2][2] = 1; y[2][2] = -1; z[2][2] = -1;
	x[2][3] = 1; y[2][3] = 1; z[2][3] = -1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[2][i];
		yn[i] = y[2][i];
		zn[i] = z[2][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[2][0] = normVec[0];
	nVector[2][1] = normVec[1];
	nVector[2][2] = normVec[2];
	//right
	x[3][0] = 1; y[3][0] = 1; z[3][0] = 1;
	x[3][1] = 1; y[3][1] = 1; z[3][1] = -1;
	x[3][2] = 1; y[3][2] = -1; z[3][2] = -1;
	x[3][3] = 1; y[3][3] = -1; z[3][3] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[3][i];
		yn[i] = y[3][i];
		zn[i] = z[3][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[3][0] = normVec[0];
	nVector[3][1] = normVec[1];
	nVector[3][2] = normVec[2];
	//top
	x[4][0] = 1; y[4][0] = 1; z[4][0] = 1;
	x[4][1] = -1; y[4][1] = 1; z[4][1] = 1;
	x[4][2] = -1; y[4][2] = 1; z[4][2] = -1;
	x[4][3] = 1; y[4][3] = 1; z[4][3] = -1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[4][i];
		yn[i] = y[4][i];
		zn[i] = z[4][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[4][0] = normVec[0];
	nVector[4][1] = normVec[1];
	nVector[4][2] = normVec[2];
	//bottom
	x[5][0] = 1; y[4][0] = 1; z[5][0] = 1;
	x[5][1] = 1; y[4][1] = 1; z[5][1] = -1;
	x[5][2] = -1; y[4][2] = 1; z[5][2] = -1;
	x[5][3] = -1; y[4][3] = 1; z[5][3] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[5][i];
		yn[i] = y[5][i];
		zn[i] = z[5][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[5][0] = normVec[0];
	nVector[5][1] = normVec[1];
	nVector[5][2] = normVec[2];

	//lid points----------------------------------------------------------------------
	//front
	x[6][0] = 1; y[6][0] = 1; z[6][0] = 1;
	x[6][1] = 1; y[6][1] = 0.5; z[6][1] = 1;
	x[6][2] = -1; y[6][2] = 0.5; z[6][2] = 1;
	x[6][3] = -1; y[6][3] = 1; z[6][3] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[6][i];
		yn[i] = y[6][i];
		zn[i] = z[6][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[6][0] = normVec[0];
	nVector[6][1] = normVec[1];
	nVector[6][2] = normVec[2];
	//left
	x[7][0] = -1; y[7][0] = 1; z[7][0] = 1;
	x[7][1] = -1; y[7][1] = 0.5; z[7][1] = 1;
	x[7][2] = -1; y[7][2] = 0.5; z[7][2] = -1;
	x[7][3] = -1; y[7][3] = 1; z[7][3] = -1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[7][i];
		yn[i] = y[7][i];
		zn[i] = z[7][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[7][0] = normVec[0];
	nVector[7][1] = normVec[1];
	nVector[7][2] = normVec[2];
	//back
	x[8][0] = 1; y[8][0] = 1; z[8][0] = -1;
	x[8][1] = -1; y[8][1] = 1; z[8][1] = -1;
	x[8][2] = -1; y[8][2] = 0.5; z[8][2] = -1;
	x[8][3] = 1; y[8][3] = 0.5; z[8][3] = -1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[8][i];
		yn[i] = y[8][i];
		zn[i] = z[8][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[8][0] = normVec[0];
	nVector[8][1] = normVec[1];
	nVector[8][2] = normVec[2];
	//right
	x[9][0] = 1; y[9][0] = 1; z[9][0] = 1;
	x[9][1] = 1; y[9][1] = 1; z[9][1] = -1;
	x[9][2] = 1; y[9][2] = 0.5; z[9][2] = -1;
	x[9][3] = 1; y[9][3] = 0.5; z[9][3] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = x[9][i];
		yn[i] = y[9][i];
		zn[i] = z[9][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[9][0] = normVec[0];
	nVector[9][1] = normVec[1];
	nVector[9][2] = normVec[2];

	return;
}

//method to load polyman, polywoman, and angel
void loadIcon(float wbx[][33], float wby[][33], float wz[][33], float bx[][33], float by[][33], float bz[][33]) {
	float normVec[3], xn[3], yn[3], zn[3];
	float normVec2[3];

	//points for polyman and woman
	wbx[0][0] = -1.125; wby[0][0] = 0.0; wz[0][0] = 1;
	wbx[0][1] = -0.625; wby[0][1] = 0.75; wz[0][1] = 1;
	wbx[0][2] = 0.625; wby[0][2] = 0.75; wz[0][2] = 1;
	wbx[0][3] = 1.125; wby[0][3] = 0.0; wz[0][3] = 1;
	wbx[0][4] = 0.625; wby[0][4] = -0.75; wz[0][4] = 1;
	wbx[0][5] = -0.625; wby[0][5] = -0.75; wz[0][5] = 1;

	//points for mouth
	wbx[0][6] = 0.375; wby[0][6] = 0.0; wz[0][6] = 1;
	wbx[0][7] = 0.875; wby[0][7] = -0.5; wz[0][7] = 1;
	//points for legs
	wbx[0][8] = -0.25; wby[0][8] = -0.5; wz[0][8] = 0.5;
	wbx[0][9] = -0.25; wby[0][9] = -1.0; wz[0][9] = 0.5;
	wbx[0][10] = 0; wby[0][10] = -1.0; wz[0][10] = 0.5;
	wbx[0][11] = 0.25; wby[0][11] = -0.5; wz[0][11] = 1;
	wbx[0][12] = 0.25; wby[0][12] = -1.0; wz[0][12] = 1;
	wbx[0][13] = 0.5; wby[0][13] = -1.0; wz[0][13] = 1;
	//points for eyes
	wbx[0][14] = 0.5; wby[0][14] = 0.5; wz[0][14] = 1;
	//points for corn rows
	wbx[0][15] = 0.25; wby[0][15] = 0.75; wz[0][15] = 1;
	wbx[0][16] = 0.25; wby[0][16] = 0.5; wz[0][16] = 1;
	wbx[0][17] = 0.0; wby[0][17] = 0.75; wz[0][17] = 1;
	wbx[0][18] = 0.0; wby[0][18] = 0.5; wz[0][18] = 1;
	wbx[0][19] = -0.25; wby[0][19] = 0.75; wz[0][19] = 1;
	wbx[0][20] = -0.25; wby[0][20] = 0.5; wz[0][20] = 1;
	//bows
	wbx[0][21] = 0.35; wby[0][21] = 0.5; wz[0][21] = 1;
	wbx[0][22] = 0.35; wby[0][22] = 0.4; wz[0][22] = 1;
	wbx[0][23] = 0.15; wby[0][23] = 0.4; wz[0][23] = 1;
	wbx[0][24] = 0.15; wby[0][24] = 0.5; wz[0][24] = 1;
	wbx[0][25] = 0.10; wby[0][25] = 0.5; wz[0][25] = 1;
	wbx[0][26] = 0.10; wby[0][26] = 0.4; wz[0][26] = 1;
	wbx[0][27] = -0.10; wby[0][27] = 0.4; wz[0][27] = 1;
	wbx[0][28] = -0.10; wby[0][28] = 0.5; wz[0][28] = 1;
	wbx[0][29] = -0.15; wby[0][29] = 0.5; wz[0][29] = 1;
	wbx[0][30] = -0.15; wby[0][30] = 0.4; wz[0][30] = 1;
	wbx[0][31] = -0.35; wby[0][31] = 0.4; wz[0][31] = 1;
	wbx[0][32] = -0.35; wby[0][32] = 0.5; wz[0][32] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[0][i];
		yn[i] = wby[0][i];
		zn[i] = wz[0][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[0][0] = normVec[0];
	nVector[0][1] = normVec[1];
	nVector[0][2] = normVec[2];

	//polywoman left
	wbx[1][0] = -1.125; wby[1][0] = 0.0; wz[1][0] = 1;
	wbx[1][1] = -0.625; wby[1][1] = -0.75; wz[1][1] = 1;
	wbx[1][2] = -0.625; wby[1][2] = -0.75; wz[1][2] = 0.5;
	wbx[1][3] = -1.125; wby[1][3] = 0.0; wz[1][3] = 0.5;
	wbx[1][4] = -0.625; wby[1][4] = 0.75; wz[1][4] = 0.5;
	wbx[1][5] = -0.625; wby[1][5] = 0.75; wz[1][5] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[1][i];
		yn[i] = wby[1][i];
		zn[i] = wz[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[1][0] = normVec[0];
	nVector[1][1] = normVec[1];
	nVector[1][2] = normVec[2];

	//polywoman back
	wbx[2][0] = -1.125; wby[2][0] = 0.0; wz[2][0] = 0.5;
	wbx[2][1] = -0.625; wby[2][1] = -0.75; wz[2][1] = 0.5;
	wbx[2][2] = 0.625; wby[2][2] = -0.75; wz[2][2] = 0.5;
	wbx[2][3] = 1.125; wby[2][3] = 0.0; wz[2][3] = 0.5;
	wbx[2][4] = 0.625; wby[2][4] = 0.75; wz[2][4] = 0.5;
	wbx[2][5] = -0.625; wby[2][5] = 0.75; wz[2][5] = 0.5;
	//points for mouth
	wbx[2][6] = 0.375; wby[2][6] = 0.0; wz[2][6] = 0.5;
	wbx[2][7] = 0.875; wby[2][7] = -0.5; wz[2][7] = 0.5;
	//points for eyes
	wbx[2][14] = 0.5; wby[2][14] = 0.5; wz[2][14] = 0.5;
	//points for corn rows
	wbx[2][15] = 0.25; wby[2][15] = 0.75; wz[2][15] = 0.5;
	wbx[2][16] = 0.25; wby[2][16] = 0.5; wz[2][16] = 0.5;
	wbx[2][17] = 0.0; wby[2][17] = 0.75; wz[2][17] = 0.5;
	wbx[2][18] = 0.0; wby[2][18] = 0.5; wz[2][18] = 0.5;
	wbx[2][19] = -0.25; wby[2][19] = 0.75; wz[2][19] = 0.5;
	wbx[2][20] = -0.25; wby[2][20] = 0.5; wz[2][20] = 0.5;
	//bows
	wbx[2][21] = 0.35; wby[2][21] = 0.5; wz[2][21] = 0.5;
	wbx[2][22] = 0.15; wby[2][22] = 0.5; wz[2][22] = 0.5;
	wbx[2][23] = 0.15; wby[2][23] = 0.4; wz[2][23] = 0.5;
	wbx[2][24] = 0.35; wby[2][24] = 0.4; wz[2][24] = 0.5;
	wbx[2][25] = 0.10; wby[2][25] = 0.5; wz[2][25] = 0.5;
	wbx[2][26] = -0.10; wby[2][26] = 0.5; wz[2][26] = 0.5;
	wbx[2][27] = -0.10; wby[2][27] = 0.4; wz[2][27] = 0.5;
	wbx[2][28] = 0.10; wby[2][28] = 0.4; wz[2][28] = 0.5;
	wbx[2][29] = -0.15; wby[2][29] = 0.5; wz[2][29] = 0.5;
	wbx[2][30] = -0.35; wby[2][30] = 0.5; wz[2][30] = 0.5;
	wbx[2][31] = -0.35; wby[2][31] = 0.4; wz[2][31] = 0.5;
	wbx[2][32] = -0.15; wby[2][32] = 0.4; wz[2][32] = 0.5;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[2][i];
		yn[i] = wby[2][i];
		zn[i] = wz[2][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[2][0] = normVec[0];
	nVector[2][1] = normVec[1];
	nVector[2][2] = normVec[2];

	//polywoman right
	wbx[3][0] = 1.125; wby[3][0] = 0.0; wz[3][0] = 1;
	wbx[3][1] = 0.625; wby[3][1] = 0.75; wz[3][1] = 1;
	wbx[3][2] = 0.625; wby[3][2] = 0.75; wz[3][2] = 0.5;
	wbx[3][3] = 1.125; wby[3][3] = 0.0; wz[3][3] = 0.5;
	wbx[3][4] = 0.625; wby[3][4] = -0.75; wz[3][4] = 0.5;
	wbx[3][5] = 0.625; wby[3][5] = -0.75; wz[3][5] = 1;
	//points for mouth
	wbx[3][6] = 0.875; wby[3][6] = -0.5; wz[3][6] = 1;
	wbx[3][7] = 0.875; wby[3][7] = -0.5; wz[3][7] = 0.5;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[3][i];
		yn[i] = wby[3][i];
		zn[i] = wz[3][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[3][0] = normVec[0];
	nVector[3][1] = normVec[1];
	nVector[3][2] = normVec[2];

	//polyman top
	wbx[4][0] = -0.625; wby[4][0] = 0.75; wz[4][0] = 1;
	wbx[4][1] = -0.625; wby[4][1] = 0.75; wz[4][1] = 0.5;
	wbx[4][2] = 0.625; wby[4][2] = 0.75; wz[4][2] = 0.5;
	wbx[4][3] = 0.625; wby[4][3] = 0.75; wz[4][3] = 1;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[4][i];
		yn[i] = wby[4][i];
		zn[i] = wz[4][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[4][0] = normVec[0];
	nVector[4][1] = normVec[1];
	nVector[4][2] = normVec[2];

	//polyman bottom

	wbx[5][0] = -0.625; wby[5][0] = -0.75; wz[5][0] = 1;
	wbx[5][1] = 0.625; wby[5][1] = -0.75; wz[5][1] = 1;
	wbx[5][2] = 0.625; wby[5][2] = -0.75; wz[5][2] = 0.5;
	wbx[5][3] = -0.625; wby[5][3] = -0.75; wz[5][3] = 0.5;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = wbx[5][i];
		yn[i] = wby[5][i];
		zn[i] = wz[5][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[5][0] = normVec[0];
	nVector[5][1] = normVec[1];
	nVector[5][2] = normVec[2];

	return;
}

//draw polyman
void drawIcon(float bx[][33], float by[][33], float bz[][33]) {
	int i;
	int j = dx;
	int face;

	glEnable(GL_NORMALIZE);

	glLineWidth(3);

	//draw the shape for the polygon
	for (face = 0; face <= 5; face++) {
		if (face == 4 || face == 5) {
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			glColor3f(1.0, 0.0, 0.0);
			for (i = 0; i <= 3; i++) {
				glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
				glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			}
			glEnd();
		}
		else {
			if (face == 1 || face == 3) glColor3f(1.0, 1.0, 0.0);
			else glColor3f(0.0, 1.0, 0.0);
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			for (i = 0; i <= 5; i++) {
				glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
				glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			}
			glEnd();
		}
	}

	//draw the legs, each leg take turn up and down when dx is even or odd
	if (j % 2) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (i = 8; i <= 10; i++) {
			glVertex3f(bx[0][i], by[0][i] + 0.15, bz[0][i]);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 11; i <= 13; i++) {
			glVertex3f(bx[0][i], by[0][i], bz[0][i]);
		}
		glEnd();
	}
	else {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (i = 11; i <= 13; i++) {
			glVertex3f(bx[0][i], by[0][i] + 0.15, bz[0][i]);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 8; i <= 10; i++) {
			glVertex3f(bx[0][i], by[0][i], bz[0][i]);
		}
		glEnd();
	}

	//draw the mouth
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(bx[0][6], by[0][6], bz[0][6] + 0.01);
	glVertex3f(bx[0][7] - 0.01, by[0][7] - 0.01, bz[0][7] + 0.01);
	glVertex3f(bx[2][7] - 0.01, by[2][7] - 0.01, bz[2][7] - 0.01);
	glVertex3f(bx[2][6], by[2][6], bz[2][6] - 0.01);
	glEnd();

	//draw the eyes
	glColor3f(1.0, 1.0, 1.0);
	//front eye
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(bx[0][14], by[0][14], bz[0][14] + 0.01);
	glEnd();
	//back eye
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(bx[2][14], by[2][14], bz[2][14] - 0.01);
	glEnd();

	return;
}

//draw polywoman
void drawIcon2(float bx[][33], float by[][33], float bz[][33]) {
	int i;
	int j = dxw;
	int face;

	glEnable(GL_NORMALIZE);

	//draw the shape for the polygon
	for (face = 0; face <= 5; face++) {
		if (face == 4 || face == 5) {
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			glColor3f(1.0, 0.0, 1.0);
			for (i = 0; i <= 3; i++) {
				glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
				glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			}
			glEnd();
		}
		else {
			if (face == 1 || face == 3) glColor3f(1.0, 1.0, 0.0);
			else glColor3f(1.0, 0.0, 0.0);
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			for (i = 0; i <= 5; i++) {
				glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
				glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			}
			glEnd();
		}
	}

	//draw the legs, each leg take turn up and down when dx is even or odd
	if (j % 2) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (i = 8; i <= 10; i++) {
			glVertex3f(bx[0][i], by[0][i] + 0.15, bz[0][i]);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 11; i <= 13; i++) {
			glVertex3f(bx[0][i], by[0][i], bz[0][i]);
		}
		glEnd();
	}
	else {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (i = 11; i <= 13; i++) {
			glVertex3f(bx[0][i], by[0][i] + 0.15, bz[0][i]);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 8; i <= 10; i++) {
			glVertex3f(bx[0][i], by[0][i], bz[0][i]);
		}
		glEnd();
	}

	//draw the mouth
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(bx[0][6], by[0][6], bz[0][6] + 0.01);
	glVertex3f(bx[0][7] - 0.01, by[0][7] - 0.01, bz[0][7] + 0.01);
	glVertex3f(bx[2][7] - 0.01, by[2][7] - 0.01, bz[2][7] - 0.01);
	glVertex3f(bx[2][6], by[2][6], bz[2][6] - 0.01);
	glEnd();

	//draw the eyes
	glColor3f(1.0, 1.0, 1.0);
	//front eye
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(bx[0][14], by[0][14], bz[0][14] + 0.01);
	glEnd();
	//back eye
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(bx[2][14], by[2][14], bz[2][14] - 0.01);
	glEnd();

	//draw corm rows and bows
	//front
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(bx[0][15], by[0][15], bz[0][15] + 0.01);
	glVertex3f(bx[0][16], by[0][16], bz[0][16] + 0.01);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(bx[0][17], by[0][17], bz[0][17] + 0.01);
	glVertex3f(bx[0][18], by[0][18], bz[0][18] + 0.01);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(bx[0][19], by[0][19], bz[0][19] + 0.01);
	glVertex3f(bx[0][20], by[0][20], bz[0][20] + 0.01);
	glEnd();
	//bows front
	glColor3f(1.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 21; i <= 24; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] + 0.01);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 25; i <= 28; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] + 0.01);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 29; i <= 32; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] + 0.01);
	glEnd();
	//bow back
	glColor3f(1.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 21; i <= 24; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] - 0.11);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 25; i <= 28; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] - 0.11);
	glEnd();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	for (i = 29; i <= 32; i++) glVertex3f(bx[0][i], by[0][i], bz[0][i] - 0.11);
	glEnd();
	//back
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(bx[2][15], by[2][15], bz[2][15] - 0.01);
	glVertex3f(bx[2][16], by[2][16], bz[2][16] - 0.01);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(bx[2][17], by[2][17], bz[2][17] - 0.01);
	glVertex3f(bx[2][18], by[2][18], bz[2][18] - 0.01);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(bx[2][19], by[2][19], bz[2][19] - 0.01);
	glVertex3f(bx[2][20], by[2][20], bz[2][20] - 0.01);
	glEnd();

	return;
}

//settrans for present
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxp, dyp, dzp);
	glRotatef(thetap, 0.0, 1.0, 0.0);
	return;
}

//settrans for present lid
void settrans2(void) {
	int i = frame;
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxl, dyl, dzl);
	if(i == 3)glRotatef(thetal, 1.0, 0.0, 0.0);
	else glRotatef(thetal, 0.0, 1.0, 0.0);
	return;
}

//settrans for polyman
void settrans3(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 0.0, 1.0, 0.0);
	glScalef(1.5, 1.5, 1.5);
	return;
}

//method to calculate bezier
float calculateBezier(float u, int n, float cp[]) {
	float val = 0;
	int i;
	for (i = 0; i <= n; i++) {
		val += cp[i] * float(fact(n)) / float((fact(i)*fact(n - i)))*pow(u, float(i))*pow(float(1.0 - u), float(n - i));
	}
	return val;
}

//method to calucalate factorial
int fact(int n) {
	int counter, factorial = 1;
	if (n == 0)return 1;
	for (int counter = 1; counter <= n; counter++) {
		factorial = factorial * counter;
	}
	return factorial;
}

//settrans for polywoman
void settrans4(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//calculate bezer for x and y
	dxw = calculateBezier(Uval, 3, xcontrol);
	dyw = calculateBezier(Uval, 3, ycontrol);
	glTranslatef(dxw, dyw, dzw);
	glRotatef(thetaw, 0.0, 1.0, 0.0);
	glScalef(scalew, scalew, scalew);
	return;
}

//settrans for star
void settrans5(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxs, dys, dzs);
	glRotatef(thetas, 0.0, 1.0, 0.0);
	glScalef(scales, scales, scales);
	return;
}

//method to draw present
void drawPresent(float x[][4], float y[][4], float z[][4], float nVector[][3]) {
	int face;
	int i;
	float s[4] = { 0.0, 0.0, 1.0, 1.0 }, t[4] = { 0.0, 1.0, 1.0, 0.0 };
	//enable normalize
	glEnable(GL_NORMALIZE);

	//draw present
	for (face = 0; face <= 5; face++) {
		glColor3f(1.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (i = 0; i <= 3; i++) {
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glTexCoord2f(s[i], t[i]);
			glVertex3f(x[face][i], y[face][i], z[face][i]);
		}
		glEnd();
	}

	return;
}

//method to draw star
void drawStar(float x[][4], float y[][4], float z[][4], float nVector[][3]) {
	int face;
	int i;
	float s[4] = { 0.0, 0.0, 1.0, 1.0 }, t[4] = { 0.0, 1.0, 1.0, 0.0 };
	//enable normalize
	glEnable(GL_NORMALIZE);

	//draw present
	for (face = 0; face <= 5; face++) {
		glColor3f(1.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (i = 0; i <= 3; i++) {
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glTexCoord2f(s[i], t[i]);
			glVertex3f(x[face][i], y[face][i], z[face][i]);
		}
		glEnd();
	}

	return;
}

//method to draw present lid
void drawPresentLid(float x[][4], float y[][4], float z[][4], float nVector[][3]) {
	int face;
	int i;
	float s[4] = { 0.0, 0.0, 1.0, 1.0 }, t[4] = { 0.0, 1.0, 1.0, 0.0 };
	//enable normalize
	glEnable(GL_NORMALIZE);

	//draw present lid
	for (face = 6; face <= 11; face++) {
		if(face == 10) glBindTexture(GL_TEXTURE_2D, textures[3]);
		glColor3f(1.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (i = 0; i <= 3; i++) {
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glTexCoord2f(s[i], t[i]);
			glVertex3f(x[face][i], y[face][i], z[face][i]);
		}
		glEnd();
	}

	return;
}

//timerfunction to switch frames
void TimerFunction(int value) {
	switch (frame) {
	case 1: //polyman walk to the present
		thetap += 5;
		thetal += 5;
		dx -= 0.15;
		if (dx <= 1) {
			dx = 1;
			frame = 2;
		}
		break;
	case 2: //present stop spinning
		thetap = 0.0;
		thetal = 0.0;
		frame = 3;
		break;
	case 3: //star jump out of the present and goes to tree
		dys += 0.15;
		scales += 0.01;
		thetas += 5;
		if (dys >= 7 && scales >= 1.0) {
			dys = 7;
			scales = 1.0;
			dxs -= 0.15;
			if (dxs <= -6.7) {
				dxs = -6.7;
				frame = 4;
			}
		}
		break;
	case 4: //polywoman appear using bezier
		Uval += 0.01;
		if (Uval >= 1.0)Uval = 1.0;
		thetaw += 5;
		scalew += 0.01;
		if (thetaw >= 540 && scalew >= 1.5) {
			thetaw = 540;
			scalew = 1.5;
			frame = 5;
		}
		break;
	case 5: //polyman turn around
		theta += 5;
		if (theta >= 360) {
			theta = 360;
		}
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}