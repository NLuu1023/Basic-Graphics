//Nhung Luu
//assignment 3

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
//polywoman
float thetaw = 0.0, scale1w = 1.0, dxw = -7.0, dyw = -3.0;
//square
float thetas = 0.0, scale1s = 1.0, dxs = -7.0, dys = -3.0;
int frame = 1;
//prototype
void SetupRC(void);
void RenderScene(void);
void loadIcon(float[], float[], float[], float[], float[], float[], float[], float[], float[], float[], float[], float[]);
void settrans1(void);
void settrans2(void);
void drawIcon(float[], float[], float[], float[], float, float);
void drawIcon2(float[], float[], float[], float[], float, float);
void settrans3(void);
void drawSquare(float[], float[], float[], float[], float, float);
void TimerFunction(int);

//main
int main(int argc, char** argv) {
    //name header of the window
    char header[] = "Polyman Battle by Nhung Luu";
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
    //array for polywoman
    float wbx[6], wby[6], wblx[16], wbly[16], wbex = 0.5, wbey = 0.5;
    //arrays for square
    float sbx[4], sby[4], sblx[10], sbly[10], sbex = 0.25, sbey = 0.5;
    cout << "in renderscene" << endl;
    //matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set viewport and glortho
    glViewport(0, 0, 540, 440);
    glOrtho(-7.0, 7.0, -7.0, 7.0, 1.0, -1.0);
    //call loadicon
    loadIcon(bx, by, blx, bly, sbx, sby, sblx, sbly, wbx, wby, wblx, wbly);
    //clear color
    glClear(GL_COLOR_BUFFER_BIT);
    //settans and draw icons
    settrans1();
    drawIcon(bx, by, blx, bly, bex, bey);
    settrans2();
    drawIcon2(wbx, wby, wblx, wbly, wbex, wbey);
    settrans3();
    drawSquare(sbx, sby, sblx, sbly, sbex, sbey);
    glFlush();
    glEnd();
    glutSwapBuffers();
    return;
}

//mothod to load icon with the coordinates
void loadIcon(float bx[], float by[], float blx[], float bly[], float sbx[], float sby[], float sblx[], float sbly[], float wbx[], float wby[], float wblx[], float wbly[]) {
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

    //polywoman coordinates
    wbx[0] = -1.125;	    wby[0] = 0.0;
    wbx[1] = -0.625;	    wby[1] = 0.75;
    wbx[2] = 0.625;	    wby[2] = 0.75;
    wbx[3] = 1.125;	    wby[3] = 0.0;
    wbx[4] = 0.625;	    wby[4] = -0.75;
    wbx[5] = -0.625;	    wby[5] = -0.75;
    //polywoman lines
    wblx[0] = 0.375;	wbly[0] = 0.0;
    wblx[1] = 0.875;	wbly[1] = -0.5;
    wblx[2] = -0.25;	     wbly[2] = -0.5;
    wblx[3] = -0.25;	     wbly[3] = -1.0;
    wblx[4] = 0.0;		wbly[4] = -1.0;
    wblx[5] = 0.25;	     wbly[5] = -0.5;
    wblx[6] = 0.25;	     wbly[6] = -1.0;
    wblx[7] = 0.5;		wbly[7] = -1.0;

    //square body
    sbx[0] = 0;	    sby[0] = 1;
    sbx[1] = 1;	    sby[1] = 0;
    sbx[2] = 0;	    sby[2] = -1;
    sbx[3] = -1;	    sby[3] = 0;
    //square lines
    sblx[0] = -0.25;	sbly[0] = -0.5;
    sblx[1] = -0.25;	sbly[1] = -1.25;
    sblx[2] = 0;	     sbly[2] = -1.25;
    sblx[3] = 0.25;	     sbly[3] = -0.5;
    sblx[4] = 0.25;		sbly[4] = -1.25;
    sblx[5] = 0.5;	     sbly[5] = -1.25;
    sblx[6] = 0.5;	     sbly[6] = -0.5;
    sblx[7] = 0.25;		sbly[7] = -0.25;
    sblx[8] = -0.25;	sbly[8] = -0.25;
    sblx[9] = 1.25;	     sbly[9] = 1.25;
    return;
}

//settrans method for polyman with matrix
void settrans1(void) {
    cout << "in settrans1" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(dx, dy, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    return;
}

//settrans for polywoman
void settrans2(void) {
    cout << "in settrans1" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(dxw, dyw, 0.0);
    glRotatef(thetaw, 0.0, 0.0, 1.0);
    return;
}

//settrans for square
void settrans3(void) {
    cout << "in settrans1" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(dxs, dys, 0.0);
    glRotatef(thetas, 0.0, 0.0, 1.0);
    return;
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
    if(dy <= -3) {
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
    if(j % 2) {
	   glColor3f(0.0, 0.0, 1.0);
	   glBegin(GL_LINE_STRIP);
	   for (i = 2; i <= 4; i++) {
		  glVertex2f(blx[i], bly[i]+0.15);
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
		  glVertex2f(blx[i], bly[i]+0.15);
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

//draw polywoman method
void drawIcon2(float bx[], float by[], float blx[], float bly[], float bex, float bey) {
    int i;
    int j = dxw;
    cout << "in drawicon" << endl;
    //draw the shape fo the polygon
    glColor3f(1.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glBegin(GL_POLYGON);
    for (i = 0; i <= 5; i++) glVertex2f(bx[i], by[i]);
    glEnd();

    if (frame == 9 && dxs <= -6.5) {
	   //draw the open mouth
	   if (dy <= -3) {
		  glColor3f(1.0, 1.0, 1.0);
		  glShadeModel(GL_FLAT);
		  glBegin(GL_POLYGON);
		  glShadeModel(GL_FLAT);
		  glBegin(GL_POLYGON);
		  glVertex2f(bx[0], by[0]);
		  glVertex2f(-blx[0], bly[0]);
		  glVertex2f(-blx[1], bly[1]);
		  glEnd();
	   }

	   //draw the corn rows
	   glColor3f(0.0, 0.0, 0.0);
	   glBegin(GL_LINES);
	   glVertex2f(-0.25, 0.75);
	   glVertex2f(-0.25, 0.5);
	   glVertex2f(-0.25 + 0.25, 0.75);
	   glVertex2f(-0.25 + 0.25, 0.5);
	   glVertex2f(-0.25 + 0.5, 0.75);
	   glVertex2f(-0.25 + 0.5, 0.5);
	   glEnd();

	   //draw the bows
	   glColor3f(1.0, 0.0, 1.0);
	   glBegin(GL_POLYGON);
	   glVertex2f(-0.35, 0.5);
	   glVertex2f(-0.15, 0.5);
	   glVertex2f(-0.15, 0.4);
	   glVertex2f(-0.35, 0.4);
	   glEnd();
	   glBegin(GL_POLYGON);
	   glVertex2f(-0.35 + 0.25, 0.5);
	   glVertex2f(-0.15 + 0.25, 0.5);
	   glVertex2f(-0.15 + 0.25, 0.4);
	   glVertex2f(-0.35 + 0.25, 0.4);
	   glEnd();
	   glBegin(GL_POLYGON);
	   glVertex2f(-0.35 + 0.5, 0.5);
	   glVertex2f(-0.15 + 0.5, 0.5);
	   glVertex2f(-0.15 + 0.5, 0.4);
	   glVertex2f(-0.35 + 0.5, 0.4);
	   glEnd();

	   //draw the legs, each leg take turn up and down when dx is even or odd
	   if (j % 2) {
		  glColor3f(1.0, 0.0, 0.0);
		  glBegin(GL_LINE_STRIP);
		  for (i = 2; i <= 4; i++) {
			 glVertex2f(-blx[i], bly[i] + 0.15);
		  }
		  glEnd();
		  glBegin(GL_LINE_STRIP);
		  for (i = 5; i <= 7; i++) {
			 glVertex2f(-blx[i], bly[i]);
		  }
		  glEnd();
	   }
	   else {
		  glColor3f(1.0, 0.0, 0.0);
		  glBegin(GL_LINE_STRIP);
		  for (i = 5; i <= 7; i++) {
			 glVertex2f(-blx[i], bly[i] + 0.15);
		  }
		  glEnd();
		  glBegin(GL_LINE_STRIP);
		  for (i = 2; i <= 4; i++) {
			 glVertex2f(-blx[i], bly[i]);
		  }
		  glEnd();
	   }

	   //draw the mouth
	   glColor3f(1.0, 1.0, 1.0);
	   glBegin(GL_LINES);
	   glVertex2f(-blx[0], bly[0]);
	   glVertex2f(-blx[1], bly[1]);
	   glEnd();

	   //draw the eyes
	   glPointSize(5);
	   glBegin(GL_POINTS);
	   glVertex2f(-bex, bey);
	   glEnd();
    }
    else {
	   //draw the corn rows
	   glColor3f(0.0, 0.0, 0.0);
	   glBegin(GL_LINES);
	   glVertex2f(0.25, 0.75);
	   glVertex2f(0.25, 0.5);
	   glVertex2f(0.25-0.25, 0.75);
	   glVertex2f(0.25-0.25, 0.5);
	   glVertex2f(0.25-0.5, 0.75);
	   glVertex2f(0.25-0.5, 0.5);
	   glEnd();

	   //draw the bows
	   glColor3f(1.0, 0.0, 1.0);
	   glBegin(GL_POLYGON);
	   glVertex2f(0.35, 0.5);
	   glVertex2f(0.15, 0.5);
	   glVertex2f(0.15, 0.4);
	   glVertex2f(0.35, 0.4);
	   glEnd();
	   glBegin(GL_POLYGON);
	   glVertex2f(0.35-0.25, 0.5);
	   glVertex2f(0.15-0.25, 0.5);
	   glVertex2f(0.15-0.25, 0.4);
	   glVertex2f(0.35-0.25, 0.4);
	   glEnd();
	   glBegin(GL_POLYGON);
	   glVertex2f(0.35-0.5, 0.5);
	   glVertex2f(0.15-0.5, 0.5);
	   glVertex2f(0.15-0.5, 0.4);
	   glVertex2f(0.35-0.5, 0.4);
	   glEnd();

	   //draw the legs, each leg take turn up and down when dx is even or odd
	   if (j % 2) {
		  glColor3f(1.0, 0.0, 0.0);
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
		  glColor3f(1.0, 0.0, 0.0);
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

	   //draw the mouth
	   glColor3f(1.0, 1.0, 1.0);
	   glBegin(GL_LINES);
	   glVertex2f(blx[0], bly[0]);
	   glVertex2f(blx[1], bly[1]);
	   glEnd();

	   //draw the eyes
	   glPointSize(5);
	   glBegin(GL_POINTS);
	   glVertex2f(bex, bey);
	   glEnd();
    }
    return;
}

//draw the square method
void drawSquare(float sbx[], float sby[], float sblx[], float sbly[], float sbex, float sbey) {
    int i;
    int j = dxs;
    cout << "in drawsquare" << endl;
    //draw the body
    if (dxw == -3.0) {
	   glColor3f(0.0, 1.0, 0.0);
	   glShadeModel(GL_FLAT);
	   glBegin(GL_POLYGON);
	   for (i = 0; i <= 3; i++) glVertex2f(sbx[i], sby[i]);
	   glEnd();

	   if (frame == 9) {
		  //draw the lance
		  glColor3f(0.0, 0.0, 0.0);
		  glShadeModel(GL_FLAT);
		  glBegin(GL_POLYGON);
		  glVertex2f(sblx[9], sbly[9]);
		  glVertex2f(sblx[8], sbly[8]);
		  glVertex2f(sblx[8] + sblx[8], sbly[8] - sbly[8]);
		  glEnd();

		  //draw the legs, mouth
		  //draw the legs, each leg take turn up and down when dx is even or odd
		  if (j % 2) {
			 glColor3f(1.0, 0.0, 0.0);
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 2; i++) {
				glVertex2f(-sblx[i], sbly[i] + 0.15);
			 }
			 glEnd();
			 glBegin(GL_LINE_STRIP);
			 for (i = 3; i <= 5; i++) {
				glVertex2f(-sblx[i], sbly[i]);
			 }
			 glEnd();
		  }
		  else {
			 glColor3f(1.0, 0.0, 0.0);
			 glBegin(GL_LINE_STRIP);
			 for (i = 3; i <= 5; i++) {
				glVertex2f(-sblx[i], sbly[i] + 0.15);
			 }
			 glEnd();
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 2; i++) {
				glVertex2f(-sblx[i], sbly[i]);
			 }
			 glEnd();
		  }

		  glColor3f(0.0, 0.0, 0.0);
		  glPointSize(5);
		  glBegin(GL_POINTS);
		  glVertex2f(-sbex, sbey);
		  glEnd();

		  glColor3f(0.0, 0.0, 0.0);
		  glBegin(GL_LINE_STRIP);
		  glVertex2f(-sblx[6], sbly[6]);
		  glVertex2f(-sblx[7], sbly[7]);
		  glEnd();
	   }
	   else {
		  //draw the lance
		  glColor3f(0.0, 0.0, 0.0);
		  glShadeModel(GL_FLAT);
		  glBegin(GL_POLYGON);
		  glVertex2f(sblx[9], sbly[9]);
		  glVertex2f(sblx[8], sbly[8]);
		  glVertex2f(sblx[8] + sblx[8], sbly[8] - sbly[8]);
		  glEnd();

		  //draw the legs, mouth
		  //draw the legs, each leg take turn up and down when dx is even or odd
		  if (j % 2) {
			 glColor3f(1.0, 0.0, 0.0);
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 2; i++) {
				glVertex2f(sblx[i], sbly[i] + 0.15);
			 }
			 glEnd();
			 glBegin(GL_LINE_STRIP);
			 for (i = 3; i <= 5; i++) {
				glVertex2f(sblx[i], sbly[i]);
			 }
			 glEnd();
		  }
		  else {
			 glColor3f(1.0, 0.0, 0.0);
			 glBegin(GL_LINE_STRIP);
			 for (i = 3; i <= 5; i++) {
				glVertex2f(sblx[i], sbly[i] + 0.15);
			 }
			 glEnd();
			 glBegin(GL_LINE_STRIP);
			 for (i = 0; i <= 2; i++) {
				glVertex2f(sblx[i], sbly[i]);
			 }
			 glEnd();
		  }

		  glColor3f(0.0, 0.0, 0.0);
		  glPointSize(5);
		  glBegin(GL_POINTS);
		  glVertex2f(sbex, sbey);
		  glEnd();

		  glColor3f(0.0, 0.0, 0.0);
		  glBegin(GL_LINE_STRIP);
		  glVertex2f(sblx[6], sbly[6]);
		  glVertex2f(sblx[7], sbly[7]);
		  glEnd();
	   }
    }
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
	   if (dxw >= -3.5) {
		  dxw = -3.5;
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

    case 4: //polyman goes down, polywoman rock backward
	   dy -= 0.15;
	   if (dy <= -3.0) {
		  dy = -3.0;
		  thetaw += 0.5;
		  if (thetaw >= 20) {
			 thetaw = 20;
			 frame = 5;
		  }
	   }
	   break;

    case 5: //polywoman rock forward
	   thetaw -= 0.5;
	   if (thetaw <= 0.0) {
		  thetaw = 0.0;
		  dxw += 0.15;
		  if (dxw >= -3) {
			 dxw = -3;
			 frame = 6;
		  }
	   }
	   break;

    case 6: //square enter
	   dxs += 0.15;
	   if (dxs >= -3.5) {
		  dxs = -3.5;
		  frame = 7;
	   }
	   break;

    case 7: //square stab
	   dxs += 0.15;
	   if (dxs >= 1) {
		  dxs = 1;
		  thetas -= 10;
		  if (thetas <= -50) {
			 thetas = -50;
			 frame = 8;
		  }
	   }
	   break;

    case 8: //polyman die
	   theta -= 10;
	   if (theta <= -100) {
		  theta = -100;
		  thetas += 10;
		  if (thetas >= 0.0) {
			 thetas = 0.0;
			 frame = 9;
		  }
	   }
	   break;

    case 9:  //square leave
	   dxs -= 0.15;
	   if (dxs <= -6.5) {
		  dxw -= 0.15;
	   }
	   break;
    }

    glutPostRedisplay();
    glutTimerFunc(30, TimerFunction, 1);
}