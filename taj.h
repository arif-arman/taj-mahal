#include<iostream>
#include<windows.h>
#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/gl.h>
#define ll long long
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define BS binary_search
#define SIZE 400006
#define MOD 1000000007
#define BLACK 0, 0, 0

using namespace std;

inline ll getnum()
{
	char c = getchar();
	ll num, sign = 1;
	for (; c<'0' || c>'9'; c = getchar())if (c == '-')sign = -1;
	for (num = 0; c >= '0'&&c <= '9';)
	{
		c -= '0';
		num = num * 10 + c;
		c = getchar();
	}
	return num*sign;
}

int plane[6] = { GL_CLIP_PLANE0, GL_CLIP_PLANE1, GL_CLIP_PLANE2, GL_CLIP_PLANE3, GL_CLIP_PLANE4, GL_CLIP_PLANE5 };

double cameraAngle;			//in radian
double cameraAngleDelta;

double cameraHeight;
double cameraRadius;

double camUP;

double camX = 0, camY = 0, camZ = 0;
double lookX = 100, lookY = 0, lookZ = 0;
double upX = 0, upY = 0, upZ = 100;
double lrX = 0, lrY = 100, lrZ = 0;
double lookA = 0.1, upA = 0.1, lrA = 0.1;
double lookM = 4, upM = 4, lrM = 4;

double rectAngle;	//in degree

double chandelierAngle;

bool canDrawGrid;

void increase(double x, double y, double z) {
	camX += x; camZ += z; camY += y;
	lookX += x; lookY += y; lookZ += z;
	lrX += x; lrY += y; lrZ += z;
	upX += x; upY += y; upZ += z;
}

void notroof() {
	GLUquadric *quad = gluNewQuadric();
	{
		glColor3f(0.4, 0.4, 0.4);

		for (int i = 0; i < 6; i++) {
			double theta = (2 * 3.1416 / 6) * i;
			double r = 8;
			double x1 = r*sin(theta);
			double y1 = r*cos(theta);
			double theta2 = (2 * 3.1416 / 6) * ((i + 1) % 6);
			double x2 = r*sin(theta2);
			double y2 = r*cos(theta2);
			double delx = (x2 - x1) / 3;
			double dely = (y2 - y1) / 3;
			r = 5;
			double x3 = r*sin(theta);
			double y3 = r*cos(theta);
			double x4 = r*sin(theta2);
			double y4 = r*cos(theta2);
			double delx2 = (x4 - x3) / 3;
			double dely2 = (y4 - y3) / 3;
			for (int j = 0; j < 3; j++) {
				glPushMatrix(); {
					glTranslatef(x1 + delx*j, y1 + dely*j, 3);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);


				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3);
					glBegin(GL_QUADS); {
						glVertex3f(x1 + delx*j, y1 + dely*j, 0);
						glVertex3f(x1 + delx*j, y1 + dely*j, -0.5);
						glVertex3f(x3 + delx2*j, y3 + dely2*j, -2);
						glVertex3f(x3 + delx2*j, y3 + dely2*j, 0);

					}
					glEnd();
				}
				glPopMatrix();
			}

		}

	}
	glPushMatrix();
	glTranslatef(0, 0, 4.5);
	gluCylinder(quad, 8, 8, 0.6, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2);
	gluCylinder(quad, 7, 7, 1, 30, 30);
	glPopMatrix();

	// second base
}

void domeTaj(bool main) {
	GLUquadric *quad = gluNewQuadric();
	if (main) {
		// base

		gluCylinder(quad, 6, 6, 3, 200, 200);
		// second base
		glPushMatrix(); {
			glTranslatef(0, 0, 3);
			glColor3f(0, 1, 0);
			gluCylinder(quad, 6, 6, 2, 200, 200);
		}
		glPopMatrix();
		// third base angular white
		glPushMatrix(); {
			glTranslatef(0, 0, 5);
			glColor3f(1, 1, 1);
			gluCylinder(quad, 6, 6.8, 1.5, 200, 200);
		}
		glPopMatrix();

	}
	// fourth base, angular gray
	glPushMatrix(); {
		glTranslatef(0, 0, 6.5);
		glColor3f(0, 1, 0);
		gluCylinder(quad, 6.8, 7, .5, 200, 200);
	}
	glPopMatrix();
	glColor3f(1, 0, 0);
	glPushMatrix(); {
		glTranslatef(0, 0, 7);
		glScalef(1, 1, 1.2);
		double equ[4];
		equ[0] = 0; equ[1] = 0; equ[2] = 1; equ[3] = 0;
		glClipPlane(GL_CLIP_PLANE0, equ);
		glEnable(GL_CLIP_PLANE0); {
			glPushMatrix(); {
				double equ1[4];
				equ1[0] = 0; equ1[1] = 0; equ1[2] = -1; equ1[3] = 6.5;
				glClipPlane(GL_CLIP_PLANE1, equ1);
				glEnable(GL_CLIP_PLANE1); {
					glColor3f(1, 1, 1);
					gluSphere(quad, 7, 200, 200);
				}
				glDisable(GL_CLIP_PLANE1);

			}
			glPopMatrix();
		}
		glDisable(GL_CLIP_PLANE0);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0, 0, 14.5);
		glScalef(0.3, 0.3, 0.3);
		domeTop();
	}
	glPopMatrix();
}

void secondTaj() {
	double y = 0, front = 1;
	if (front == -1) y = 20;
	// side gate
	// blue base extended
	{glColor3f(0, 0, 1);
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 0, 0);
		glVertex3f(11, y + 0, 1.3);
		glVertex3f(13, y + 0, 1.3);
		glVertex3f(13, y + 0, 0);
	}
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 0, 9);
		glVertex3f(11, y + 0, 18);
		glVertex3f(21, y + 0, 18);
		glVertex3f(21, y + 0, 9);
	}
	glEnd();

	glBegin(GL_QUADS); {
		glVertex3f(11, y + 0, 9);
		glVertex3f(11, y + 0, 1.3);
		glVertex3f(13, y + 0, 1.3);
		glVertex3f(13, y + 0, 9);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(19, y + 0, 9);
		glVertex3f(19, y + 0, 1.3);
		glVertex3f(21, y + 0, 1.3);
		glVertex3f(21, y + 0, 9);
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS); {
		glVertex3f(19, y + 0, 0);
		glVertex3f(19, y + 0, 1.3);
		glVertex3f(21, y + 0, 1.3);
		glVertex3f(21, y + 0, 0);
	}
	glEnd();
	}
	// second cylinder
	glPushMatrix(); {
		glColor3f(1, 0, 0);
		glTranslatef(21, y + 0, 0);
		GLUquadric *quad;
		quad = gluNewQuadric();
		gluCylinder(quad, .3, .3, 21, 20, 20);

	}
	glPopMatrix();
	// second part border
	// inner square
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS); {	// left
		glVertex3f(13, y - 0.2 * front, 10);
		glVertex3f(12.5, y - 0.2 * front, 10);
		glVertex3f(12.5, y - 0.2 * front, 15);
		glVertex3f(13, y - 0.2 * front, 15);
	}
	glEnd();
	glBegin(GL_QUADS); {	// right
		glVertex3f(19, y - 0.2 * front, 10);
		glVertex3f(19.5, y - 0.2 * front, 10);
		glVertex3f(19.5, y - 0.2 * front, 15);
		glVertex3f(19, y - 0.2 * front, 15);
	}
	glEnd();
	glBegin(GL_QUADS); {	// top
		glVertex3f(13, y - 0.2 * front, 14.5);
		glVertex3f(19, y - 0.2 * front, 14.5);
		glVertex3f(19, y - 0.2 * front, 15);
		glVertex3f(13, y - 0.2 * front, 15);
	}
	glEnd();
	glBegin(GL_QUADS); {	// bottom
		glVertex3f(13, y - 0.2 * front, 10.5);
		glVertex3f(19, y - 0.2 * front, 10.5);
		glVertex3f(19, y - 0.2 * front, 10);
		glVertex3f(13, y - 0.2 * front, 10);
	}
	glEnd();
	// big border
	glBegin(GL_QUADS); { // left
		glVertex3f(11, y - 0.2 * front, 1.3);
		glVertex3f(11.5, y - 0.2 * front, 1.3);
		glVertex3f(11.5, y - 0.2 * front, 16);
		glVertex3f(11, y - 0.2 * front, 16);
	}
	glEnd();
	glBegin(GL_QUADS); { // right
		glVertex3f(20.8, y - 0.2 * front, 1.3);
		glVertex3f(20.3, y - 0.2 * front, 1.3);
		glVertex3f(20.3, y - 0.2 * front, 16);
		glVertex3f(20.8, y - 0.2 * front, 16);
	}
	glEnd();
	glBegin(GL_QUADS); { // top
		glVertex3f(20.3, y - 0.2 * front, 15.5);
		glVertex3f(11.5, y - 0.2 * front, 15.5);
		glVertex3f(11.5, y - 0.2 * front, 16);
		glVertex3f(20.3, y - 0.2 * front, 16);
	}
	glEnd();
	glBegin(GL_QUADS); { // inner left
		glVertex3f(13, y - 0.2 * front, 1.3);
		glVertex3f(12.5, y - 0.2 * front, 1.3);
		glVertex3f(12.5, y - 0.2 * front, 9.5);
		glVertex3f(13, y - 0.2 * front, 9.5);
	}
	glEnd();
	glBegin(GL_QUADS); { // inner right
		glVertex3f(19, y - 0.2 * front, 1.3);
		glVertex3f(19.5, y - 0.2 * front, 1.3);
		glVertex3f(19.5, y - 0.2 * front, 9.5);
		glVertex3f(19, y - 0.2 * front, 9.5);
	}
	glEnd();
	glBegin(GL_QUADS); { // inner top
		glVertex3f(13, y - 0.2 * front, 9);
		glVertex3f(19, y - 0.2 * front, 9);
		glVertex3f(19, y - 0.2 * front, 9.5);
		glVertex3f(13, y - 0.2 * front, 9.5);
	}
	glEnd();
	// chamber
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS); { // left
		glVertex3f(13, y + 0, 0);
		glVertex3f(13, y + 0, 10);
		glVertex3f(13, y + 3 * front, 10);
		glVertex3f(13, y + 3 * front, 0);
	}
	glEnd();
	glBegin(GL_QUADS); { // right
		glVertex3f(19, y + 0, 0);
		glVertex3f(19, y + 0, 10);
		glVertex3f(19, y + 3 * front, 10);
		glVertex3f(19, y + 3 * front, 0);
	}
	glEnd();
	glBegin(GL_QUADS); { // back
		glVertex3f(13, y + 3 * front, 0);
		glVertex3f(13, y + 3 * front, 10);
		glVertex3f(19, y + 3 * front, 10);
		glVertex3f(19, y + 3 * front, 0);
	}
	glEnd();
	// base
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS); {
		glVertex3f(13, y + 0, 0);
		glVertex3f(13, y + 3 * front, 0);
		glVertex3f(19, y + 3 * front, 0);
		glVertex3f(19, y + 0, 0);
	}
	glEnd();
	// chamber top curve

	// upper white jinish
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); {
		glVertex3f(15, y - 0.1*front, 10.5);
		glVertex3f(15, y - 0.1*front, 14);
		glVertex3f(17, y - 0.1*front, 14);
		glVertex3f(17, y - 0.1*front, 10.5);
	}
	glEnd();
	// top blue part
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 0, 18);
		glVertex3f(11, y + 0, 19);
		glVertex3f(21, y + 0, 19);
		glVertex3f(21, y + 0, 18);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 1, 18);
		glVertex3f(11, y + 1, 19);
		glVertex3f(21, y + 1, 19);
		glVertex3f(21, y + 1, 18);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(21, y + 0, 18);
		glVertex3f(21, y + 0, 19);
		glVertex3f(21, y + 1, 19);
		glVertex3f(21, y + 1, 18);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 0, 18);
		glVertex3f(11, y + 0, 19);
		glVertex3f(11, y + 1, 19);
		glVertex3f(11, y + 1, 18);
	}
	glEnd();

	// top red
	glColor3f(1, 1, 0.7);
	glBegin(GL_QUADS); {
		glVertex3f(11, y + 1.2, 19);
		glVertex3f(11, y - 0.2, 19);
		glVertex3f(21, y - 0.2, 19);
		glVertex3f(21, y + 1.2, 19);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glVertex3f(21, y + 1.2, 18);
		glVertex3f(21, y - 0.2, 18);
		glVertex3f(11, y - 0.2, 18);
		glVertex3f(11, y + 1.2, 18);
	}
	glEnd();
}

void sentryTaj() {
	GLUquadric *quad = gluNewQuadric();
	// columns
	for (int i = 0; i < 6; i++) {
		double theta = (2 * 3.1416 / 6) * i;
		double r = 6;
		glPushMatrix(); {
			glTranslatef(r*sin(theta), r*cos(theta), 0);
			glColor3f(1, 1, 1);
			gluCylinder(quad, 0.5, 0.5, 10, 4, 100);
		}
		glPopMatrix();
	}
	// triangular small gates
	double ang = 3.1412 / 4, anr = ang * 2;
	glBegin(GL_QUADS);
	for (int k = 0; k <= 8; k++)for (int a = 0, j = a + k; a <= 3; a++, j++)glVertex3f(7 * cos(j*ang), 7 * sin(j*ang), 0.1);
	for (int j = 0; j <= 4; j++)glVertex3f(5 * cos(j*anr), 5 * sin(j*anr), 0.1);
	glEnd();
	// roof
	glPushMatrix(); {
		glColor3f(1, 0, 1);
		glTranslatef(0, 0, 10);
		gluCylinder(quad, 9, 4, 1, 8, 100);
		// dome
		glPushMatrix(); {
			glTranslatef(0, 0, -6);
			glColor3f(1, 0, 0);
			//glScalef(0.6, 0.6, 0.6);
			dome(false);
		}
		glPopMatrix();
	}
	glPopMatrix();
	for (double i = 0; i < 0.5; i += 0.1) {
		glPushMatrix(); {
			glColor3f(1, 0, 1);
			glTranslatef(0, 0, 10.2);
			gluCylinder(quad, 4 - i, 4 - i, 0.5, 8, 100);
		}
		glPopMatrix();

	}
}

void quaterTaj() {
	firstPart(1);
	secondTaj();
	glPushMatrix();
	glTranslatef(13.4, -8, 0);
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	secondTaj();
	glPopMatrix();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); {
		glVertex3f(-1, 5, 10.5);
		glVertex3f(-1, 5, 14);
		glVertex3f(1, 5, 14);
		glVertex3f(1, 5, 10.5);
	}
	glEnd();

	glBegin(GL_QUADS); {
		glVertex3f(1.5, 5, 5);
		glVertex3f(1.5, 5, 0);
		glVertex3f(-1.5, 5, 0);
		glVertex3f(-1., 5, 5);
	}
	glEnd();


	glColor3f(1, 1, 0);
	glBegin(GL_QUADS); {
		glVertex3f(5, 5, 0);
		glVertex3f(4.5, 5, 0);
		glVertex3f(4.5, 5, 10);
		glVertex3f(5, 5, 10);
	}
	glEnd();

	glBegin(GL_QUADS); {
		glVertex3f(5, 5, 9.5);
		glVertex3f(5, 5, 10);
		glVertex3f(-1, 5, 10);
		glVertex3f(-1, 5, 9.5);
	}
	glEnd();


}

void towerTaj() {
	GLUquadric *quad;
	quad = gluNewQuadric();
	double ang = 3.1412 / 4;


	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(50, -50, -6);
	gluCylinder(quad, 4, 4, 7, 8, 30);
	glColor3f(0.9, 0.9, 1);
	gluCylinder(quad, 3, 2, 50, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, -50, 0.01);//top octa
	glBegin(GL_QUADS);
	for (int k = 0; k <= 8; k++)for (int a = 0, j = a + k; a <= 3; a++, j++)glVertex3f(4 * cos(j*ang), 4 * sin(j*ang), 0);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 0, 40);
	glScalef(0.5, 0.5, 1);
	sentryRoom(0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 27);
	glScalef(0.35, 0.35, 1);
	notroof();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 13);
	glScalef(0.4, 0.4, 1);
	notroof();
	glPopMatrix();


	glPopMatrix();
}

void makeTaj() {

	for (int i = 0; i <= 3; i++)
	{
		glPushMatrix();
		glRotatef(90 * i, 0, 0, 1);
		glPushMatrix();

		glColor3f(0.6, 0.6, 0.6);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, 18);
		glVertex3f(0, 27, 18);
		glVertex3f(22, 27, 18);
		glVertex3f(27, 22, 18);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(0, 0, 18);
		glVertex3f(27, 0, 18);
		glVertex3f(27, 22, 18);
		glVertex3f(22, 27, 18);
		glEnd();


		glTranslatef(0, -28, 0);
		quaterTaj();
		glPushMatrix();
		glScalef(-1, 1, 1);
		quaterTaj();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
	glScalef(0.6, 0.6, 0.6);
	for (int i = 0; i <= 3; i++)
	{
		glPushMatrix();
		glRotatef(90 * i, 0, 0, 1);
		glPushMatrix();
		glTranslatef(30, 30, 30);
		glScalef(0.8, 0.8, 0.8);
		sentryTaj();
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 14);
	glScalef(2.7, 2.7, 2.7);
	domeTaj(true);
	glPopMatrix();
}

void baseTaj() {
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); //top
	glVertex3f(50, -50, -0.01);
	glVertex3f(-50, -50, -0.01);
	glVertex3f(-50, 50, -0.01);
	glVertex3f(50, 50, -0.01);
	glEnd();


	glColor3f(0.8, 0.8, 1);
	for (int i = 0; i <= 3; i++) //sides
	{
		glPushMatrix();
		glRotatef(90 * i, 0, 0, 1);
		glPushMatrix();
		glBegin(GL_QUADS); //left?
		glVertex3f(-50, 50, 0);
		glVertex3f(-50, 50, -4);
		glVertex3f(50, 50, -4);
		glVertex3f(50, 50, 0);
		glEnd();
		glPopMatrix();
		glPopMatrix();
	}


	for (int i = 0; i <= 3; i++) //tower base
	{
		glPushMatrix();
		glRotatef(90 * i, 0, 0, 1);
		glScalef(1, 1, 0.6);
		towerTaj();
		glPopMatrix();
	}
}
