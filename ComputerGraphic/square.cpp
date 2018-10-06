#include<windows.h>
#include<GL\glut.h>
#include <GL\freeglut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>

//name the prototypes and variables in namespace
using namespace std;
//thetam, scale, change in x and y
float theta = 50.0;
float scale1 = 1.0;
float dx = 7.0, dy = -3.0;
int frame = 1;
//prototypes
void SetupRC(void);
void RenderScene(void);
void loadIcon(float[], float[], float[], float[]);
void drawIcon(float[], float[], float[], float[]);
float xPrime(float, float, float[][3]);
float yPrime(float, float, float[][3]);
void transform(float[], float[], float[], float[], float[], float[], float[], float[], float[][3]);
void TimerFunction(int);
void settrans(float[][3], float, float, float);

//main
int main(int argc, char** argv) {
    //name header of the window
    char header[] = "square by Nhung Luu";
    //begin setting the window size and position
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(560, 440);
    glutInitWindowPosition(140, 20);
    //calling the methods for setup, renderscene, and timerfunction
    SetupRC();
    glutCreateWindow(header);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(30, TimerFunction, 1);
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
    //name the xdel and the float arrays for the points
    float xdel = 0.25;
    float bx[5], by[5], blx[2], bly[2];
    float bxp[5], byp[5], blxp[2], blyp[2], t[3][3];
    cout << "in renderscene" << endl;
    //color for the line draws: black
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set viewport and glortho
    glViewport(0, 0, 540, 440);
    glOrtho(-7.0, 7.0, -7.0, 7.0, 1.0, -1.0);
    //call loadicon, and transform
    loadIcon(bx, by, blx, bly);
    settrans(t, scale1, dx, dy);
    transform(bxp, byp, blxp, blyp, bx, by, blx, bly, t);
    //clear color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    //draw icon
    drawIcon(bxp, byp, blxp, blyp);
    glEnd();
    glutSwapBuffers();
    return;
}

//mothod to load icon with the coordinates
void loadIcon(float bx[], float by[], float blx[], float bly[]) {
    bx[0] = 0.0;	by[0] = 1.0;
    bx[4] = 0.0;	by[4] = 1.0;
    bx[1] = 1.0;		by[1] = 0.0;
    bx[2] = 0.0;		by[2] = -1.0;
    bx[3] = -1.0;   by[3] = 0.0;

    blx[0] = -1.0;	bly[0] = -1.0;
    blx[1] = 1.0;	bly[1] = 1.0;

    return;
}

//method to draw the icon
void drawIcon(float bxp[], float byp[], float blxp[], float blyp[]) {
    int i;
    cout << "in drawicon" << endl;
    //draw the shape
    glBegin(GL_LINE_STRIP);
    glVertex2f(bxp[0], byp[0]);
    for (i = 1; i <= 4; i++) glVertex2f(bxp[i], byp[i]);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(blxp[0], blyp[0]);
    glVertex2f(blxp[1], blyp[1]);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f((bxp[0] + bxp[1]) / 2.0, (byp[0] + byp[1] / 2.0));
    glVertex2f(bxp[1], byp[1]);
    glVertex2f(bxp[2], byp[2]);
    glVertex2f((bxp[2] + bxp[3]) / 2.0, (byp[2] + byp[3] / 2.0));

    return;
}

void settrans(float t[][3], float scale1, float dx, float dy) {
    cout << "in settrans" << endl;
    float ts, ct, st;
    double theta1;
    for (int i = 0; i <= 2; i++) {
	   for (int j = 0; j <= 2; j++) {
		  t[i][j] = 0.0;
		  if (i == j)t[i][j] = 1.0;
	   }   
    }
    if (scale1 != -9.0) {
	   t[0][0] = scale1;
	   t[1][1] = scale1;
    }
    if (theta != -9.0) {
	   theta1 = (3.1416 / 180.0)*theta;
	   ct = cos(theta1);
	   st = sin(theta1);
	   ts = t[0][0];
	   t[0][0] = ts * ct;
	   t[0][1] = ts * st;
	   ts = t[1][1];
	   t[1][0] = -ts * st;
	   t[1][1] = ts * ct;
    }   
    if ((dx + dy) != -18.0) {
	   t[2][0] = dx;
	   t[2][1] = dy;
    }
}

//calculating the prime x and y
float xPrime(float x1, float y1, float t[][3]){
    float xp1 = x1 * t[0][0] + y1 * t[1][0] + t[2][0];
    return xp1;
}

float yPrime(float x1, float y1, float t[][3]) {
    float yp1 = x1 * t[0][1] + y1 * t[1][1] + t[2][1];
    return yp1;
}

//transform method
void transform(float bxp[], float byp[], float blxp[], float blyp[], float bx[], float by[], float blx[], float bly[], float t[][3]) { 
    int i;
    cout << "intransform" << endl;
    //transform for the body
    for (i = 0; i <= 4; i++) {
	   bxp[i] = xPrime(bx[i], by[i], t);
	   byp[i] = yPrime(bx[i], by[i], t);
    }

    //transform the lines
    for (i = 0; i <= 1; i++) {
	   blxp[i] = xPrime(blx[i], bly[i], t);
	   blyp[i] = yPrime(blx[i], bly[i], t);
    }

    return;
}

//timerfunction
void TimerFunction(int value) {
    //ise the switch to have multiple frames
    switch (frame) {
    case 1:
	   //move in from right to middle
	   dx -= 0.15;
	   if (dx <= 0.0) {
		  dx = 0.0;
		  frame = 2;
	   }
	   break;

    case 2:
	   //flip and add mouth
	   dy += 0.5;
	   if (dy <= 1) {
		  theta -= 5.0;
		  if (theta <= 0.0) {
			 theta = 50.0;
			 dy -= 0.5;
			 if (dy <= 0.0) {
				glColor3f(0.0, 0.0, 0.0);
				frame = 3;
			 } 
		  }
	   }
	   break;

    case 3:
	   //move on to the left side
	   dx -= 0.15;
	   if (dx <= -6.5) dx = -6.5;
	   break;
    }

    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}