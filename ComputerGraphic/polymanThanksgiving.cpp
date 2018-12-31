//Nhung Luu
//assignment 10
//Thanksgiving texture image on table

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
float theta = 180, scale = 3, dx = 10, dy = 0, dz = 1.0;
float thetaw = 0, scalew = 3, dxw = -10, dyw = 0, dzw = 1.0;
//transformations for the table
float thetap = 45, scalep = 1.0, dxp = 0, dyp = 0, dzp = 1.0;
//transformations for present lid
//arrays containing points for polyman
float bx[6][33], by[6][33], bz[6][33];
//array for polywoman
float wbx[6][33], wby[6][33], wz[6][33];
//array for normal vectors
float nVector[12][3];
float light;
void setStage(void);
void settrans1(void);
void settrans3(void);
void settrans4(void);
void drawIcon(float[][33], float[][33], float[][33]);
void drawIcon2(float[][33], float[][33], float[][33]);
void loadIcon(float[][33], float[][33], float[][33], float[][33], float[][33], float[][33]);
void calNormal(float[], float[], float[], float[]);
void SetupRC(void);
void RenderScene(void);
void TimerFunction(int);
//array to hold texture pictures
GLuint textures[6];

//main
int main(int argc, char** argv) {
	//name header of the window
	char header[] = "Polyman Thanksgiving";
	//begin setting the window size and position
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(140, 20);
	//calling the methods for setup, renderscene, and timerfunction
	glutCreateWindow(header);
	SetupRC();
	//include all the picture texture
	textures[0] = SOIL_load_OGL_texture("thanksgiving.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);

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
	glClearColor(0.0, 1.0, 1.0, 1.0);
	return;
}

//setup rendersene
void RenderScene(void) {
	//name the xdel and float arrays
	float xdel = 0.25;
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
	float lightPos[] = { 10,10,1,1 };
	float lightPos2[] = { 7,-6.7,0.5,1 };
	//set reflectant
	float specref[] = { 1,1,1,1 };
	//set spot the light will shine on
	float spotdir[] = { -10, -10, -1 };
	float spotdir2[] = { -7, 6.7, -0.5 };
	cout << "in renderscene" << endl;
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 800, 800);
	glOrtho(-15, 15, -15, 15, -11.0, 11.0);
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
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
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
	glFlush();
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//settans and draw icons
	//call loadicon
	loadIcon(wbx, wby, wz, bx, by, bz);
	settrans1();
	setStage();
	settrans3();
	drawIcon(wbx, wby, wz);
	settrans4();
	drawIcon2(wbx, wby, wz);
	glFlush();
	glEnd();
	glutSwapBuffers();
	return;
}

//settrans for table
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxp, dyp, dzp);
	glRotatef(thetap, 1.0, 0.0, 0.0);
	return;
}

//settrans for polyman
void settrans3(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);
	return;
}

//settrans for polywoman
void settrans4(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxw, dyw, dzw);
	glRotatef(thetaw, 0.0, 1.0, 0.0);
	glScalef(scalew, scalew, scalew);
	return;
}

//method to set the stage including the table
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

	x[2][0] = -5; y[2][0] = 1; z[2][0] = 1;
	x[2][1] = 5; y[2][1] = 1; z[2][1] = 1;
	x[2][2] = 5; y[2][2] = 0; z[2][2] = 1;
	x[2][3] = -5; y[2][3] = 0; z[2][3] = 1;
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
	//left
	x[3][0] = -5; y[3][0] = 1; z[3][0] = 1;
	x[3][1] = -5; y[3][1] = 0; z[3][1] = 1;
	x[3][2] = -5; y[3][2] = 0; z[3][2] = -6;
	x[3][3] = -5; y[3][3] = 1; z[3][3] = -6;
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
	//behind
	x[4][0] = -5; y[4][0] = 1; z[4][0] = -6;
	x[4][1] = -5; y[4][1] = 0; z[4][1] = -6;
	x[4][2] = 5; y[4][2] = 0; z[4][2] = -6;
	x[4][3] = 5; y[4][3] = 1; z[4][3] = -6;
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
	//right
	x[5][0] = 5; y[5][0] = 1; z[5][0] = 1;
	x[5][1] = 5; y[5][1] = 1; z[5][1] = -6;
	x[5][2] = 5; y[5][2] = 0; z[5][2] = -6;
	x[5][3] = 5; y[5][3] = 0; z[5][3] = 1;
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
	//top
	x[6][0] = -5; y[6][0] = 1; z[6][0] = 1;
	x[6][1] = -5; y[6][1] = 1; z[6][1] = -6;
	x[6][2] = 5; y[6][2] = 1; z[6][2] = -6;
	x[6][3] = 5; y[6][3] = 1; z[6][3] = 1;
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
	//bottom
	x[7][0] = -5; y[7][0] = 0; z[7][0] = 1;
	x[7][1] = 5; y[7][1] = 0; z[7][1] = 1;
	x[7][2] = 5; y[7][2] = 0; z[7][2] = -6;
	x[7][3] = -5; y[7][3] = 0; z[7][3] = -6;
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

	float s[4] = { 1.0, 1.0, 0.0, 0.0 }, t[4] = { 0.0, 1.0, 1.0, 0.0 };

	//enable normalize
	glEnable(GL_NORMALIZE);

	int face;

	for (face = 2; face <= 7; face++) {
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i <= 3; i++) {
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			if (face == 6) {
				glBindTexture(GL_TEXTURE_2D, textures[0]);
				glTexCoord2f(s[i], t[i]);
			}
			glVertex3f(x[face][i], y[face][i], z[face][i]);
		}
		glEnd();
	}

	//draw the table legs
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(-4, 0, 1);
	glVertex3f(-4, -3, 1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-4, 0, -6);
	glVertex3f(-4, -3, -6);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(4, 0, 1);
	glVertex3f(4, -3, 1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(4, 0, -6);
	glVertex3f(4, -3, -6);
	glEnd();

	return;
}

//method to calculate the normal vector
void calNormal(float x[], float y[], float z[], float norm[]) {
	norm[0] = y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]);
	norm[1] = z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]);
	norm[2] = x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]);
	return;
}

//method to load polyman, polywoman
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
		if (face == 2) {
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			glColor3f(0.0, 0.0, 0.0);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glVertex3f(bx[face][1], by[face][1], bz[face][1] - 0.01);
			glVertex3f(bx[face][5] , by[face][5], bz[face][5] - 0.01);
			glVertex3f(bx[face][4] - 0.5, by[face][4], bz[face][4] - 0.01);
			glVertex3f(bx[face][2]- 0.5, by[face][2], bz[face][2] - 0.01);
			glEnd();
		}
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
			else glColor3f(1.0, 1.0, 1.0);
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
		glColor3f(0.0, 0.0, 0.0);
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
		glColor3f(0.0, 0.0, 0.0);
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
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(bx[0][6], by[0][6], bz[0][6] + 0.01);
	glVertex3f(bx[0][7] - 0.01, by[0][7] - 0.01, bz[0][7] + 0.01);
	glVertex3f(bx[2][7] - 0.01, by[2][7] - 0.01, bz[2][7] - 0.01);
	glVertex3f(bx[2][6], by[2][6], bz[2][6] - 0.01);
	glEnd();

	//draw the eyes
	glColor3f(0.0, 0.0, 0.0);
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
		if (face == 0) {
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			glColor3f(0.0, 0.0, 0.0);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glVertex3f(bx[face][1] , by[face][1], bz[face][1] + 0.01);
			glVertex3f(bx[face][2]- 0.5, by[face][2], bz[face][2] + 0.01);
			glVertex3f(bx[face][4]- 0.5, by[face][4], bz[face][4] + 0.01);
			glVertex3f(bx[face][5] , by[face][5], bz[face][5] + 0.01);
			glEnd();
		}
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
			else glColor3f(1.0, 1.0, 1.0);
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
		glColor3f(0.0, 0.0, 0.0);
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
		glColor3f(0.0, 0.0, 0.0);
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
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(bx[0][6], by[0][6], bz[0][6] + 0.01);
	glVertex3f(bx[0][7] - 0.01, by[0][7] - 0.01, bz[0][7] + 0.01);
	glVertex3f(bx[2][7] - 0.01, by[2][7] - 0.01, bz[2][7] - 0.01);
	glVertex3f(bx[2][6], by[2][6], bz[2][6] - 0.01);
	glEnd();

	//draw the eyes
	glColor3f(0.0, 0.0, 0.0);
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

//timerfunction to switch frames
void TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}