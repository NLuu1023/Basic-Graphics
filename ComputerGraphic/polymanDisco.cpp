//Nhung Luu
//assignment 8

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
//rotation, scale, and tranlation for polymam
float theta = 0.0, scale = 1, dx = 7, dy = -3, dz = 0.5;
//rotation, scale , and translation for polwoman
float thetaw = 0.0, scalew = 1, dxw = -7, dyw = -3, wdz = 0.0;
//arrays containing points for polyman
float bx[6][33], by[6][33], z[6][33];
//array for polywoman
float wbx[6][33], wby[6][33], wz[6][33];
//array for stage
float stagex[6][4], stagey[6][4], stagez[6][4];
//array for normal vectors for polyman
float nVector[6][3];
float nVector2[6][3];
float light = 1;
void SetupRC(void);
void RenderScene(void);
void calNormal(float[], float[], float[], float[]);
void loadIcon(float[][33], float[][33], float[][33], float[][33], float[][33], float[][33], float[][4], float[][4], float[][4], float[][3]);
void drawStage(float[][4], float[][4], float[][4], float[][3], float[]);
void settrans1(void);
void settrans2(void);
void drawIcon(float[][33], float[][33], float[][33], float[][3], float[]);
void drawIcon2(float[][33], float[][33], float[][33]);
void TimerFunction(int);
void drawlightsource(float[]);

//main
int main(int argc, char** argv) {
	//name header of the window
	char header[] = "Polyman by Nhung Luu";
	//begin setting the window size and position
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(560, 440);
	glutInitWindowPosition(140, 20);
	//calling the methods for setup, renderscene, and timerfunction
	glutCreateWindow(header);
	SetupRC();
	//call loadicon
	loadIcon(bx, by, z, wbx, wby, wz, stagex, stagey, stagez, nVector);
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
	//array for light parameters
	float ambientLight[] = { 1.0, 0.0, 0.0, 1.0 };
	float difuseLight[] = { 1.0, 0.0, 0.0, 1.0 };
	float specularLight[] = { 1.0, 0.0, 0.0, 1.0 };
	//set light position
	float lightPos[] = { 0.0, 6.0, 0.5, 0.0 };
	//set reflectant
	float specref[] = { 1.0,1.0,1.0,1.0 };
	//set spot the light will shine on
	float spotdir[] = { 0.0, -3.0, 0.5 };
	cout << "in renderscene" << endl;
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 540, 440);
	glOrtho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0);
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
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotdir);
	glEnable(GL_LIGHT0);
	//define the color material of the light
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	//make the spot light turn on and off
	int i = dx;
	int j = dy;
	int n = frame;
	if ((i % 2 != 0) || (j % 2 == 0)) {
		glDisable(GL_LIGHT0);
		light = 0;
		glFlush();
	}
	else light = 1;
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//settans and draw icons
	drawStage(stagex, stagey, stagez, nVector2, lightPos);
	settrans1();
	drawIcon(bx, by, z, nVector, lightPos);
	settrans2();
	drawIcon2(wbx, wby, wz);
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
void loadIcon(float bx[][33], float by[][33], float z[][33], float wbx[][33], float wby[][33], float wz[][33], float stagex[][4], float stagey[][4], float stagez[][4], float nVector[][3]) {
	float normVec[3], xn[3], yn[3], zn[3];
	float normVec2[3];

	//coordinates for polyman front
	bx[0][0] = -1.125; by[0][0] = 0.0; z[0][0] = 1;
	bx[0][1] = -0.625; by[0][1] = 0.75; z[0][1] = 1;
	bx[0][2] = 0.625; by[0][2] = 0.75; z[0][2] = 1;
	bx[0][3] = 1.125; by[0][3] = 0.0; z[0][3] = 1;
	bx[0][4] = 0.625; by[0][4] = -0.75; z[0][4] = 1;
	bx[0][5] = -0.625; by[0][5] = -0.75; z[0][5] = 1;
	//points for mouth
	bx[0][6] = -0.375; by[0][6] = 0.0; z[0][6] = 1;
	bx[0][7] = -0.875; by[0][7] = -0.5; z[0][7] = 1;
	//points for legs
	bx[0][8] = -0.25; by[0][8] = -0.5; z[0][8] = 1;
	bx[0][9] = -0.25; by[0][9] = -1.0; z[0][9] = 1;
	bx[0][10] = -0.5; by[0][10] = -1.0; z[0][10] = 1;
	bx[0][11] = 0.25; by[0][11] = -0.5; z[0][11] = 0.5;
	bx[0][12] = 0.25; by[0][12] = -1.0; z[0][12] = 0.5;
	bx[0][13] = 0; by[0][13] = -1.0; z[0][13] = 0.5;
	//points for eyes
	bx[0][14] = -0.5; by[0][14] = 0.5; z[0][14] = 1;
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
	

	//polyman left
	bx[1][0] = -0.625; by[1][0] = 0.75; z[1][0] = 0.5;
	bx[1][1] = -0.625; by[1][1] = 0.75; z[1][1] = 1;
	bx[1][2] = -1.125; by[1][2] = 0; z[1][2] = 1;
	bx[1][3] = -0.625; by[1][3] = -0.75; z[1][3] = 1;
	bx[1][4] = -0.625; by[1][4] = -0.75; z[1][4] = 0.5;
	bx[1][5] = -1.125; by[1][5] = 0; z[1][5] = 0.5;
	//points for mouth
	bx[1][6] = -0.875; by[1][6] = -0.5; z[1][6] = 1;
	bx[1][7] = -0.875; by[1][7] = -0.5; z[1][7] = 0.5;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[1][i];
		yn[i] = by[1][i];
		zn[i] = z[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[1][0] = normVec[0];
	nVector[1][1] = normVec[1];
	nVector[1][2] = normVec[2];

	//polyman back
	bx[2][0] = -1.125; by[2][0] = 0.0; z[2][0] = 0.5;
	bx[2][1] = -0.625; by[2][1] = -0.75; z[2][1] = 0.5;
	bx[2][2] = 0.625; by[2][2] = -0.75; z[2][2] = 0.5;
	bx[2][3] = 1.125; by[2][3] = 0.0; z[2][3] = 0.5;
	bx[2][4] = 0.625; by[2][4] = 0.75; z[2][4] = 0.5;
	bx[2][5] = -0.625; by[2][5] = 0.75; z[2][5] = 0.5;
	//points for mouth
	bx[2][6] = -0.875; by[2][6] = -0.5; z[2][6] = 0.5;
	bx[2][7] = -0.375; by[2][7] = 0.0; z[2][7] = 0.5;
	//points for eyes
	bx[2][14] = -0.5; by[2][14] = 0.5; z[2][14] = 0.5;
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

	//polyman right
	bx[3][0] = 0.625; by[3][0] = 0.75; z[3][0] = 1;
	bx[3][1] = 0.625; by[3][1] = 0.75; z[3][1] = 0.5;
	bx[3][2] = 1.125; by[3][2] = 0; z[3][2] = 0.5;
	bx[3][3] = 0.625; by[3][3] = -0.75; z[3][3] = 0.5;
	bx[3][4] = 0.625; by[3][4] = -0.75; z[3][4] = 1;
	bx[3][5] = 1.125; by[3][5] = 0; z[3][5] = 1;
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

	//polyman top
	bx[4][0] = -0.625; by[4][0] = 0.75; z[4][0] = 1;
	bx[4][1] = -0.625; by[4][1] = 0.75; z[4][1] = 0.5;
	bx[4][2] = 0.625; by[4][2] = 0.75; z[4][2] = 0.5;
	bx[4][3] = 0.625; by[4][3] = 0.75; z[4][3] = 1;
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

	//polyman bottom
	bx[5][0] = -0.625; by[5][0] = -0.75; z[5][0] = 1;
	bx[5][1] = 0.625; by[5][1] = -0.75; z[5][1] = 1;
	bx[5][2] = 0.625; by[5][2] = -0.75; z[5][2] = 0.5;
	bx[5][3] = -0.625; by[5][3] = -0.75; z[5][3] = 0.5;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = bx[5][i];
		yn[i] = by[5][i];
		zn[i] = z[5][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector[5][0] = normVec[0];
	nVector[5][1] = normVec[1];
	nVector[5][2] = normVec[2];

	//polywoman points-------------------------------------------------------------------------

	//coordinates for polywoman front
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

	//polywoman left
	wbx[1][0] = -1.125; wby[1][0] = 0.0; wz[1][0] = 1;
	wbx[1][1] = -0.625; wby[1][1] = -0.75; wz[1][1] = 1;
	wbx[1][2] = -0.625; wby[1][2] = -0.75; wz[1][2] = 0.5;
	wbx[1][3] = -1.125; wby[1][3] = 0.0; wz[1][3] = 0.5;
	wbx[1][4] = -0.625; wby[1][4] = 0.75; wz[1][4] = 0.5;
	wbx[1][5] = -0.625; wby[1][5] = 0.75; wz[1][5] = 1;

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

	//polywoman top
	wbx[4][0] = -0.625; wby[4][0] = 0.75; wz[4][0] = 1;
	wbx[4][1] = -0.625; wby[4][1] = 0.75; wz[4][1] = 0.5;
	wbx[4][2] = 0.625; wby[4][2] = 0.75; wz[4][2] = 0.5;
	wbx[4][3] = 0.625; wby[4][3] = 0.75; wz[4][3] = 1;

	//polywoman bottom
	wbx[5][0] = -0.625; wby[5][0] = -0.75; wz[5][0] = 1;
	wbx[5][1] = 0.625; wby[5][1] = -0.75; wz[5][1] = 1;
	wbx[5][2] = 0.625; wby[5][2] = -0.75; wz[5][2] = 0.5;
	wbx[5][3] = -0.625; wby[5][3] = -0.75; wz[5][3] = 0.5;

	//stage coordinates---------------------------------------------------------------------------------

	//stage front
	stagex[0][0] = -7; stagey[0][0] = 0.0; stagez[0][0] = -4;
	stagex[0][1] = 7; stagey[0][1] = 0.0; stagez[0][1] = -4;
	stagex[0][2] = 7; stagey[0][2] = -7; stagez[0][2] = -4;
	stagex[0][3] = -7; stagey[0][3] = -7; stagez[0][3] = -4;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = stagex[0][i];
		yn[i] = stagey[0][i];
		zn[i] = stagez[0][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector2[0][0] = normVec[0];
	nVector2[0][1] = normVec[1];
	nVector2[0][2] = normVec[2];

	//stage wall
	stagex[1][0] = -7; stagey[1][0] = 7; stagez[1][0] = -4;
	stagex[1][1] = 7; stagey[1][1] = 7; stagez[1][1] = -4;
	stagex[1][2] = 7; stagey[1][2] = 0.0; stagez[1][2] = -4;
	stagex[1][3] = -7; stagey[1][3] = 0.0; stagez[1][3] = -4;
	//calculate and load the normal for this face
	for (int i = 0; i <= 2; i++) {
		xn[i] = stagex[1][i];
		yn[i] = stagey[1][i];
		zn[i] = stagez[1][i];
	}
	calNormal(xn, yn, zn, normVec);
	nVector2[1][0] = normVec[0];
	nVector2[1][1] = normVec[1];
	nVector2[1][2] = normVec[2];

	return;
}

//method to draw stage
void drawStage(float stagex[][4], float stagey[][4], float stagez[][4], float nVector[][3], float lightPos[]) {
	//draw the stage faces with color black
	int face;
	int i;
	//convert all normal vectors to unit vectors
	glEnable(GL_NORMALIZE);


	for (face = 0; face <= 1; face++) {
		//the stage will be red
		if(face == 1) glColor3f(0.5,0,0);
		else glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_POLYGON);
		glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
		for (i = 0; i <= 3; i++) {
			glVertex3f(stagex[face][i], stagey[face][i], stagez[face][i]);
		}
		glEnd();
	}

	int j = dx;
	int n = frame;
	//draw the light position striangle
	if (light == 1) {
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(-2.0, -3.0, -3.9);
		glVertex3f(0.0, 7.0, -3.9);
		glVertex3f(2.0, -3.0, -3.9);
		glEnd();

		//the spotlight beam
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3f(-0.5, 7.0, 0.51);
		glVertex3f(0.5, 7.0, 0.51);
		glVertex3f(0.5, 6.0, 0.51);
		glVertex3f(-0.5, 6.0, 0.51);
		glEnd();

		//create the circle under polyman
		glColor3f(1.0, 0.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, -3.0, 0.5);
		glutSolidSphere(2.0, 20, 20);

	}
	glFlush();

	return;
}

//settrans method for polyman with matrix
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 0.0, 1.0, 0.0);
	return;
}

//settrans for polywoman
void settrans2(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dxw, dyw, wdz);
	glRotatef(thetaw, 0.0, 1.0, 0.0);
	return;
}

//method to draw the icons
void drawIcon(float bx[][33], float by[][33], float bz[][33], float nvector[][3], float lightPos[]) {
	int i;
	int j = dx;
	int face;

	//enable normalize
	glEnable(GL_NORMALIZE);

	glBegin(GL_POLYGON);
	glNormal3f(nVector[0][0], nVector[0][1], nVector[0][2]);

	glVertex3f(bx[0][0], by[0][0], bz[0][0]);
	glVertex3f(bx[0][1], by[0][0], bz[0][0]);
	glVertex3f(bx[0][2], by[0][0], bz[0][0]);
	glVertex3f(bx[0][3], by[0][0], bz[0][0]);

	glEnd();


	//draw the shape for the polygon
	for (face = 0; face <= 5; face++) {
		if (face == 4 || face == 5) {
			glBegin(GL_POLYGON);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			glColor3f(0.0, 1.0, 1.0);
			for (i = 0; i <= 3; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
		else {
			if (face == 1 || face == 3) glColor3f(0.0, 1.0, 1.0);
			else glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
			glNormal3f(nVector[face][0], nVector[face][1], nVector[face][2]);
			for (i = 0; i <= 5; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
	}

	//draw the legs, each leg take turn up and down when dx is even or odd
	if (j % 2) {
		glColor3f(0.0, 0.0, 1.0);
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
		glColor3f(0.0, 0.0, 1.0);
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
	glVertex3f(bx[0][7], by[0][7], bz[0][7] + 0.01);
	glVertex3f(bx[2][7], by[2][7], bz[2][7] - 0.01);
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

	//draw the shape for the polygon
	for (face = 0; face <= 5; face++) {
		if (face == 4 || face == 5) {
			//draw the face clockwise
			glFrontFace(GL_CW);
			//set back face as cull face
			glCullFace(GL_BACK);
			//enable the back face
			glEnable(GL_CULL_FACE);
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			glColor3f(1.0, 0.0, 1.0);
			for (i = 0; i <= 3; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
		else {
			if (face == 1 || face == 3) glColor3f(1.0, 0.0, 1.0);
			else glColor3f(1.0, 0.0, 0.0);
			//draw the face clockwise
			glFrontFace(GL_CW);
			//set back face as cull face
			glCullFace(GL_BACK);
			//enable the back face
			glEnable(GL_CULL_FACE);
			glShadeModel(GL_SMOOTH);
			glBegin(GL_POLYGON);
			for (i = 0; i <= 5; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
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
	glVertex3f(bx[0][7]-0.01, by[0][7]-0.01, bz[0][7] + 0.01);
	glVertex3f(bx[2][7]-0.01, by[2][7]-0.01, bz[2][7] - 0.01);
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
	//draw the face clockwise
	glFrontFace(GL_CW);
	//set back face as cull face
	glCullFace(GL_BACK);
	//enable the back face
	glEnable(GL_CULL_FACE);
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
void TimerFunction(int value){
	switch (frame) {
	case 1: //polyman and polywoman enter
		dx -= 0.15;
		if (dx <= 0.0) {
			dx = 0.0;
			dxw += 0.15;
			if (dxw >= -4) {
				dxw = -4;
				frame = 2;
			}
		}
		
		break;

	case 2: //polyman turn
		theta += 5.0;
		if (theta >= 360) {
			theta = 360;
			frame = 3;
		}
		break;

	case 3: //polyman jump
		dy += 0.15;
		if (dy >= 1) {
			dy = 1;
			frame = 4;
		}
		break;

	case 4: //polyman flip
		theta -= 5.0;
		if (theta <= 0.0) {
			theta = 0.0;
			frame = 5;
		}
		break;

	case 5: //polyman goes down, polywoman turn
		dy -= 0.15;
		if (dy <= -3.0) {
			dy = -3.0;
			thetaw += 5;
			if (thetaw >= 100) {
				thetaw = 100;
				frame = 6;
			}
		}
		break;

	case 6: //polywoman turn
		thetaw -= 5;
		if (thetaw <= -100) {
			thetaw = -100;
			frame = 7;
		}
		break;

	case 7:  //polywoman turn
		thetaw += 5;
		if (thetaw >= 0.0) {
			thetaw = 0.0;
		}
		break;
	}

		glutPostRedisplay();
		glutTimerFunc(30, TimerFunction, 1);
}