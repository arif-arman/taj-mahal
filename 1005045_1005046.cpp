#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<windows.h>
#include<GL/glut.h>
#include "gate.h"
#include "taj.h"
using namespace std;

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX - camX, upY - camY, upZ - camZ);

	glMatrixMode(GL_MODELVIEW);

	//some gridlines along the field
	
	glPushMatrix();
	glTranslatef(0, 0, 4);
	makeTaj();
	//baseTaj();
	glPopMatrix();
	
	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
	//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	
	//NOTE: the camera still CONSTANTLY looks at the center


	//again select MODEL-VIEW


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	//drawGate();
	
	

	/*	//FORGET THE FIELD
	//an square field
	glColor3f(0.4, 1, 0.4);
	glBegin(GL_QUADS);{
	glVertex3f(-100,-100,0);
	glVertex3f(100,-100,0);
	glVertex3f(100,100,0);
	glVertex3f(-100,100,0);
	}glEnd();
	*/

	//some gridlines along the field
	int i;

	glColor3f(0.3, 0.3, 0.3);	//grey
	glBegin(GL_LINES); {
		for (i = -10; i <= 10; i++){

			if (i == 0)
				continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i * 10, -100, 0);
			glVertex3f(i * 10, 100, 0);

			//lines parallel to X-axis
			glVertex3f(-100, i * 10, 0);
			glVertex3f(100, i * 10, 0);
		}
	}glEnd();

	// draw the two AXES
	//100% white
	glBegin(GL_LINES); {
		//Y axis
		glColor3f(0, 0, 1);
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0, 150, 0);

		//X axis
		glColor3f(0, 1, 0);

		glVertex3f(-150, 0, 0);
		glVertex3f(150, 0, 0);
	}glEnd();


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Camera
	rectAngle -= 1;
	//cameraAngle += 0.002;	// camera will rotate at 0.002 radians per frame.

	//codes for any changes in Models

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void init(){
	//codes for initialization
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;
	chandelierAngle = 0;

	gateLoadBMP();

	//clear the screen
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70, 1, 0.1, 10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}


void keyboardListener(unsigned char key, int x, int y){
	switch (key){
		double a, b, c, d, x1, y1, z1, si, co;

	case '1': // look left
		d = sqrt((upX - camX)*(upX - camX) + (upY - camY)*(upY - camY) + (upZ - camZ)*(upZ - camZ));
		a = (upX - camX) / d;
		b = (upY - camY) / d;
		c = (upZ - camZ) / d;
		si = sin(lookA);
		co = cos(lookA);
		x1 = (a*a*(1 - co) + co)*(lookX - camX) + (b*a*(1 - co) - c*si)*(lookY - camY) + (a*c*(1 - co) + b*si)*(lookZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lookX - camX) + (b*b*(1 - co) + co)*(lookY - camY) + (b*c*(1 - co) - a*si)*(lookZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lookX - camX) + (b*c*(1 - co) + a*si)*(lookY - camY) + (c*c*(1 - co) + co)*(lookZ - camZ);
		lookX = x1 + camX;
		lookY = y1 + camY;
		lookZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(lrX - camX) + (b*a*(1 - co) - c*si)*(lrY - camY) + (a*c*(1 - co) + b*si)*(lrZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lrX - camX) + (b*b*(1 - co) + co)*(lrY - camY) + (b*c*(1 - co) - a*si)*(lrZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lrX - camX) + (b*c*(1 - co) + a*si)*(lrY - camY) + (c*c*(1 - co) + co)*(lrZ - camZ);
		lrX = x1 + camX;
		lrY = y1 + camY;
		lrZ = z1 + camZ;

		break;

	case '2': // look right
		d = sqrt((upX - camX)*(upX - camX) + (upY - camY)*(upY - camY) + (upZ - camZ)*(upZ - camZ));
		a = (upX - camX) / d;
		b = (upY - camY) / d;
		c = (upZ - camZ) / d;
		si = sin(-lookA);
		co = cos(-lookA);
		x1 = (a*a*(1 - co) + co)*(lookX - camX) + (b*a*(1 - co) - c*si)*(lookY - camY) + (a*c*(1 - co) + b*si)*(lookZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lookX - camX) + (b*b*(1 - co) + co)*(lookY - camY) + (b*c*(1 - co) - a*si)*(lookZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lookX - camX) + (b*c*(1 - co) + a*si)*(lookY - camY) + (c*c*(1 - co) + co)*(lookZ - camZ);
		lookX = x1 + camX;
		lookY = y1 + camY;
		lookZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(lrX - camX) + (b*a*(1 - co) - c*si)*(lrY - camY) + (a*c*(1 - co) + b*si)*(lrZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lrX - camX) + (b*b*(1 - co) + co)*(lrY - camY) + (b*c*(1 - co) - a*si)*(lrZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lrX - camX) + (b*c*(1 - co) + a*si)*(lrY - camY) + (c*c*(1 - co) + co)*(lrZ - camZ);
		lrX = x1 + camX;
		lrY = y1 + camY;
		lrZ = z1 + camZ;

		break;

	case '3': // pitch down
		d = sqrt((lrX - camX)*(lrX - camX) + (lrY - camY)*(lrY - camY) + (lrZ - camZ)*(lrZ - camZ));
		a = (lrX - camX) / d;
		b = (lrY - camY) / d;
		c = (lrZ - camZ) / d;
		si = sin(upA);
		co = cos(upA);
		x1 = (a*a*(1 - co) + co)*(lookX - camX) + (b*a*(1 - co) - c*si)*(lookY - camY) + (a*c*(1 - co) + b*si)*(lookZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lookX - camX) + (b*b*(1 - co) + co)*(lookY - camY) + (b*c*(1 - co) - a*si)*(lookZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lookX - camX) + (b*c*(1 - co) + a*si)*(lookY - camY) + (c*c*(1 - co) + co)*(lookZ - camZ);
		lookX = x1 + camX;
		lookY = y1 + camY;
		lookZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(upX - camX) + (b*a*(1 - co) - c*si)*(upY - camY) + (a*c*(1 - co) + b*si)*(upZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(upX - camX) + (b*b*(1 - co) + co)*(upY - camY) + (b*c*(1 - co) - a*si)*(upZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(upX - camX) + (b*c*(1 - co) + a*si)*(upY - camY) + (c*c*(1 - co) + co)*(upZ - camZ);
		upX = x1 + camX;
		upY = y1 + camY;
		upZ = z1 + camZ;

		break;

	case '4': // pitch up
		d = sqrt((lrX - camX)*(lrX - camX) + (lrY - camY)*(lrY - camY) + (lrZ - camZ)*(lrZ - camZ));
		a = (lrX - camX) / d;
		b = (lrY - camY) / d;
		c = (lrZ - camZ) / d;
		si = sin(-upA);
		co = cos(-upA);
		x1 = (a*a*(1 - co) + co)*(lookX - camX) + (b*a*(1 - co) - c*si)*(lookY - camY) + (a*c*(1 - co) + b*si)*(lookZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lookX - camX) + (b*b*(1 - co) + co)*(lookY - camY) + (b*c*(1 - co) - a*si)*(lookZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lookX - camX) + (b*c*(1 - co) + a*si)*(lookY - camY) + (c*c*(1 - co) + co)*(lookZ - camZ);
		lookX = x1 + camX;
		lookY = y1 + camY;
		lookZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(upX - camX) + (b*a*(1 - co) - c*si)*(upY - camY) + (a*c*(1 - co) + b*si)*(upZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(upX - camX) + (b*b*(1 - co) + co)*(upY - camY) + (b*c*(1 - co) - a*si)*(upZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(upX - camX) + (b*c*(1 - co) + a*si)*(upY - camY) + (c*c*(1 - co) + co)*(upZ - camZ);
		upX = x1 + camX;
		upY = y1 + camY;
		upZ = z1 + camZ;

		break;


	case '6':   //roll left
		d = sqrt((lookX - camX)*(lookX - camX) + (lookY - camY)*(lookY - camY) + (lookZ - camZ)*(lookZ - camZ));
		a = (lookX - camX) / d;
		b = (lookY - camY) / d;
		c = (lookZ - camZ) / d;
		si = sin(-lrA);
		co = cos(-lrA);

		x1 = (a*a*(1 - co) + co)*(lrX - camX) + (b*a*(1 - co) - c*si)*(lrY - camY) + (a*c*(1 - co) + b*si)*(lrZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lrX - camX) + (b*b*(1 - co) + co)*(lrY - camY) + (b*c*(1 - co) - a*si)*(lrZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lrX - camX) + (b*c*(1 - co) + a*si)*(lrY - camY) + (c*c*(1 - co) + co)*(lrZ - camZ);
		lrX = x1 + camX;
		lrY = y1 + camY;
		lrZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(upX - camX) + (b*a*(1 - co) - c*si)*(upY - camY) + (a*c*(1 - co) + b*si)*(upZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(upX - camX) + (b*b*(1 - co) + co)*(upY - camY) + (b*c*(1 - co) - a*si)*(upZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(upX - camX) + (b*c*(1 - co) + a*si)*(upY - camY) + (c*c*(1 - co) + co)*(upZ - camZ);
		upX = x1 + camX;
		upY = y1 + camY;
		upZ = z1 + camZ;

		break;


	case '5':   //roll right
		d = sqrt((lookX - camX)*(lookX - camX) + (lookY - camY)*(lookY - camY) + (lookZ - camZ)*(lookZ - camZ));
		a = (lookX - camX) / d;
		b = (lookY - camY) / d;
		c = (lookZ - camZ) / d;
		si = sin(lrA);
		co = cos(lrA);

		x1 = (a*a*(1 - co) + co)*(lrX - camX) + (b*a*(1 - co) - c*si)*(lrY - camY) + (a*c*(1 - co) + b*si)*(lrZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(lrX - camX) + (b*b*(1 - co) + co)*(lrY - camY) + (b*c*(1 - co) - a*si)*(lrZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(lrX - camX) + (b*c*(1 - co) + a*si)*(lrY - camY) + (c*c*(1 - co) + co)*(lrZ - camZ);
		lrX = x1 + camX;
		lrY = y1 + camY;
		lrZ = z1 + camZ;

		x1 = (a*a*(1 - co) + co)*(upX - camX) + (b*a*(1 - co) - c*si)*(upY - camY) + (a*c*(1 - co) + b*si)*(upZ - camZ);
		y1 = (b*a*(1 - co) + c*si)*(upX - camX) + (b*b*(1 - co) + co)*(upY - camY) + (b*c*(1 - co) - a*si)*(upZ - camZ);
		z1 = (c*a*(1 - co) - b*si)*(upX - camX) + (b*c*(1 - co) + a*si)*(upY - camY) + (c*c*(1 - co) + co)*(upZ - camZ);
		upX = x1 + camX;
		upY = y1 + camY;
		upZ = z1 + camZ;

		break;

	case '7':   //reset camera
		camX = 0, camY = 0, camZ = 0;
		lookX = 100, lookY = 0, lookZ = 0;
		upX = 0, upY = 0, upZ = 100;
		lrX = 0, lrY = 100, lrZ = 0;
		lookA = 0.1, upA = 0.1, lrA = 0.1;
		lookM = 4, upM = 4, lrM = 4;

		break;


	case 27:	//ESCAPE KEY -- simply exit
		exit(0);
		break;

	default:
		break;
	}
}

void specialKeyListener(int key, int x, int y){
	switch (key){
		double a, b, c, d;
	case GLUT_KEY_DOWN:		//backward
		d = sqrt((lookX - camX)*(lookX - camX) + (lookY - camY)*(lookY - camY) + (lookZ - camZ)*(lookZ - camZ));
		a = (lookX - camX) / d*-lookM;
		b = (lookY - camY) / d*-lookM;
		c = (lookZ - camZ) / d*-lookM;
		increase(a, b, c);

		break;

	case GLUT_KEY_UP:		//forward
		d = sqrt((lookX - camX)*(lookX - camX) + (lookY - camY)*(lookY - camY) + (lookZ - camZ)*(lookZ - camZ));
		a = (lookX - camX) / d*lookM;
		b = (lookY - camY) / d*lookM;
		c = (lookZ - camZ) / d*lookM;
		increase(a, b, c);

		break;



	case GLUT_KEY_RIGHT: //strafe right
		d = sqrt((lrX - camX)*(lrX - camX) + (lrY - camY)*(lrY - camY) + (lrZ - camZ)*(lrZ - camZ));
		a = (lrX - camX) / d*-lrM;
		b = (lrY - camY) / d*-lrM;
		c = (lrZ - camZ) / d*-lrM;
		increase(a, b, c);
		break;

	case GLUT_KEY_LEFT: //strafe left
		d = sqrt((lrX - camX)*(lrX - camX) + (lrY - camY)*(lrY - camY) + (lrZ - camZ)*(lrZ - camZ));
		a = (lrX - camX) / d*lrM;
		b = (lrY - camY) / d*lrM;
		c = (lrZ - camZ) / d*lrM;
		increase(a, b, c);
		break;



	case GLUT_KEY_PAGE_UP: //fly up
		d = sqrt((upX - camX)*(upX - camX) + (upY - camY)*(upY - camY) + (upZ - camZ)*(upZ - camZ));
		a = (upX - camX) / d*upM;
		b = (upY - camY) / d*upM;
		c = (upZ - camZ) / d*upM;
		increase(a, b, c);
		break;
	case GLUT_KEY_PAGE_DOWN: //fly down
		d = sqrt((upX - camX)*(upX - camX) + (upY - camY)*(upY - camY) + (upZ - camZ)*(upZ - camZ));
		a = (upX - camX) / d*-upM;
		b = (upY - camY) / d*-upM;
		c = (upZ - camZ) / d*-upM;
		increase(a, b, c);
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			cameraAngleDelta = -cameraAngleDelta;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA);	//Depth, Double buffer, RGB color

	glutCreateWindow("Graphics Offline02");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing


	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}