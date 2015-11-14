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

// done
void sentryRoom1(bool roof) {
	GLUquadric *quad = gluNewQuadric();
	if (!roof) {

		// first base
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, basetaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 5, 5, 3, 6, 100);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);


		// second base khaj
		glColor3f(1, 1, 1);
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
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, floortaj);
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glDisable(GL_TEXTURE_2D);




				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3);

					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, floortaj);
					glNormal3f(1.0, 0.0, 0.0);
					glBegin(GL_POLYGON);
					glTexCoord2f(0, 0); glVertex3f(x1 + delx*j, y1 + dely*j, 0);
					glTexCoord2f(1, 0); glVertex3f(x3 + delx2*j, y3 + dely2*j, 0);
					glTexCoord2f(1, 1); glVertex3f(x3 + delx2*j, y3 + dely2*j, -2);
					glTexCoord2f(0, 1); glVertex3f(x1 + delx*j, y1 + dely*j, -0.5);
					glEnd();
					glDisable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}

		}

	}
	// second base
	glPushMatrix(); {
		glTranslatef(0, 0, 3);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, basetaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 8, 8, 2, 6, 100);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);

	}
	glPopMatrix();
	// first base floor
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floortaj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(7, -4, 3);
	glTexCoord2f(1, 0); glVertex3f(-7, -4, 3);
	glTexCoord2f(1, 1); glVertex3f(-7, 4, 3);
	glTexCoord2f(0, 1); glVertex3f(7, 4, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floortaj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(7, 4, 3);
	glTexCoord2f(1, 0); glVertex3f(-7, 4, 3);
	glTexCoord2f(1, 1); glVertex3f(0, 8, 3);
	glTexCoord2f(0, 1); glVertex3f(0, 8, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floortaj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(7, -4, 3);
	glTexCoord2f(1, 0); glVertex3f(-7, -4, 3);
	glTexCoord2f(1, 1); glVertex3f(0, -8, 3);
	glTexCoord2f(0, 1); glVertex3f(0, -8, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	// vitorer cylinder (main room)
	for (double i = 0; i < 0.5; i += 0.1) {
		glPushMatrix(); {
			glTranslatef(0, 0, 3);
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, basetaj);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 4 - i, 4 - i, 1, 6, 100);
				glMatrixMode(GL_TEXTURE);
			} glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);

		}
		glPopMatrix();
	}
	// columns
	for (int i = 0; i < 6; i++) {
		double theta = (2 * 3.1416 / 6) * i;
		double r = 4;
		glPushMatrix(); {
			glTranslatef(r*sin(theta), r*cos(theta), 3);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, floortaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 0.3, 0.3, 1, 60, 100);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, floortaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 0.2, 0.2, 5, 60, 100);
			glDisable(GL_TEXTURE_2D);
			glPushMatrix(); {
				glTranslatef(0, 0, 5);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, floortaj);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);
				gluCylinder(quad, 0.3, 0.3, 2, 60, 100);
				glDisable(GL_TEXTURE_2D);

			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	// triangular small gates
	for (int i = 0; i < 6; i++) {
		double theta = (2 * 3.1416 / 6) * i;
		double r = 4;
		double x1 = r*sin(theta);
		double y1 = r*cos(theta);
		double z1 = 8;
		double theta2 = (2 * 3.1416 / 6) * ((i + 1) % 6);
		double x2 = r*sin(theta2);
		double y2 = r*cos(theta2);
		double z2 = 10;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, basetaj);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 0); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2);
		glTexCoord2f(1, 1); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2 - 1);
		glTexCoord2f(0, 1); glVertex3f(x1, y1, z1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, basetaj);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(x2, y2, z2);
		glTexCoord2f(1, 0); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2);
		glTexCoord2f(1, 1); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2 - 1);
		glTexCoord2f(0, 1); glVertex3f(x2, y2, z1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	// roof
	glPushMatrix(); {

		glTranslatef(0, 0, 9.2);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, floortaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 9, 4, 1, 8, 100);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);

		// dome
		glPushMatrix(); {
			glTranslatef(0, 0, -2.5);
			glScalef(0.6, 0.6, 0.6);
			dome(false);
		}
		glPopMatrix();
	}
	glPopMatrix();
	for (double i = 0; i < 0.5; i += 0.1) {
		glPushMatrix(); {

			glTranslatef(0, 0, 10.2);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, floortaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 4 - i, 4 - i, 0.5, 8, 100);
			glDisable(GL_TEXTURE_2D);

		}
		glPopMatrix();

	}



}

// done
void increase(double x, double y, double z) {
	camX += x; camZ += z; camY += y;
	lookX += x; lookY += y; lookZ += z;
	lrX += x; lrY += y; lrZ += z;
	upX += x; upY += y; upZ += z;
}

// done
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
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, towertaj); // here texid corresponds a bitmap image.
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glDisable(GL_TEXTURE_2D);
					


				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, white_rect);
					glNormal3f(1.0, 0.0, 0.0);
					glBegin(GL_POLYGON);
					glTexCoord2f(0, 0); glVertex3f(x1 + delx*j, y1 + dely*j, 0);
					glTexCoord2f(1, 0); glVertex3f(x3 + delx2*j, y3 + dely2*j, 0);
					glTexCoord2f(1, 1); glVertex3f(x3 + delx2*j, y3 + dely2*j, -2);
					glTexCoord2f(0, 1); glVertex3f(x1 + delx*j, y1 + dely*j, -0.5);
					glEnd();
					glDisable(GL_TEXTURE_2D);

				}
				glPopMatrix();
			}

		}

	}
	glPushMatrix();
	glTranslatef(0, 0, 4.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, towertaj); // here texid corresponds a bitmap image.
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GLU_TRUE);
	gluCylinder(quad, 8, 8, 0.6, 30, 30);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, towertaj); // here texid corresponds a bitmap image.
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GLU_TRUE);
	gluCylinder(quad, 7, 7, 1, 30, 30);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();

	// second base
}

// done
void domeTaj(bool main) {
	glColor3f(1, 1, 1);
	GLUquadric *quad = gluNewQuadric();
	if (main) {
		// base
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(40, 20, 10); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, towertaj);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 6, 6, 3, 200, 200);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		
		// second base
		glPushMatrix(); {
			glTranslatef(0, 0, 3);
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(40, 20, 10); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, towertaj);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 6, 6, 2, 200, 200);
				glMatrixMode(GL_TEXTURE);
			} glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
		}
		glPopMatrix();
		// third base angular white
		glPushMatrix(); {
			glTranslatef(0, 0, 5);
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(40, 1, 1); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, dome_tex);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 6, 6.8, 1.5, 200, 200);
				glMatrixMode(GL_TEXTURE);
			} glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
		}
		glPopMatrix();

	}
	// fourth base, angular gray
	glPushMatrix(); {
		glTranslatef(0, 0, 6.5);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(40, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, white_rect);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 6.8, 7, .5, 200, 200);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		
	}
	glPopMatrix();
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
					glEnable(GL_TEXTURE_2D);
					glMatrixMode(GL_TEXTURE);
					glPushMatrix(); {
						glScalef(40, 20, 10); // This scaling controls the number of texture repetitions 
						glBindTexture(GL_TEXTURE_2D, white_rect);
						gluQuadricNormals(quad, GLU_SMOOTH);
						gluQuadricTexture(quad, GLU_TRUE);
						glMatrixMode(GL_MODELVIEW);
						gluSphere(quad, 7, 200, 200);
						glMatrixMode(GL_TEXTURE);
					} glPopMatrix();
					glDisable(GL_TEXTURE_2D);
					glMatrixMode(GL_MODELVIEW);
					
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

// done
void secondTaj() {
	double y = 0, front = 1;
	if (front == -1) y = 20;
	// side gate
	// blue base extended
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(11, y + 0, 0);
		glTexCoord2f(1, 0); glVertex3f(13, y + 0, 0);
		glTexCoord2f(1, 1); glVertex3f(13, y + 0, 1.3);
		glTexCoord2f(0, 1); glVertex3f(11, y + 0, 1.3);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, taj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(11, y + 0, 9);
	glTexCoord2f(5, 0); glVertex3f(21, y + 0, 9);
	glTexCoord2f(5, 5); glVertex3f(21, y + 0, 18);
	glTexCoord2f(0, 5); glVertex3f(11, y + 0, 18);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, taj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(11, y + 0, 9);
	glTexCoord2f(5, 0); glVertex3f(13, y + 0, 9); 
	glTexCoord2f(5, 5); glVertex3f(13, y + 0, 1.3);
	glTexCoord2f(0, 5); glVertex3f(11, y + 0, 1.3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, taj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(19, y + 0, 9);
	glTexCoord2f(5, 0); glVertex3f(21, y + 0, 9);
	glTexCoord2f(5, 5); glVertex3f(21, y + 0, 1.3);
	glTexCoord2f(0, 5); glVertex3f(19, y + 0, 1.3);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, taj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(19, y + 0, 0);
	glTexCoord2f(5, 0); glVertex3f(21, y + 0, 0);
	glTexCoord2f(5, 5); glVertex3f(21, y + 0, 1.3);
	glTexCoord2f(0, 5);  glVertex3f(19, y + 0, 1.3); 
	glEnd();
	glDisable(GL_TEXTURE_2D);


	}
	// second cylinder
	glPushMatrix(); {
		glTranslatef(21, y + 0, 0);
		GLUquadric *quad;
		quad = gluNewQuadric();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, smallwall_top); // here texid corresponds a bitmap image.
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluQuadricTexture(quad, GLU_TRUE);
		gluCylinder(quad, .3, .3, 21, 20, 20);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix(); {
			glTranslatef(0, 0, 21);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, border); // here texid corresponds a bitmap image.
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, .4, .5, 1, 20, 20);
			glDisable(GL_TEXTURE_2D);

			glPushMatrix(); {
				glTranslatef(0, 0, 1);
				glScalef(.05, .05, .05);
				dome(false);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); {
			for (int i = 0; i < 3; i++) {
				glTranslatef(0, 0, 5);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, border); // here texid corresponds a bitmap image.
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);
				gluCylinder(quad, .4, .4, 1, 20, 20);
				glDisable(GL_TEXTURE_2D);

			}
		}
		glPopMatrix();

	}
	glPopMatrix();
	// second part border 
	// inner square
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(12.5, y - 0.2 * front, 10);
			glTexCoord2f(1, 0); glVertex3f(12.5, y - 0.2 * front, 15);
			glTexCoord2f(1, 1); glVertex3f(13, y - 0.2 * front, 15);
			glTexCoord2f(0, 1); glVertex3f(13, y - 0.2 * front, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(19, y - 0.2 * front, 10);
			glTexCoord2f(1, 0); glVertex3f(19, y - 0.2 * front, 15);
			glTexCoord2f(1, 1); glVertex3f(19.5, y - 0.2 * front, 15);
			glTexCoord2f(0, 1); glVertex3f(19.5, y - 0.2 * front, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y - 0.2 * front, 14.5);
			glTexCoord2f(1, 0); glVertex3f(19, y - 0.2 * front, 14.5);
			glTexCoord2f(1, 1); glVertex3f(19, y - 0.2 * front, 15);
			glTexCoord2f(0, 1); glVertex3f(13, y - 0.2 * front, 15);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y - 0.2 * front, 10.5);
			glTexCoord2f(1, 0); glVertex3f(19, y - 0.2 * front, 10.5);
			glTexCoord2f(1, 1); glVertex3f(19, y - 0.2 * front, 10);
			glTexCoord2f(0, 1); glVertex3f(13, y - 0.2 * front, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);



	// big border

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y - 0.2 * front, 1.3);
			glTexCoord2f(1, 0); glVertex3f(11, y - 0.2 * front, 16);
			glTexCoord2f(1, 1); glVertex3f(11.5, y - 0.2 * front, 16);
			glTexCoord2f(0, 1); glVertex3f(11.5, y - 0.2 * front, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(20.8, y - 0.2 * front, 1.3);
			glTexCoord2f(1, 0); glVertex3f(20.8, y - 0.2 * front, 16);
			glTexCoord2f(1, 1); glVertex3f(20.3, y - 0.2 * front, 16);
			glTexCoord2f(0, 1); glVertex3f(20.3, y - 0.2 * front, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(20.3, y - 0.2 * front, 15.5);
			glTexCoord2f(1, 0); glVertex3f(11.5, y - 0.2 * front, 15.5);
			glTexCoord2f(1, 1); glVertex3f(11.5, y - 0.2 * front, 16);
			glTexCoord2f(0, 1); glVertex3f(20.3, y - 0.2 * front, 16);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y - 0.2 * front, 1.3);
			glTexCoord2f(1, 0); glVertex3f(13, y - 0.2 * front, 9.5);
			glTexCoord2f(1, 1); glVertex3f(12.5, y - 0.2 * front, 9.5);
			glTexCoord2f(0, 1); glVertex3f(12.5, y - 0.2 * front, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(19, y - 0.2 * front, 1.3);
			glTexCoord2f(1, 0); glVertex3f(19, y - 0.2 * front, 9.5);
			glTexCoord2f(1, 1); glVertex3f(19.5, y - 0.2 * front, 9.5);
			glTexCoord2f(0, 1); glVertex3f(19.5, y - 0.2 * front, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y - 0.2 * front, 9);
			glTexCoord2f(1, 0); glVertex3f(19, y - 0.2 * front, 9);
			glTexCoord2f(1, 1); glVertex3f(19, y - 0.2 * front, 9.5);
			glTexCoord2f(0, 1); glVertex3f(13, y - 0.2 * front, 9.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// chamber
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber_side);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(13, y + 3 * front, 0);
			glTexCoord2f(1, 1); glVertex3f(13, y + 3 * front, 10);
			glTexCoord2f(0, 1); glVertex3f(13, y + 0, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber_side);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(19, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(19, y + 3 * front, 0);
			glTexCoord2f(1, 1); glVertex3f(19, y + 3 * front, 10);
			glTexCoord2f(0, 1); glVertex3f(19, y + 0, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y + 3 * front, 0);
			glTexCoord2f(1, 0); glVertex3f(19, y + 3 * front, 0);
			glTexCoord2f(1, 1); glVertex3f(19, y + 3 * front, 10);
			glTexCoord2f(0, 1); glVertex3f(13, y + 3 * front, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// chamber top curve
	if (front == 1) {
		glPushMatrix(); {
			glTranslatef(16, 0.5, 5);
			glScalef(0.3, 0.6, 0.3);
			gateTopSym();
		}
		glPopMatrix();
	}
	else {
		glPushMatrix(); {
			glTranslatef(16, 20.7, 5);
			glScalef(0.3, 0.6, 0.3);
			gateTopSym();
		}
		glPopMatrix();
	}


	// upper white jinish
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_jinish);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(15, y - 0.1*front, 10.5);
			glTexCoord2f(1, 0); glVertex3f(17, y - 0.1*front, 10.5);
			glTexCoord2f(1, 1); glVertex3f(17, y - 0.1*front, 14);
			glTexCoord2f(0, 1); glVertex3f(15, y - 0.1*front, 14);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// top blue part
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(21, y + 0, 18);
			glTexCoord2f(1, 1); glVertex3f(21, y + 0, 19);
			glTexCoord2f(0, 1); glVertex3f(11, y + 0, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 1, 18);
			glTexCoord2f(1, 0); glVertex3f(21, y + 1, 18);
			glTexCoord2f(1, 1); glVertex3f(21, y + 1, 19);
			glTexCoord2f(0, 1); glVertex3f(11, y + 1, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(21, y + 1, 18);
			glTexCoord2f(1, 1); glVertex3f(21, y + 1, 19);
			glTexCoord2f(0, 1); glVertex3f(21, y + 0, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(11, y + 1, 18);
			glTexCoord2f(1, 1); glVertex3f(11, y + 1, 19);
			glTexCoord2f(0, 1); glVertex3f(11, y + 0, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	// top red
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 1.2, 19);
			glTexCoord2f(1, 0); glVertex3f(21, y + 1.2, 19);
			glTexCoord2f(1, 1); glVertex3f(21, y - 0.2, 19);
			glTexCoord2f(0, 1); glVertex3f(11, y - 0.2, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 1.2, 18);
			glTexCoord2f(1, 0); glVertex3f(11, y + 1.2, 18);
			glTexCoord2f(1, 1); glVertex3f(11, y - 0.2, 18);
			glTexCoord2f(0, 1); glVertex3f(21, y - 0.2, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

// done
void sentryTaj() {
	GLUquadric *quad = gluNewQuadric();
	// columns
	for (int i = 0; i < 6; i++) {
		double theta = (2 * 3.1416 / 6) * i;
		double r = 6;
		glPushMatrix(); {
			glTranslatef(r*sin(theta), r*cos(theta), 0);
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, basetaj);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 0.5, 0.5, 10, 4, 100);
				glMatrixMode(GL_TEXTURE);
			} glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
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
		glTranslatef(0, 0, 10);
		gluCylinder(quad, 9, 4, 1, 8, 100);
		// dome
		glPushMatrix(); {
			glTranslatef(0, 0, -6);
			//glScalef(0.6, 0.6, 0.6);
			dome(false);
		}
		glPopMatrix();
	}
	glPopMatrix();
	for (double i = 0; i < 0.5; i += 0.1) {
		glPushMatrix(); {
			glTranslatef(0, 0, 10.2); 
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, towertaj);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 4 - i, 4 - i, 0.5, 8, 100);
				glMatrixMode(GL_TEXTURE);
			} glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
		}
		glPopMatrix();

	}
}

// done
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
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_jinish);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(-1, 5, 10.5);
			glTexCoord2f(1, 0); glVertex3f(1, 5, 10.5);
			glTexCoord2f(1, 1); glVertex3f(1, 5, 14);
			glTexCoord2f(0, 1); glVertex3f(-1, 5, 14);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_jinish);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(-1.5, 5, 0);
			glTexCoord2f(1, 0); glVertex3f(1.5, 5, 0);
			glTexCoord2f(1, 1); glVertex3f(1.5, 5, 5); 
			glTexCoord2f(0, 1);  glVertex3f(-1.5, 5, 5); 
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(5, 5, 0);
			glTexCoord2f(1, 0); glVertex3f(4.5, 5, 0);
			glTexCoord2f(1, 1); glVertex3f(4.5, 5, 10);
			glTexCoord2f(0, 1); glVertex3f(5, 5, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(5, 5, 9.5);
			glTexCoord2f(1, 0); glVertex3f(-1, 5, 9.5);
			glTexCoord2f(1, 1); glVertex3f(-1, 5, 10);
			glTexCoord2f(0, 1);
			glVertex3f(5, 5, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

// done
void towerTaj() {
	GLUquadric *quad;
	quad = gluNewQuadric();
	double ang = 3.1412 / 4;
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(50, -50, -6);
	// base
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix(); {
		glScalef(8, 1, 1); // This scaling controls the number of texture repetitions 
		glBindTexture(GL_TEXTURE_2D, basetaj);
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluQuadricTexture(quad, GLU_TRUE);
		glMatrixMode(GL_MODELVIEW);
		gluCylinder(quad, 4, 4, 7, 8, 30);
		glMatrixMode(GL_TEXTURE);
	} glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	
	// tower
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix(); {
		glScalef(10, 10, 5); // This scaling controls the number of texture repetitions 
		glBindTexture(GL_TEXTURE_2D, towertaj);
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluQuadricTexture(quad, GLU_TRUE);
		glMatrixMode(GL_MODELVIEW);
		gluCylinder(quad, 3, 2, 50, 30, 30);
		glMatrixMode(GL_TEXTURE);
	} glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(50, -50, 0.01);//top octa
	glBegin(GL_QUADS);
	for (int k = 0; k <= 8; k++) {
		for (int a = 0, j = a + k; a <= 3; a++, j++){
			glVertex3f(4 * cos(j*ang), 4 * sin(j*ang), 0);
		}
		glEnd();
	}
	

	glPushMatrix();
	glTranslatef(0, 0, 40);
	glScalef(0.5, 0.5, 1);
	sentryRoom1(0);
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

// done
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

// done
void baseTaj() {
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floortaj);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(50, -50, -0.01);
	glTexCoord2f(20, 0); glVertex3f(50, 50, -0.01);
	glTexCoord2f(20, 20); glVertex3f(-50, 50, -0.01);
	glTexCoord2f(0, 20); glVertex3f(-50, -50, -0.01);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i <= 3; i++) //sides
	{
		glPushMatrix();
		glRotatef(90 * i, 0, 0, 1);
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, basetaj);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(50, 50, -4);
		glTexCoord2f(20, 0); glVertex3f(-50, 50, -4);
		glTexCoord2f(20, 1); glVertex3f(-50, 50, 0); 
		glTexCoord2f(0, 1); glVertex3f(50, 50, 0); 
		glEnd();
		glDisable(GL_TEXTURE_2D);
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
