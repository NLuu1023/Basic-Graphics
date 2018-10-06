/*//Nhung Luu
//CSC328
//Assignment 1: graphing functions

#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

//function set up the render state including the background color of the window
void SetupRC(void) {
	//set background color to white
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	return;
}

//funciton to render scene: setting up the graph and graphing the functions
void RenderScene(void) {
	//color the window background
	//set the three colors for the function lines
	double x, y, xdel = 0.25;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//line color for functions
	glColor3f(0.0, 0.0, 0.0);
	//set viewport and ortho
	glViewport(100, 100, 900, 500);
	glOrtho(-10.0, 10.0, -50.0, 50.0, 1.0, -1.0);
	//draw the graph
	glBegin(GL_LINES);
	//set the x-axis
	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	for (x = -10.0; x <= 10.0; x += 1.0) {
		glVertex2f(x, -1.0);
		glVertex2f(x, 1.0);
	}
	//set the y-axis
	glVertex2f(0.0, -50.0);
	glVertex2f(0.0, 50.0);
	for (y = -50.0; y <= 50.0; y += 1.0) {
		glVertex2f(-0.15, y);
		glVertex2f(0.15, y);
	}
	glEnd();

	//draw the function x^3+x^2-20x
	glBegin(GL_LINE_STRIP);
	for (x = -10.0; x <= 10.0; x += xdel) {
		y = pow(x,3.0) + pow(x,2.0) - (20.0 * x);
		glVertex2f(x, y);
	}
	glEnd();

	//set a different color for next function
	glColor3f(1.0, 0.0, 0.0);
	//draw 10cos(x)+3
	glBegin(GL_LINE_STRIP);
	for (x = -10.0; x <= 10.0; x += xdel) {
		y = (10.0 * cos(x)) + 3.0;
		glVertex2f(x, y);
	}
	glEnd();

	//set diferent color for the third function
	glColor3f(0.0, 0.0, 1.0);
	//draw combination of first function subtract second function
	glBegin(GL_LINE_STRIP);
	for (x = -10.0; x <= 10.0; x += xdel) {
		y = (pow(x, 3.0) + pow(x, 2.0) - (20.0 * x)) - ((10.0 * cos(x)) + 3.0);
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
	return;
}

int main(int argc, char* *argv) {
	//set window title
	char header[] = "Graph of 3 Functions by Nhung Luu";
	//initialize the glopen and set up the window size and position
	glutInit(&argc, argv);
	glutInitWindowSize(1016, 680);
	glutInitWindowPosition(0, 0);
	//Open window with label
	glutCreateWindow(header);
	//input function that will draw the scene
	glutDisplayFunc(RenderScene);
	//set state of the rendering machine with the background color
	SetupRC();
	//execute OpenGL
	glutMainLoop();
	return 0;
};*/