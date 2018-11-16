//Nhung Luu
//assignment 7

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
//rotation, scale, and tranlation for polyman
float theta = -45, scale = 0.5, dx = -7, dy = 7, dz = 0.5;
//bezier control points
float xcontrol[10], ycontrol[10], Uval = 0.0;
void SetupRC(void);
void RenderScene(void);
void loadIcon(float[][33], float[][33], float[][33]);
void settrans1(void);
void drawIcon2(float[][33], float[][33], float[][33]);
float calculateBezier(float, int, float[]);
int fact(int);
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
	//u value for x(u) and y(u)
	float uval;
	//arrays containing points for polyman
	float wbx[6][33], wby[6][33], wz[6][33];
	//set the control points
	xcontrol[0] = -7; ycontrol[0] = 7;
	xcontrol[1] = 4; ycontrol[1] = -3.5;
	xcontrol[2] = 3; ycontrol[2] = 6;
	xcontrol[3] = -3; ycontrol[3] = 7.0;
	xcontrol[4] = -3.5; ycontrol[4] = 4.0;
	xcontrol[5] = 8; ycontrol[5] = -8;
	int nControlPts = 6, i;
	cout << "in renderscene" << endl;
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	//clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewport and glortho
	glViewport(0, 0, 540, 440);
	glOrtho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);
	//draw the snowy mountain
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
	glVertex3f(-7.0, 6.5, 0.5);
	glVertex3f(6.5, -7.5, 0.5);
	glVertex3f(-7.0, -7.0, 0.5);
	glEnd();
	//draw the control points
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (i = 0; i < nControlPts; i++) glVertex2f(xcontrol[i], ycontrol[i]);
	glEnd();
	//draw the bezier curve
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	uval = 0.0;
	for (i = 0; i <= 20; i++) {
		glVertex2f(calculateBezier(uval, 5, xcontrol), calculateBezier(uval, 5, ycontrol));
		uval += 0.05;
	}
	glEnd();
	//settans and draw icons
	//call loadicon
	loadIcon(wbx, wby, wz);
	settrans1();
	drawIcon2(wbx, wby, wz);
	glFlush();
	glEnd();
	glutSwapBuffers();
	return;
}

//method to load icon with the coordinates
void loadIcon(float wbx[][33], float wby[][33], float wz[][33]) {
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

	//polyman top
	wbx[4][0] = -0.625; wby[4][0] = 0.75; wz[4][0] = 1;
	wbx[4][1] = -0.625; wby[4][1] = 0.75; wz[4][1] = 0.5;
	wbx[4][2] = 0.625; wby[4][2] = 0.75; wz[4][2] = 0.5;
	wbx[4][3] = 0.625; wby[4][3] = 0.75; wz[4][3] = 1;

	//polyman bottom
	wbx[5][0] = -0.625; wby[5][0] = -0.75; wz[5][0] = 1;
	wbx[5][1] = 0.625; wby[5][1] = -0.75; wz[5][1] = 1;
	wbx[5][2] = 0.625; wby[5][2] = -0.75; wz[5][2] = 0.5;
	wbx[5][3] = -0.625; wby[5][3] = -0.75; wz[5][3] = 0.5;

	return;
}

//settrans method for polyman with matrix
void settrans1(void) {
	cout << "in settrans1" << endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//calculate bezer for x and y
	dx = calculateBezier(Uval, 5, xcontrol);
	dy = calculateBezier(Uval, 5, ycontrol);
	glTranslatef(dx, dy, dz);
	glRotatef(theta, 0.0, 0.0, 1.0);
	return;
}

//draw polywoman
void drawIcon2(float bx[][33], float by[][33], float bz[][33]) {
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
	//draw the ski equipment
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
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-1, -0.85, 0.5);
		glVertex3f(1, -0.85, 0.5);
		glVertex3f(1.15, -0.45, 0.5);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(-1, -1, 1);
		glVertex3f(1, -1, 1);
		glVertex3f(1.15, -0.60, 1);
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
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-1, -0.85, 1);
		glVertex3f(1, -0.85, 1);
		glVertex3f(1.15, -0.45, 1);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(-1, -1, 0.5);
		glVertex3f(1, -1, 0.5);
		glVertex3f(1.15, -0.60, 0.5);
		glEnd();
	}
	
	//front smile
	glColor3f(0.0, 1.0, 1.0);
	//draw the face clockwise
	glFrontFace(GL_CW);
	//set back face as cull face
	glCullFace(GL_BACK);
	//enable the back face
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glVertex3f(1.125, 0.0, 1.01);
	glVertex3f(0.875, -0.5, 1.01);
	glVertex3f(0.375, 0.0, 1.01);
	glEnd();
	//left side smile
	//draw the face clockwise
	glFrontFace(GL_CW);
	//set back face as cull face
	glCullFace(GL_BACK);
	//enable the back face
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glVertex3f(1.125, 0.0, 1.01);
	glVertex3f(1.125, 0.0, 0.49);
	glVertex3f(0.875, -0.5, 0.49);
	glVertex3f(0.875, -0.5, 1.01);
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
	glVertex3f(1.125, 0.0, 0.49);
	glVertex3f(0.375, 0.0, 0.49);
	glVertex3f(0.875, -0.5, 0.49);
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

//timerfunction to switch frames
void TimerFunction(int value) {
	//polyman turn when flipping
	if (dx >= -1.0) {
		theta += 5;
		if (theta >= 315)theta = 315;
	}
	Uval += 0.01;
	if (Uval >= 1.0)Uval = 1.0;

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}