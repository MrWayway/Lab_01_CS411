#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
void renderScene(void)
{
	int X0 = 9, X1 = 100, Y0 = 9, Y1 = 100;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

	glPointSize(20.0f);

	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels 
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps 
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step 
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++)
	{
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(X, Y, 0.0f);
		glEnd();
		X += Xinc;          
		Y += Yinc;         
	}
	glutSwapBuffers();
	
}

void Init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);   //this one
	glPointSize(5);             //and this one

	glMatrixMode(GL_PROJECTION);    //coordinate system
	//glLoadIdentity();
	gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");

	Init();
	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}