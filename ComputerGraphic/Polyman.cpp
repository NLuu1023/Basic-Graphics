//Nhung Luu
//assignment 2

#include<windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<iostream>

//name the prototypes and variables in namespace
using namespace std;
//theta, scale, change in x and y
//polyman
float theta = 0.0;
float scale1 = 1.0;
float dx = 7.0, dy = -3.0;
int frame = 1;
//prototype
void SetupRC(void);
void RenderScene(void);
void loadIcon(float[], float[], float[], float[]);
float xPrime(float, float);
float yPrime(float, float);
void transform(float[], float[], float[], float[], float, float, float[], float[], float[], float[]);
void drawIcon(float[], float[], float[], float[], float, float);
void TimerFunction(int);

//main
int main(int argc, char** argv) {
    //name header of the window
    char header[] = "Polyman by Nhung Luu";
    //begin setting the window size and position
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(560, 440);
    glutInitWindowPosition(140, 20);
    //calling the methods for setup, renderscene, and timerfunction
    glutCreateWindow(header);
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutTimerFunc(30, TimerFunction, 1);
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
    float bx[6], by[6], blx[8], bly[8], bex = -0.5, bey = 0.5;
    float bxp[6], byp[6], blxp[8], blyp[8], bexp = 0, beyp = 0;
    cout << "in renderscene" << endl;
    //matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set viewport and glortho
    glViewport(0, 0, 540, 440);
    glOrtho(-7.0, 7.0, -7.0, 7.0, 1.0, -1.0);
    //call loadicon
    loadIcon(bx, by, blx, bly);
    //clear color
    glClear(GL_COLOR_BUFFER_BIT);
    //settans and draw icons
    transform(bx, by, blx, bly, bex, bey, bxp, byp, blxp, blyp);
    bexp = xPrime(bex, bey);
    beyp = yPrime(bex, bey);
    drawIcon(bxp, byp, blxp, blyp, bexp, beyp);
    glFlush();
    glEnd();
    glutSwapBuffers();
    return;
}

//mothod to load icon with the coordinates
void loadIcon(float bx[], float by[], float blx[], float bly[]) {
    //coordinates for polyman body
    bx[0] = -1.125;	    by[0] = 0.0;
    bx[1] = -0.625;	    by[1] = 0.75;
    bx[2] = 0.625;	    by[2] = 0.75;
    bx[3] = 1.125;	    by[3] = 0.0;
    bx[4] = 0.625;	    by[4] = -0.75;
    bx[5] = -0.625;	    by[5] = -0.75;
    //polyman lines
    blx[0] = -0.375;	bly[0] = 0.0;
    blx[1] = -0.875;	bly[1] = -0.5;
    blx[2] = -0.25;	     bly[2] = -0.5;
    blx[3] = -0.25;	     bly[3] = -1.0;
    blx[4] = -0.5;		bly[4] = -1.0;
    blx[5] = 0.25;	     bly[5] = -0.5;
    blx[6] = 0.25;	     bly[6] = -1.0;
    blx[7] = 0.0;		bly[7] = -1.0;
    return;
}

//method to rotate, scale, and translate the points of polyman using x prime and y prime
float xPrime(float x, float y) {
    float xPrime = (x*scale1*cos((3.1416 / 180.0)*theta)) - (y*scale1*sin((3.1416 / 180.0)*theta)) + dx;
    return xPrime;
}

float yPrime(float x, float y) {
    float yPrime = (x*scale1*sin((3.1416 / 180.0)*theta)) + (y*scale1*cos((3.1416 / 180.0)*theta)) + dy;
    return yPrime;
}

//tranform the points using the translation equations
void transform(float bx[], float by[], float blx[], float bly[], float bex, float bey, float bxp[], float byp[], float blxp[], float blyp[]) {
    int i;
    for (i = 0; i <= 5; i++) {
	   bxp[i] = xPrime(bx[i], by[i]);
	   byp[i] = yPrime(bx[i], by[i]);
    }
    for (i = 0; i <= 7; i++) {
	   blxp[i] = xPrime(blx[i], bly[i]);
	   blyp[i] = yPrime(blx[i], bly[i]);
    }
}

//method to draw the icons
void drawIcon(float bx[], float by[], float blx[], float bly[], float bex, float bey) {
    int i;
    int j = dx;
    cout << "in drawicon" << endl;
    //draw the shape fo the polygon
    glColor3f(0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
    glBegin(GL_POLYGON);
    for (i = 0; i <= 5; i++) glVertex2f(bx[i], by[i]);
    glEnd();

    //after flip, y=-3, draw smile
    if (dx < 0) {
	   glColor3f(1.0, 1.0, 1.0);
	   glShadeModel(GL_FLAT);
	   glBegin(GL_POLYGON);
	   glShadeModel(GL_FLAT);
	   glBegin(GL_POLYGON);
	   glVertex2f(bx[0], by[0]);
	   glVertex2f(blx[0], bly[0]);
	   glVertex2f(blx[1], bly[1]);
	   glEnd();
    }

    //draw the mouth
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(blx[0], bly[0]);
    glVertex2f(blx[1], bly[1]);
    glEnd();

    //draw the legs, each leg take turn up and down when dx is even or odd
    if (j % 2) {
	   glColor3f(0.0, 0.0, 1.0);
	   glBegin(GL_LINE_STRIP);
	   for (i = 2; i <= 4; i++) {
		  glVertex2f(blx[i], bly[i] + 0.15);
	   }
	   glEnd();
	   glBegin(GL_LINE_STRIP);
	   for (i = 5; i <= 7; i++) {
		  glVertex2f(blx[i], bly[i]);
	   }
	   glEnd();
    }
    else {
	   glColor3f(0.0, 0.0, 1.0);
	   glBegin(GL_LINE_STRIP);
	   for (i = 5; i <= 7; i++) {
		  glVertex2f(blx[i], bly[i] + 0.15);
	   }
	   glEnd();
	   glBegin(GL_LINE_STRIP);
	   for (i = 2; i <= 4; i++) {
		  glVertex2f(blx[i], bly[i]);
	   }
	   glEnd();
    }

    //draw the eyes
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(bex, bey);
    glEnd();

    return;
}

//timerfunction to switch frames
void TimerFunction(int value) {
    switch (frame) {
    case 1: //polyman enter from right
	   dx -= 0.15;
	   if (dx <= 0.0) {
		  dx = 0.0;
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
	   if (theta <= -300) {
		  theta = 0;
		  frame = 4;
	   }
	   break;

    case 4: //polyman goes down
	   dy -= 0.15;
	   if (dy <= -3.0) {
		  dy = -3.0;
		  frame = 5;
	   }
	   break;

    case 5: //polyman leave to the left
	   dx -= 0.15;
    }

    glutPostRedisplay();
    glutTimerFunc(30, TimerFunction, 1);
}