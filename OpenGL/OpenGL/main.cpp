#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <math.h>

using namespace std;

void renderScene(void)
{
	int X0 = 9, X1 = 100, Y0 = 9, Y1 = 100;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

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

void LineBersenham(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	int x1 = 100, y1 = 300, x2 = 200, y2 = 500;
	int m_new = 2 * (y2 - y1);
	int slope_error_new = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++)
	{
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x, y, 0);
		glEnd();
	
		slope_error_new += m_new;
 
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * (x2 - x1);
		}
	}
	glutSwapBuffers();
}

void CircleMidPoint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	int x_cen = 300, y_cen = 300, r = 200;
	int x = r;
	int y = 0;

	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3f(x + x_cen, y + y_cen, 0.0);

	if (r > 0)
	{
		glVertex3f(x + x_cen, -y + y_cen, 0.0);
		glVertex3f(y + x_cen, x + y_cen, 0.0);
		glVertex3f(-y + x_cen, x + y_cen, 0.0);
	}

	int P = 1 - r;
	while (x > y)
	{
		y++;

		// Mid-point is inside or on the perimeter 
		if (P <= 0)
			P = P + 2 * y + 1;
		// Mid-point is outside the perimeter 
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed 
		if (x < y)
			break;

		// Printing the generated point and its reflection 
		// in the other octants after translation 
		glVertex3f(x + x_cen, y + y_cen, 0.0);
		glVertex3f(-x + x_cen, y + y_cen, 0.0);
		glVertex3f(x + x_cen, -y + y_cen, 0.0);
		glVertex3f(-x + x_cen, -y + y_cen, 0.0);

		// If the generated point is on the line x = y then  
		// the perimeter points have already been printed 
		if (x != y)
		{
			glVertex3f(y + x_cen, x + y_cen, 0.0);
			glVertex3f(-y + x_cen, x + y_cen, 0.0);
			glVertex3f(y + x_cen, -x + y_cen, 0.0);
			glVertex3f(-y + x_cen, -x + y_cen, 0.0);
		}
	}
	glEnd();
	glutSwapBuffers();
}

void EllipseMidPoint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	int rx = 200, ry = 200, xc = 500, yc = 500;
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	// Initial decision parameter of region 1 
	d1 = (ry * ry) - (rx * rx * ry) +
		(0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(xc, yc, 0.0);

	// For region 1 
	while (dx < dy)
	{

		// Print points based on 4-way symmetry 
		glVertex3f(x + xc, y + yc, 0.0);
		glVertex3f(-x + xc, y + yc, 0.0);
		glVertex3f(x + xc, -y + yc, 0.0);
		glVertex3f(-x + xc, -y + yc, 0.0);
		

		// Checking and updating value of 
		// decision parameter based on algorithm 
		if (d1 < 0)
		{
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}
		else
		{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}

	// Decision parameter of region 2 
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	// Plotting points of region 2 
	while (y >= 0)
	{

		// Print points based on 4-way symmetry 
		glVertex3f(x + xc, y + yc, 0.0);
		glVertex3f(-x + xc, y + yc, 0.0);
		glVertex3f(x + xc, -y + yc, 0.0);
		glVertex3f(-x + xc, -y + yc, 0.0);


		// Checking and updating parameter 
		// value based on algorithm 
		if (d2 > 0)
		{
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}
		else
		{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
	glEnd();
	glutSwapBuffers();
}

void ParaMidPoint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	float midY = 240;
	float midX = 320;

	float y = 0;

	
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (float x = -200; x <= 200; x += 0.05) {
		y = x * x;
		glVertex3f(midX + x, midY + y, 0.0);
	}
	glEnd();
	glutSwapBuffers();
}

void HyperMidPoint(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 1.0f);

	int xc = 600, yc = 600;
	long rx = 6;
	long ry = 8;
	int bound = 100;

	long x, y, d, mida, midb;
	long tworx2, twory2, rx2, ry2;
	long x_slop, y_slop;
	x = rx; y = 0;
	rx2 = rx * rx;
	ry2 = ry * ry;
	tworx2 = 2 * rx2; twory2 = 2 * ry2;
	x_slop = 2 * twory2 * (x + 1);
	y_slop = 2 * tworx2;
	mida = x_slop / 2; midb = y_slop / 2;
	d = tworx2 - ry2 * (1 + 2 * rx) + midb;
	while ((d < x_slop) && (y <= bound))
	{
		glVertex2f(x, y);
		if (d >= 0)
		{
			d -= x_slop;
			x++;
			x_slop += 2 * tworx2;
		}
		d += tworx2 + y_slop;
		y++;
		y_slop += 2 * tworx2;
	}
	d -= (x_slop + y_slop) / 2 + (rx2 + ry2) - midb - mida;
	if (rx > ry)
	{
		while (y <= bound)
		{
			glVertex4f(xc, yc, x, y);
			if (d <= 0)
			{
				d += y_slop;
				y++;
				y += 2 * tworx2;
			}
			d -= twory2 - x_slop;
			x++;
			x_slop += 2 * twory2;
		}
	}
	glEnd();
	glutSwapBuffers();
}


void Init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");

	Init();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(HyperMidPoint);

	glutMainLoop();

	return 0;
}