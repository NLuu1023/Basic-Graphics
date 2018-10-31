//Nhung Luu
//assignment 8

#include<windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<iostream>

//name the prototypes and variables in namespace
using namespace std;
int frame = 1;
//rotation, scale, and tranlation for polymam
float theta = 0.0, scale = 1, dx = 7, dy = -3, dz = 0.5;
//rotation, scale , and translation for polwoman
float thetaw = 0.0, scalew = 1, dxw = -7, dyw = -3, wdz = 0.0;
void SetupRC(void);
void RenderScene(void);
void loadIcon(float[][33], float[][33], float[][33], float[][33], float[][33], float[][33], float[][4], float[][4], float[][4]);
void drawStage(float[][4], float[][4], float[][4]);
void settrans1(void);
void settrans2(void);
void drawIcon(float[][33], float[][33], float[][33]);
void drawIcon2(float[][33], float[][33], float[][33]);
void TimerFunction(int);

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
	glutDisplayFunc(RenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
	return 0;
}

//setup method to choose clear color for the window: white
void SetupRC(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	return;
}

//setup rendersene
void RenderScene(void) {
	//name the xdel and float arrays
	float xdel = 0.25;
	//arrays containing points for polyman
	float bx[6][33], by[6][33], z[6][33];
	//array for polywoman
	float wbx[6][33], wby[6][33], wz[6][33];
	//array for stage
	float stagex[5][4], stagey[5][4], stagez[5][4];
	cout << "in renderscene" << endl;
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 540, 440);
	glOrtho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);
	//call loadicon
	loadIcon(bx, by, z, wbx, wby, wz, stagex, stagey, stagez);
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//settans and draw icons
	settrans1();
	drawIcon(bx, by, z);
	settrans2();
	drawIcon2(wbx, wby, wz);
	glFlush();
	glEnd();
	glutSwapBuffers();
	return;
}

//method to load icon with the coordinates
void loadIcon(float bx[][33], float by[][33], float z[][33], float wbx[][33], float wby[][33], float wz[][33], float stagex[][4], float stagey[][4], float stagez[][4]) {
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

	//polyman upper right
	bx[3][0] = 0.625; by[3][0] = 0.75; z[3][0] = 1;
	bx[3][1] = 0.625; by[3][1] = 0.75; z[3][1] = 0.5;
	bx[3][2] = 1.125; by[3][2] = 0; z[3][2] = 0.5;
	bx[3][3] = 0.625; by[3][3] = -0.75; z[3][3] = 0.5;
	bx[3][4] = 0.625; by[3][4] = -0.75; z[3][4] = 1;
	bx[3][5] = 1.125; by[3][5] = 0; z[3][5] = 1;

	//polyman top
	bx[4][0] = -0.625; by[4][0] = 0.75; z[4][0] = 1;
	bx[4][1] = -0.625; by[4][1] = 0.75; z[4][1] = 0.5;
	bx[4][2] = 0.625; by[4][2] = 0.75; z[4][2] = 0.5;
	bx[4][3] = 0.625; by[4][3] = 0.75; z[4][3] = 1;

	//polyman bottom
	bx[5][0] = -0.625; by[5][0] = -0.75; z[5][0] = 1;
	bx[5][1] = 0.625; by[5][1] = -0.75; z[5][1] = 1;
	bx[5][2] = 0.625; by[5][2] = -0.75; z[5][2] = 0.5;
	bx[5][3] = -0.625; by[5][3] = -0.75; z[5][3] = 0.5;

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
	stagex[0][0] = -2; stagey[0][0] = -1; stagez[0][0] = 4;
	stagex[0][1] = 2; stagey[0][1] = -1; stagez[0][1] = 4;
	stagex[0][2] = 2; stagey[0][2] = -3; stagez[0][2] = 4;
	stagex[0][3] = -2; stagey[0][3] = -3; stagez[0][3] = 4;

	//stage left
	stagex[1][0] = -2; stagey[1][0] = -1; stagez[1][0] = -4;
	stagex[1][1] = -2; stagey[1][1] = -1; stagez[1][1] = 4;
	stagex[1][2] = -2; stagey[1][2] = -3; stagez[1][2] = 4;
	stagex[1][3] = -2; stagey[1][3] = -3; stagez[1][3] = -4;

	//stage back
	stagex[2][0] = -2; stagey[2][0] = 3; stagez[2][0] = -4;
	stagex[2][1] = -2; stagey[2][1] = -3; stagez[2][1] = -4;
	stagex[2][2] = 2; stagey[2][2] = -3; stagez[2][2] = -4;
	stagex[2][3] = 2; stagey[2][3] = 3; stagez[2][3] = -4;

	//stage right
	stagex[3][0] = 2; stagey[3][0] = -1; stagez[3][0] = 4;
	stagex[3][1] = 2; stagey[3][1] = -1; stagez[3][1] = -4;
	stagex[3][2] = 2; stagey[3][2] = -3; stagez[3][2] = -4;
	stagex[3][3] = 2; stagey[3][3] = -3; stagez[3][3] = 4;

	//stage top
	stagex[4][0] = -2; stagey[4][0] = -1; stagez[4][0] = -4;
	stagex[4][1] = 2; stagey[4][1] = -1; stagez[4][1] = -4;
	stagex[4][2] = 2; stagey[4][2] = -1; stagez[4][2] = 4;
	stagex[4][3] = -2; stagey[4][3] = -1; stagez[4][3] = 4;

	return;
}

//method to draw stage
void drawStage(float stagex[][4], float stagey[][4], float stagez[][4]) {
	//draw the stage faces with color black
	int face;
	int i;

	for (face = 0; face <= 4; face++) {
		//the back of the stage will be grey
		if(face == 2) glColor3f(0.5, 0.5, 0.5);
		else glColor3f(0.0, 0.0, 0.0);
		//draw the face clockwise
		glFrontFace(GL_CW);
		//set back face as cull face
		glCullFace(GL_BACK);
		//enable the back face
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		for (i = 0; i <= 3; i++) {
			glVertex3f(stagex[face][i], stagey[face][i], stagez[face][i]);
		}
		glEnd();
	}

	return;
}

//settrans method for polyman with matrix
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 1.0, 0.0, 1.0);
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
void drawIcon(float bx[][33], float by[][33], float bz[][33]) {
	int i;
	int j = dx;
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
			glColor3f(0.0, 1.0, 1.0);
			for (i = 0; i <= 3; i++) glVertex3f(bx[face][i], by[face][i], bz[face][i]);
			glEnd();
		}
		else {
			if (face == 1 || face == 3) glColor3f(0.0, 1.0, 1.0);
			else glColor3f(0.0, 0.0, 1.0);
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

	//after flip, frame = 4, draw smile
	if (frame == 4) {
		//front smile
		glColor3f(1.0, 1.0, 1.0);
		//draw the face clockwise
		glFrontFace(GL_CW);
		//set back face as cull face
		glCullFace(GL_BACK);
		//enable the back face
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		glVertex3f(-1.125, 0.0, 1.01);
		glVertex3f(-0.375, 0.0, 1.01);
		glVertex3f(-0.875, -0.5, 1.01);
		glEnd();

		//left smile
		glColor3f(1.0, 1.0, 1.0);
		//draw the face clockwise
		glFrontFace(GL_CW);
		//set back face as cull face
		glCullFace(GL_BACK);
		//enable the back face
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		glVertex3f(-1.125, 0.0, 1.01);
		glVertex3f(-0.875, -0.5, 1.01);
		glVertex3f(-0.875, -0.5, 0.49);
		glVertex3f(-1.125, 0.0, 0.49);
		glEnd();

		//back side
		//draw the face clockwise
		glFrontFace(GL_CW);
		//set back face as cull face
		glCullFace(GL_BACK);
		//enable the back face
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_POLYGON);
		glVertex3f(-1.125, 0.0, 0.49);
		glVertex3f(-0.875, -0.5, 0.49);
		glVertex3f(-0.375, 0.0, 0.49);
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
void TimerFunction(int value) {
	switch (frame) {
	case 1: //polyman and polywoman enter
		dx -= 0.15;
		if (dx <= 0.0) {
			dx = 0.0;
		}
		dxw += 0.15;
		if (dxw >= -1.5) {
			dxw = -1.5;
			frame = 2;
		}
		break;

	case 2: //polyman jump
		dy += 0.15;
		if (dy >= -1.0) {
			frame = 3;
		}
		break;

	case 3: //polyman flip
		theta -= 5.0;
		if (theta <= -360) {
			theta = -360;
			frame = 4;
		}
		break;

	case 4: //polyman goes down, polywoman turn
		dy -= 0.15;
		if (dy <= -3.0) {
			dy = -3.0;
			thetaw += 5;
			if (thetaw >= 100) {
				thetaw = 100;
				frame = 5;
			}
		}
		break;

	case 5: //polywoman turn
		thetaw -= 5;
		if (thetaw <= -100) {
			thetaw = -100;
			frame = 6;
		}
		break;

	case 6:  //polywoman turn
		thetaw += 5;
		if (thetaw >= 0.0) {
			thetaw = 0.0;
			frame = 7;
		}
		break;

	case 7: //polywoman leave left, polyman leave after
		dx -= 0.15;
		if (dx <= -4) {
			thetaw += 5.0;
			if (thetaw >= 180) {
				thetaw = 180;
				dxw -= 0.15;
			}
		}
		break;
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}