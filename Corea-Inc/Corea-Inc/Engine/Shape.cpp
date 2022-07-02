#include "Shape.h"
#include "GL/glew.h"
#include <cmath>

void clear_background(double red, double green, double blue, double alpha)
{
	glClearColor((GLclampf)red, (GLclampf)green, (GLclampf)blue, (GLclampf)alpha);
}

void set_fill_color(double red, double green, double blue, double alpha)
{
	glColor4b((GLbyte)red, (GLbyte)green, (GLbyte)blue, (GLbyte)alpha);
}

void set_outline_color(/*GLbyte*/ double red, double green, double blue)
{
	glColor3b((GLbyte)red, (GLbyte)green, (GLbyte)blue);
}

void draw_point(double x, double y)
{
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glFinish();
}

void draw_line(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glFinish();
}

void draw_ellipse(double x, double y, double angle)
{
	double rad = 0.5;
	int max_angle = 360;

	glBegin(GL_POLYGON);
	for (int i = 0; i < max_angle; i++)
	{
		angle = i * 3.141592 / 180;
		x = rad * cos(angle);
		y = rad * sin(angle);
		glVertex2f((GLfloat)x, (GLfloat)y);
	}
	glEnd();
	glFinish();
}

void draw_rect(double x, double y, double w, double h)
{
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glFinish();
}