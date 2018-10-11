//Nhung Luu
//Exam 1 Take Home

#include<windows.h>
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<iomanip>
#include<iostream>

using namespace std;
//square movements
float sqtheta = 0.0;
float sqtransx = 0.0, sqtransy = 0.0;
float sqscalex = 1, sqscaley = 1;
//trapezoid movements
float trtheta = 0.0, trtransx = 0.0, trtransy = 0.0, trscalex = 1, trscaley = 1;
//movements for square on trapezoid
float theta = 0.0, transx = 0.0, transy = 0.0, scalex = 1, scaley = 1;
int frame = 1;
void SetupRC(void);
void RenderScene(void);
void DrawAllIcons(float[], float[], int, int[], int[], float[], float[], float[], float, float, float, float, float);
void TimerFunction(int);
void loadSquare(float[], float[], int[], int[], float[], float[], float[]);
void loadTrapezoid(float[], float[], int[], int[], float[], float[], float[]);
void loadSquareOnTrapezoid(float[], float[], int[], int[], float[], float[], float[]);

//main
int main(int argc, char** argv) {
    //name header of the window
    char header[] = "Square on Trapezoid by Nhung Luu";
    //begin setting the window size and position
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(540, 440);
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    return;
}

//setup rendersene
void RenderScene(void) {
    //name the xdel and float arrays
    float xdel = 0.25;
    //array of plot points for square, trapezoid, and square on trapezoid
    float sqx[6], sqy[6], trx[6], tray[6], x[10], y[10];
    //arrays containing the square and trapezoid's points per draw, drawtype, and color
    int sqPointsPerDraw[3], sqDrawType[3];
    float sqColorr[1], sqColorg[1], sqColorb[1];
    int trPointsPerDraw[3], trDrawType[3];
    float trColorr[1], trColorg[1], trColorb[1];
    //arrays for square on trapezoid
    int pointsPerDraw[5], drawType[5];
    float colorr[2], colorg[2], colorb[2];
    cout << "in renderscene" << endl;
    //matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set viewport and glortho
    glViewport(0, 0, 540, 440);
    glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, -1.0);
    //clear color
    glClear(GL_COLOR_BUFFER_BIT);
    //call loadicons
    //settans and draw icons
    loadSquare(sqx, sqy, sqPointsPerDraw, sqDrawType, sqColorr, sqColorg, sqColorb);
    DrawAllIcons(sqx, sqy, 3, sqPointsPerDraw, sqDrawType, sqColorr, sqColorg, sqColorb, sqtheta, sqscalex, sqscaley, sqtransx, sqtransy);
    loadTrapezoid(trx, tray, trPointsPerDraw, trDrawType, trColorr, trColorg, trColorb);
    DrawAllIcons(trx, tray, 3, trPointsPerDraw, trDrawType, trColorr, trColorg, trColorb, trtheta, trscalex, trscaley, trtransx, trtransy);
    loadSquareOnTrapezoid(x, y, pointsPerDraw, drawType, colorr, colorg, colorb);
    DrawAllIcons(x, y, 5, pointsPerDraw, drawType, colorr, colorg, colorb, theta, scalex, scaley, transx, transy);
    glFlush();
    glEnd();
    glutSwapBuffers();
    return;
}

//method to load all the points and drawtypes for square
void loadSquare(float x[], float y[], int pointsPerDraw[], int drawType[], float colorr[], float colorg[], float colorb[]) {
    //points for square body
    x[0] = 1.0; y[0] = 1.0;
    x[1] = 1.0; y[1] = -1.0;
    x[2] = -1.0; y[2] = -1.0;
    x[3] = -1.0; y[3] = 1.0;
    x[4] = 0.0; y[4] = 2.0;
    x[5] = 0.0; y[5] = -2.0;

    //takes 5 points to draw the square and 2 points to draw line through
    pointsPerDraw[0] = 5;
    pointsPerDraw[1] = 2;
    pointsPerDraw[2] = 4;

    //set draw type: 1 = GL_LINES, 2 = GL_LINE_STRIP, 3 = GL_POLYGON
    drawType[0] = 2;
    drawType[1] = 1;
    drawType[2] = 3;

    //set color
    colorr[0] = 1.0;
    colorg[0] = 0.0;
    colorb[0] = 0.0;

    return;
}

//method to load all the points and drawtypes for trapezoid
void loadTrapezoid(float x[], float y[], int pointsPerDraw[], int drawType[], float colorr[], float colorg[], float colorb[]) {
    x[0] = 1.0; y[0] = 1.0;
    x[1] = 1.5; y[1] = -1.0;
    x[2] = -1.5; y[2] = -1.0;
    x[3] = -1.0; y[3] = 1.0;
    x[4] = 0.0; y[4] = 2.0;
    x[5] = 0.0; y[5] = -2.0;

    //takes 5 points to draw the trapezoid and 2 points to draw line through
    pointsPerDraw[0] = 5;
    pointsPerDraw[1] = 2;
    pointsPerDraw[2] = 4;

    //set draw type: 1 = GL_LINES, 2 = GL_LINE_STRIP, 3 = GL_POLYGON
    drawType[0] = 2;
    drawType[1] = 1;
    drawType[2] = 3;

    //set color
    colorr[0] = 0.0;
    colorg[0] = 1.0;
    colorb[0] = 0.0;

    return;
}

//method to load all the points and drawtypes for square
void loadSquareOnTrapezoid(float x[], float y[], int pointsPerDraw[], int drawType[], float colorr[], float colorg[], float colorb[]) {
    //points for square body
    x[0] = 1.0; y[0] = 1.0;
    x[1] = 1.0; y[1] = 0.0;
    x[2] = -1.0; y[2] = 0.0;
    x[3] = -1.0; y[3] = 1.0;
    //points for trapezoid
    x[4] = 1.5; y[4] = 0.0;
    x[5] = 2.0; y[5] = -1.0;
    x[6] = -2.0; y[6] = -1.0;
    x[7] = -1.5; y[7] = 0.0;
    //points for line
    x[8] = 0.0; y[8] = 3.0;
    x[9] = 0.0; y[9] = -3.0;

    //takes 5 points to draw the square and trapezoid and 2 points to draw line through
    pointsPerDraw[0] = 5;
    pointsPerDraw[1] = 5;
    pointsPerDraw[2] = 2;
    pointsPerDraw[3] = 4;
    pointsPerDraw[4] = 4;

    //set draw type: 1 = GL_LINES, 2 = GL_LINE_STRIP, 3 = GL_POLYGON
    drawType[0] = 2;
    drawType[1] = 2;
    drawType[2] = 1;
    drawType[3] = 3;
    drawType[4] = 3;

    //set color
    colorr[0] = 1.0;
    colorg[0] = 0.0;
    colorb[0] = 0.0;

    colorr[1] = 0.0;
    colorg[1] = 1.0;
    colorb[1] = 0.0;

    return;
}

//method use to draw all icons
void DrawAllIcons(float x[], float y[], int ndraws, int pointsperdraw[], int drawtype[], float colorr[], float colorg[], float colorb[], float rotate, float scalex, float scaley, float transx, float transy) {
    int i;
    //set the modelview matrix first inserting the theta, scale, and translation
    cout << "in settrans" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //translate
    glTranslatef(transx, transy, 0.0);
    //rotate
    glRotatef(rotate, 0.0, 0.0, 1.0);
    //scale
    glScalef(scalex, scaley, 1.0);

    //if the number of draws is 2, then its drawing the square or trapezoid
    if (ndraws == 3) {
	   //make sure the points per draw is 5 for both square and trapezoid
	   if (pointsperdraw[0] == 5) {
		  //inser the drawType
		  if (drawtype[0] == 2) {
			 //set color
			 glColor3f(colorr[0], colorg[0], colorb[0]);
			 //draw the shape
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 3; i++) {
				glVertex2f(x[i], y[i]);
			 }
			 glVertex2f(x[0], y[0]);
			 glEnd();
		  }
	   }
	   //the second points per draw is for the line
	   if (pointsperdraw[1] == 2) {
		  if (drawtype[1] == 1) {
			 //set color
			 glColor3f(colorr[0], colorg[0], colorb[0]);
			 //draw line through
			 glBegin(GL_LINES);
			 glVertex2f(x[4], y[4]);
			 glVertex2f(x[5], y[5]);
			 glEnd();
		  }
	   }
	   if (pointsperdraw[2] == 4) {
		  if (drawtype[2] == 3) {
			 glColor3f(colorr[0], colorg[0], colorb[0]);
			 glShadeModel(GL_FLAT);
			 glBegin(GL_POLYGON);
			 glVertex2f((x[0]+x[3])/2, y[0]);
			 glVertex2f(x[0], y[0]);
			 glVertex2f(x[1], y[1]);
			 glVertex2f((x[1]+x[2])/2, y[1]);
			 glEnd();
		  }
	   }
    }
    //else it the num of draws is 3, then it is the square on trapezoid
    else if (ndraws == 5) {
	   //draw the trapezoid first, then square, then the line through
	   if (pointsperdraw[0] == 5) {
		  if (pointsperdraw[1] == 5) {
			 if (drawtype[1] == 2) {
				//set color
				glColor3f(colorr[1], colorg[1], colorb[1]);
				//draw the shape
				glBegin(GL_LINE_STRIP);
				for (i = 4; i <= 7; i++) {
				    glVertex2f(x[i], y[i]);
				}
				glVertex2f(x[4], y[4]);
				glEnd();
			 }
		  }
		  if (drawtype[0] == 2) {
			 //set color
			 glColor3f(colorr[0], colorg[0], colorb[0]);
			 //draw the shape
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 3; i++) {
				glVertex2f(x[i], y[i]);
			 }
			 glVertex2f(x[0], y[0]);
			 glEnd();
		  }
	   }
	   //draw the line though
	   if (pointsperdraw[2] == 2) {
		  if (drawtype[2] == 1) {
			 //set color
			 glColor3f(colorr[1], colorg[1], colorb[1]);
			 //draw line through
			 glBegin(GL_LINES);
			 glVertex2f(x[8], y[8]);
			 glVertex2f(x[9], y[9]);
			 glEnd();
		  }
	   }
	   if (pointsperdraw[3] == 4) {
		  if (drawtype[3] == 3) {
			 glColor3f(colorr[0], colorg[0], colorb[0]);
			 glShadeModel(GL_FLAT);
			 glBegin(GL_POLYGON);
			 glVertex2f((x[0] + x[3]) / 2, y[0]);
			 glVertex2f(x[0], y[0]);
			 glVertex2f(x[1], y[1]);
			 glVertex2f((x[1] + x[2]) / 2, y[1]);
			 glEnd();
		  }
	   }
	   if (pointsperdraw[4] == 4) {
		  if (drawtype[4] == 3) {
			 glColor3f(colorr[1], colorg[1], colorb[1]);
			 glShadeModel(GL_FLAT);
			 glBegin(GL_POLYGON);
			 glVertex2f((x[4] + x[7]) / 2, y[4]);
			 glVertex2f(x[4], y[4]);
			 glVertex2f(x[5], y[5]);
			 glVertex2f((x[5] + x[6]) / 2, y[5]);
			 glEnd();
		  }
	   }
    }
    glFlush();
    return;
}

//timerfunction with the switch to dictate frames of actions
void TimerFunction(int value) {
    switch (frame) {
    case 1: //suare move up and over right by 5
	   sqtransx += 0.15;
	   if (sqtransx >= 5.0) {
		  sqtransx = 5.0;
		  sqtransy += 0.15;
		  if (sqtransy >= 5.0) {
			 sqtransy = 5.0;
			 frame = 2;
		  }
	   }
	   break;

    case 2: //trapezoid move down and over left by 5
	   trtransx -= 0.15;
	   if (trtransx <= -5.0) {
		  trtransx = -5.0;
		  trtransy -= 0.15;
		  if (trtransy <= -5.0) {
			 trtransy = -5.0;
			 frame = 3;
		  }
	   }

    case 3: //scale square and trapezoid
	   if (trtransx == -5 && trtransy == -5) {
		  trscalex = 2;
		  trscaley = 2;
		  sqscalex = 2;
		  sqscaley = 2;
		  frame = 4;
	   }
	   
    case 4: //rotate all icons
	   if (sqscalex == 2 && trscalex == 2) {
		  trtheta += 5;
		  theta += 5;
		  sqtheta += 5;
	   }
    }
    
    glutPostRedisplay();
    glutTimerFunc(30, TimerFunction, 1);
}
