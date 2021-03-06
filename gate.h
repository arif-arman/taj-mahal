#include<GL/glut.h>
#include<iostream>
using namespace std;
#include<math.h>
#include "texture.h"

GLuint basewall, smallwall, smallwall_top, border, thirdpart, chamber, chamber_side, white_jinish, white_rect, dome_tex, back_tower, back_tower_base, base_tex;
GLuint basetaj, floortaj, towertaj, taj;
void gateLoadBMP() {
	basewall = LoadBitmap("img/basewall.bmp");
	smallwall = LoadBitmap("img/smallwall.bmp");
	smallwall_top = LoadBitmap("img/smallwall_top.bmp");
	border = LoadBitmap("img/border.bmp");
	thirdpart = LoadBitmap("img/thirdpart.bmp");
	chamber = LoadBitmap("img/chamber.bmp");
	chamber_side = LoadBitmap("img/chamber_side.bmp");
	white_jinish = LoadBitmap("img/white_jinish.bmp");
	white_rect = LoadBitmap("img/white_rect.bmp");
	dome_tex = LoadBitmap("img/dome.bmp");
	back_tower = LoadBitmap("img/back_tower.bmp");
	back_tower_base = LoadBitmap("img/back_tower_base.bmp");
	base_tex = LoadBitmap("img/base.bmp");
	basetaj = LoadBitmap("img/taj_base.bmp");
	floortaj = LoadBitmap("img/taj_floor.bmp");
	towertaj = LoadBitmap("img/taj_tower.bmp");
	taj = LoadBitmap("img/taj.bmp");
}

void gateTop() {
	//glScalef(3, 2, 1);
	glPushMatrix(); {
		glRotatef(90, 1, 0, 0);
		double equ[4];
		equ[0] = 1; equ[1] = 0; equ[2] = 0; equ[3] = 0;
		glClipPlane(GL_CLIP_PLANE0, equ);
		glEnable(GL_CLIP_PLANE0); {

			equ[0] = 0; equ[1] = 1; equ[2] = 0; equ[3] = 0;
			glClipPlane(GL_CLIP_PLANE1, equ);
			glEnable(GL_CLIP_PLANE1); {
				equ[0] = 0; equ[1] = -1; equ[2] = 0; equ[3] = 15;
				glClipPlane(GL_CLIP_PLANE2, equ);
				glEnable(GL_CLIP_PLANE2); {
					equ[0] = -1; equ[1] = 0; equ[2] = 0; equ[3] = 10;
					glClipPlane(GL_CLIP_PLANE3, equ);
					glEnable(GL_CLIP_PLANE3); {
						glBegin(GL_QUADS); {
							glVertex3f(0, 10, 1);
							glVertex3f(0, 20, 1);
							glVertex3f(15, 20, 1);
							glVertex3f(15, 10, 1);
						}
						glEnd();
						double delta = 2 * 3.1416 / 200;
						double theta = 0;
						for (double i = 0; i < 200; i++) {
							double theta2 = theta + delta;
							double x1 = 10 * cos(theta);
							double y1 = 10 * sin(theta);
							double x2 = 10 * cos(theta2);
							double y2 = 10 * sin(theta2);
							if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0) {
								glBegin(GL_QUADS); {
									glVertex3f(x1, y1, 1);
									glVertex3f(x2, y2, 1);
									glVertex3f(x2 + 20, y2 + 2, 1);
									glVertex3f(x1 + 20, y2 - 2, 1);
								}
								glEnd();

							}
							theta = theta2;
							//gluCylinder(quad, r, r, 5, 100, 100);
						}
						
					}
					glDisable(GL_CLIP_PLANE3);

				}
				glDisable(GL_CLIP_PLANE2);

			}
			glDisable(GL_CLIP_PLANE1);
		}
		glDisable(GL_CLIP_PLANE0);
		
	}
	glPopMatrix();
	
}

void gateTopSym() {
	glPushMatrix(); {
		gateTop();
	}
	glPopMatrix();
	
	glPushMatrix(); {
		glScalef(-1, 1, 1);
		gateTop();
	}
	glPopMatrix();
}

// done
void domeTop() {
	GLUquadric *quad = gluNewQuadric();
	// base
	glColor3f(0.3, 0.3, 0.3);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_TEXTURE);
	glPushMatrix(); {
		glScalef(40, 1, 1); // This scaling controls the number of texture repetitions 
		glBindTexture(GL_TEXTURE_2D, white_rect);
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluQuadricTexture(quad, GLU_TRUE);

		glMatrixMode(GL_MODELVIEW);
		gluCylinder(quad, 6, 2, 3, 20, 20);
		glMatrixMode(GL_TEXTURE);
	} glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 1, 0);
	// first cylinder
	glPushMatrix(); {
		glTranslatef(0, 0, 3);
		gluCylinder(quad, 2, 1, 1, 20, 20);
	}
	glPopMatrix();
	// first golla
	glPushMatrix(); {
		glTranslatef(0, 0, 5);
		gluSphere(quad, 1.5, 200, 200);

	}
	glPopMatrix();
	// second golla, cut
	glPushMatrix(); {
		glTranslatef(0, 0, 8.5);
		double equ[4];
		equ[0] = 0; equ[1] = 0; equ[2] = -1; equ[3] = 1.5;
		glClipPlane(GL_CLIP_PLANE0, equ);
		glEnable(GL_CLIP_PLANE0); {
			gluSphere(quad, 2, 200, 200);
		}
		glDisable(GL_CLIP_PLANE0);

	}
	glPopMatrix();
	// second cylinder
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		gluCylinder(quad, 1.3, 0.3, 2, 200, 200);

	}
	glPopMatrix();
	// flat cylinder
	glPushMatrix(); {
		glTranslatef(0, 0, 12);
		gluCylinder(quad, 0.7, 0.7, 0.3, 200, 200);

	}
	glPopMatrix();
	// third golla
	glPushMatrix(); {
		glTranslatef(0, 0, 13.3);
		double equ[4];
		equ[0] = 0; equ[1] = 0; equ[2] = -1; equ[3] = 0.9;
		glClipPlane(GL_CLIP_PLANE0, equ);
		glEnable(GL_CLIP_PLANE0); {
			gluSphere(quad, 1, 200, 200);
		}
		glDisable(GL_CLIP_PLANE0);
	}
	glPopMatrix();
	// third cylinder
	glPushMatrix(); {
		glTranslatef(0, 0, 14.1);
		gluCylinder(quad, 0.3, 0.1, 2, 200, 200);

	}
	glPopMatrix();
	// final choto golla
	glPushMatrix(); {
		glTranslatef(0, 0, 16.5);
		gluSphere(quad, 0.5, 200, 200);
	}
	glPopMatrix();
	// final chokhkha cylinder
	glPushMatrix(); {
		glTranslatef(0, 0, 17);
		gluCylinder(quad, 0.2, 0.1, 1.5, 200, 200);

	}
	glPopMatrix();

}

// done
void dome(bool main) {
	glColor3f(1, 1, 1);
	GLUquadric *quad = gluNewQuadric();
	if (main) {
		// base
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(40, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, thirdpart);
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
				glScalef(40, 1, 1); // This scaling controls the number of texture repetitions 
				glBindTexture(GL_TEXTURE_2D, dome_tex);
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
				glBindTexture(GL_TEXTURE_2D, white_rect);
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
		glColor3f(0.7, 0.7, 0.7);
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
	glColor3f(1, 1, 1);
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
						glScalef(40, 40, 20); // This scaling controls the number of texture repetitions 
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
		glScalef(0.5, 0.5, 0.5);
		domeTop();
	}
	glPopMatrix();



}

// done
void firstPart(double front) {
	glColor3f(1, 1, 1);
	double y = 0;
	if (front == -1) y = 20;
	// inner part
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 6 * front, 0);
			glTexCoord2f(1, 0); glVertex3f(6.5, y + 6 * front, 0); 
			glTexCoord2f(1, 1); glVertex3f(6.5, y + 6 * front, 18);
			glTexCoord2f(0, 1); glVertex3f(0, y + 6 * front, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber_side);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(6.5, y + 0 * front, 0);
			glTexCoord2f(1, 0); glVertex3f(6.5, y + 6 * front, 0);
			glTexCoord2f(1, 1); glVertex3f(6.5, y + 6 * front, 18);
			glTexCoord2f(0, 1); glVertex3f(6.5, y + 0 * front, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// base
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 0 * front, 0);
			glTexCoord2f(1, 0); glVertex3f(0, y + 6 * front, 0);
			glTexCoord2f(1, 1); glVertex3f(6.5, y + 6 * front, 0);
			glTexCoord2f(0, 1); glVertex3f(6.5, y + 0 * front, 0);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// inner part curvy
	glColor3f(1, 1, 1);
	if (front == 1){
		glPushMatrix(); {
			glTranslatef(0, 1, 10);
			glScalef(.65, 1, .5);
			gateTop();
		}
		glPopMatrix();
	}
	else {
		glPushMatrix(); {
			glTranslatef(0, 21, 10);
			glScalef(.65, 1, .5);
			gateTop();
		}
		glPopMatrix();
	}
	
	// border of gate
	for (double i = 0; i >= -0.5; i -= 0.1) {
		double j = y + i*front;
		// top
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(0, j, 17);
				glTexCoord2f(1, 0); glVertex3f(7.9, j, 17); 
				glTexCoord2f(1, 1); glVertex3f(7.9, j, 18);
				glTexCoord2f(0, 1); glVertex3f(0, j, 18);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(6.7, j, 17);
				glTexCoord2f(1, 0); glVertex3f(6.7, j, 1.3); 
				glTexCoord2f(1, 1); glVertex3f(7.9, j, 1.3);
				glTexCoord2f(0, 1); glVertex3f(7.9, j, 18);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(6.7, j, 2.3);
				glTexCoord2f(1, 0); glVertex3f(10.5, j, 2.3);
				glTexCoord2f(1, 1); glVertex3f(10.5, j, 1.3);
				glTexCoord2f(0, 1); glVertex3f(6.7, j, 1.3);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(9.8, j, 2.3);
				glTexCoord2f(1, 0); glVertex3f(9.8, j, 21.0); 
				glTexCoord2f(1, 1); glVertex3f(10.5, j, 21.0);
				glTexCoord2f(0, 1); glVertex3f(10.5, j, 2.3);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(0, j, 20.3);
				glTexCoord2f(1, 0); glVertex3f(10.5, j, 20.3);
				glTexCoord2f(1, 1); glVertex3f(10.5, j, 21.0);
				glTexCoord2f(0, 1); glVertex3f(0, j, 21.0);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
	// blue base
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(10.5, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(6.7, y + 0, 0);
			glTexCoord2f(1, 1); glVertex3f(6.7, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(10.5, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// inner white rectangles
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_rect);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(7.9, y + 0, 2.3);
			glTexCoord2f(1, 0); glVertex3f(7.9, y + 0, 20.3);
			glTexCoord2f(1, 1); glVertex3f(9.8, y + 0, 20.3);
			glTexCoord2f(0, 1); glVertex3f(9.8, y + 0, 2.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_rect);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(9.8, y + 0, 18); 
			glTexCoord2f(1, 1); glVertex3f(9.8, y + 0, 20.3);
			glTexCoord2f(0, 1); glVertex3f(0, y + 0, 20.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	// top of gate
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 0, 21);
			glTexCoord2f(1, 0); glVertex3f(10.5, y + 0, 21);
			glTexCoord2f(1, 1); glVertex3f(10.5, y + 0, 22);
			glTexCoord2f(0, 1); glVertex3f(0, y + 0, 22);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 2, 21);
			glTexCoord2f(1, 0); glVertex3f(10.5, y + 2, 21);
			glTexCoord2f(1, 1); glVertex3f(10.5, y + 2, 22);
			glTexCoord2f(0, 1); glVertex3f(0, y + 2, 22);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(10.5, y + 0, 21);
			glTexCoord2f(1, 0); glVertex3f(10.5, y + 2, 21);
			glTexCoord2f(1, 1); glVertex3f(10.5, y + 2, 22);
			glTexCoord2f(0, 1); glVertex3f(10.5, y + 0, 22);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(0, y + 2, 22);
			glTexCoord2f(1, 0); glVertex3f(10.5, y + 2, 22);
			glTexCoord2f(1, 1); glVertex3f(10.5, y + 0, 22);
			glTexCoord2f(0, 1); glVertex3f(0, y + 0, 22);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(-0.5, y + 2.5, 21);
			glTexCoord2f(1, 0); glVertex3f(11, y + 2.5, 21);
			glTexCoord2f(1, 1); glVertex3f(11, y - 0.5, 21);
			glTexCoord2f(0, 1); glVertex3f(-0.5, y - 0.5, 21);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// first cylinder
	glPushMatrix(); {

		glTranslatef(10.8, y + 0, 0);
		GLUquadric *quad;
		quad = gluNewQuadric();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, smallwall_top); // here texid corresponds a bitmap image.
		gluQuadricNormals(quad, GLU_SMOOTH);
		gluQuadricTexture(quad, GLU_TRUE);
		gluCylinder(quad, .3, .3, 27, 20, 20);
		glDisable(GL_TEXTURE_2D);
		
		glPushMatrix(); {

			glTranslatef(0, 0, 27);
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
			for (int i = 0; i < 4; i++) {
				glTranslatef(0, 0, 5);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, border); // here texid corresponds a bitmap image.
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);
				gluCylinder(quad, .4, .5, 1, 20, 20);
				glDisable(GL_TEXTURE_2D);
				
			
			
			}
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

// done
void secondPart(double front) {
	double y = 0;
	if (front == -1) y = 20;
	// side gate
	// blue base extended
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(13, y + 0, 0);
			glTexCoord2f(1, 1); glVertex3f(13, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(11, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// back
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 0, 9);
			glTexCoord2f(1, 0); glVertex3f(21, y + 0, 9);
			glTexCoord2f(1, 1); glVertex3f(21, y + 0, 18);
			glTexCoord2f(0, 1); glVertex3f(11, y + 0, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(11, y + 0, 9);
			glTexCoord2f(1, 0); glVertex3f(13, y + 0, 9);
			glTexCoord2f(1, 1); glVertex3f(13, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(11, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(19, y + 0, 9);
			glTexCoord2f(1, 0); glVertex3f(21, y + 0, 9);
			glTexCoord2f(1, 1); glVertex3f(21, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(19, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(19, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(21, y + 0, 0);
			glTexCoord2f(1, 1); glVertex3f(21, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(19, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

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


	// base
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(13, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(19, y + 0, 0);
			glTexCoord2f(1, 1); glVertex3f(19, y + 3 * front, 0);
			glTexCoord2f(0, 1); glVertex3f(13, y + 3 * front, 0);
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
void thirdPart(double front) {
	double y = 0;
	if (front == -1) y = 20;
	// third part
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(28, y + 0, 18);
			glTexCoord2f(1, 1); glVertex3f(28, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(21, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 0, 0);
			glTexCoord2f(1, 0); glVertex3f(28, y + 0, 0);
			glTexCoord2f(1, 1); glVertex3f(28, y + 0, 1.3);
			glTexCoord2f(0, 1); glVertex3f(21, y + 0, 1.3);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// third part border
	glColor3f(1, 1, 1);
	
	if (front == 1) {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.3, y - .2, 16);
				glTexCoord2f(1, 0); glVertex3f(21.3, y - .2, 1.3); 
				glTexCoord2f(1, 1); glVertex3f(21.8, y - .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(21.8, y - .2, 16);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(27.5, y - .2, 16);
				glTexCoord2f(1, 0); glVertex3f(27.5, y - .2, 1.3);
				glTexCoord2f(1, 1); glVertex3f(28.1, y - .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(28.1, y - .2, 16); 
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y - .2, 16);
				glTexCoord2f(1, 0); glVertex3f(27.5, y - .2, 16);
				glTexCoord2f(1, 1); glVertex3f(27.5, y - .2, 15.5);
				glTexCoord2f(0, 1); glVertex3f(21.8, y - .2, 15.5);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y - .2, 1.8);
				glTexCoord2f(1, 0); glVertex3f(27.5, y - .2, 1.8);
				glTexCoord2f(1, 1); glVertex3f(27.5, y - .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(21.8, y - .2, 1.3);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y - .2, 0.8);
				glTexCoord2f(1, 0); glVertex3f(27.5, y - .2, 0.8);
				glTexCoord2f(1, 1); glVertex3f(27.5, y - .2, 0);
				glTexCoord2f(0, 1); glVertex3f(21.8, y - .2, 0);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		
	}
	else {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.3, y + .2, 16);
				glTexCoord2f(1, 0); glVertex3f(21.3, y + .2, 1.3);
				glTexCoord2f(1, 1); glVertex3f(21.8, y + .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(21.8, y + .2, 16); 
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(26.2, y + .2, 16);
				glTexCoord2f(1, 0); glVertex3f(26.2, y + .2, 1.3);
				glTexCoord2f(1, 1); glVertex3f(26.7, y + .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(26.7, y + .2, 16); 
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y + .2, 16);
				glTexCoord2f(1, 0); glVertex3f(26.2, y + .2, 16);
				glTexCoord2f(1, 1); glVertex3f(26.2, y + .2, 15.5);
				glTexCoord2f(0, 1); glVertex3f(21.8, y + .2, 15.5);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y + .2, 1.8);
				glTexCoord2f(1, 0); glVertex3f(26.2, y + .2, 1.8);
				glTexCoord2f(1, 1); glVertex3f(26.2, y + .2, 1.3);
				glTexCoord2f(0, 1); glVertex3f(21.8, y + .2, 1.3);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(21.8, y + .2, 0.8);
				glTexCoord2f(1, 0); glVertex3f(26.2, y + .2, 0.8);
				glTexCoord2f(1, 1); glVertex3f(26.2, y + .2, 0);
				glTexCoord2f(0, 1); glVertex3f(21.8, y + .2, 0);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
	
	// top blue part
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(28, y + 0, 18);
			glTexCoord2f(1, 1); glVertex3f(28, y + 0, 19);
			glTexCoord2f(0, 1); glVertex3f(21, y + 0, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 1, 18);
			glTexCoord2f(1, 0); glVertex3f(28, y + 1, 18);
			glTexCoord2f(1, 1); glVertex3f(28, y + 1, 19);
			glTexCoord2f(0, 1); glVertex3f(21, y + 1, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, y + 0, 18);
			glTexCoord2f(1, 0); glVertex3f(28, y + 1, 18);
			glTexCoord2f(1, 1); glVertex3f(28, y + 1, 19);
			glTexCoord2f(0, 1); glVertex3f(28, y + 0, 19);
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

	// top red

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(21, y + 1.2, 19);
			glTexCoord2f(1, 0); glVertex3f(28, y + 1.2, 19);
			glTexCoord2f(1, 1); glVertex3f(28, y - 0.2, 19);
			glTexCoord2f(0, 1); glVertex3f(21, y - 0.2, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, y + 1.2, 18);
			glTexCoord2f(1, 0); glVertex3f(21, y + 1.2, 18);
			glTexCoord2f(1, 1); glVertex3f(21, y - 0.2, 18);
			glTexCoord2f(0, 1); glVertex3f(28, y - 0.2, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

// done
void rightSym(double x) {
	// three symmetric parts
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 5 + x, 18);
			glTexCoord2f(2, 0); glVertex3f(28, x, 18);
			glTexCoord2f(2, 1); glVertex3f(28, x, 7);
			glTexCoord2f(0, 1); glVertex3f(28, 5 + x, 7);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, x + 0.8, 18);
			glTexCoord2f(3, 0); glVertex3f(28, x, 18);
			glTexCoord2f(3, 1); glVertex3f(28, x, 0);
			glTexCoord2f(0, 1); glVertex3f(28, x + 0.8, 0);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, x + 5 - 0.8, 18);
			glTexCoord2f(3, 0); glVertex3f(28, x + 5, 18);
			glTexCoord2f(3, 1); glVertex3f(28, x + 5, 0);
			glTexCoord2f(0, 1); glVertex3f(28, x + 5 - 0.8, 0);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	// segment border
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x, 16);
			glTexCoord2f(3, 0); glVertex3f(28.1, x, 1.5);
			glTexCoord2f(3, 1); glVertex3f(28, x + .5, 1.5);
			glTexCoord2f(0, 1); glVertex3f(28, x + .5, 16);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5, 16);
			glTexCoord2f(3, 0); glVertex3f(28.1, x + 5, 1.5);
			glTexCoord2f(3, 1); glVertex3f(28, x + 5 - .5, 1.5);
			glTexCoord2f(0, 1); glVertex3f(28, x + 5 - .5, 16);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.5, 16);
			glTexCoord2f(1, 0); glVertex3f(28, x + .5, 16);
			glTexCoord2f(1, 1); glVertex3f(28, x + .5, 15.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.5, 15.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// three parts of each segment
	// bottom
	// right
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8, 7);
			glTexCoord2f(3, 0); glVertex3f(28.1, x + 5 - 0.8, 1.5); 
			glTexCoord2f(3, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 1.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 7);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// leftt
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 0.8, 7);
			glTexCoord2f(3, 0); glVertex3f(28.1, x + 0.8, 1.5);
			glTexCoord2f(3, 1); glVertex3f(28.1, x + 0.8 + 0.2, 1.5);
			glTexCoord2f(0, 1);  glVertex3f(28.1, x + 0.8 + 0.2, 7);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// top
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 7);
			glTexCoord2f(1, 0); glVertex3f(28.1, x + 0.8 + 0.2, 7);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 0.8 + 0.2, 6.8);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 6.8);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	// bot chamber
	// left
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber_side);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 0.8, 0);
			glTexCoord2f(1, 0); glVertex3f(25.1, x + 0.8, 0);
			glTexCoord2f(1, 1); glVertex3f(25.1, x + 0.8, 9);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 0.8, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// right
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber_side);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8, 0);
			glTexCoord2f(1, 0); glVertex3f(25.1, x + 5 - 0.8, 0);
			glTexCoord2f(1, 1); glVertex3f(25.1, x + 5 - 0.8, 9);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// back
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, chamber);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(25.1, x + 0.8, 0);
			glTexCoord2f(1, 0); glVertex3f(25.1, x + 5 - 0.8, 0);
			glTexCoord2f(1, 2); glVertex3f(25.1, x + 5 - 0.8, 9);
			glTexCoord2f(0, 2); glVertex3f(25.1, x + 0.8, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// base
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 0.8, 0);
			glTexCoord2f(1, 0);	glVertex3f(25.1, x + 0.8, 0);
			glTexCoord2f(1, 1); glVertex3f(25.1, x + 5 - 0.8, 0);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8, 0);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// chamber top
	glPushMatrix(); {
		glTranslatef(27.8, x + 2.5, 4.5);
		glScalef(0.2, 0.15, 0.15);
		glRotatef(90, 0, 0, 1);
		gateTopSym();
	}
	glPopMatrix();

	glColor3f(1, 1, 1);
	// middle
	// right
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8, 10);
			glTexCoord2f(2, 0);	glVertex3f(28.1, x + 5 - 0.8, 7.5);
			glTexCoord2f(2, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 7.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// left
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 0.8, 10);
			glTexCoord2f(2, 0);	glVertex3f(28.1, x + 0.8, 7.5);
			glTexCoord2f(2, 1); glVertex3f(28.1, x + 0.8 + 0.2, 7.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 0.8 + 0.2, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// top
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 10);
			glTexCoord2f(1, 0);	glVertex3f(28.1, x + 0.8 + 0.2, 10);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 0.8 + 0.2, 9.8);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 9.8);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// bot
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 7.5);
			glTexCoord2f(1, 0);	glVertex3f(28.1, x + 0.8 + 0.2, 7.5);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 0.8 + 0.2, 7.7);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 7.7);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	// top
	// right
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8, 10.5);
			glTexCoord2f(3, 0);	glVertex3f(28.1, x + 5 - 0.8, 15);
			glTexCoord2f(3, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 15);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 10.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// leftt
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 0.8, 10.5);
			glTexCoord2f(3, 0);	glVertex3f(28.1, x + 0.8, 15);
			glTexCoord2f(3, 1); glVertex3f(28.1, x + 0.8 + 0.2, 15);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 0.8 + 0.2, 10.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// top
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 15);
			glTexCoord2f(1, 0);	glVertex3f(28.1, x + 0.8 + 0.2, 15);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 0.8 + 0.2, 14.6);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 14.6);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	// bot
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 10.5);
			glTexCoord2f(1, 0);	glVertex3f(28.1, x + 0.8 + 0.2, 10.5);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 0.8 + 0.2, 11);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 5 - 0.8 - 0.2, 11);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// upper white jinish
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, white_jinish);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, x + 1.7, 11);
			glTexCoord2f(1, 0);	glVertex3f(28.1, x + 3.3, 11);
			glTexCoord2f(1, 1); glVertex3f(28.1, x + 3.3, 14);
			glTexCoord2f(0, 1); glVertex3f(28.1, x + 1.7, 14);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}


// done
void right() {
	// top blue part
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 0, 18);
			glTexCoord2f(2, 0); glVertex3f(28, 20, 18);
			glTexCoord2f(2, 1); glVertex3f(28, 20, 19);
			glTexCoord2f(0, 1); glVertex3f(28, 0, 19); 
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(27, 0, 18);
			glTexCoord2f(2, 0); glVertex3f(27, 20, 18);
			glTexCoord2f(2, 1); glVertex3f(27, 20, 19);
			glTexCoord2f(0, 1); glVertex3f(27, 0, 19); 
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(27, 0, 18);
			glTexCoord2f(2, 0); glVertex3f(28, 0, 18);
			glTexCoord2f(2, 1); glVertex3f(28, 20, 18);
			glTexCoord2f(0, 1); glVertex3f(27, 20, 18); 
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// top red
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(26.8, 0, 19);
			glTexCoord2f(1, 0); glVertex3f(28.2, 0, 19);
			glTexCoord2f(1, 1); glVertex3f(28.2, 20, 19);
			glTexCoord2f(0, 1); glVertex3f(26.8, 20, 19);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.2, 0, 18);
			glTexCoord2f(1, 0); glVertex3f(26.8, 0, 18);
			glTexCoord2f(1, 1); glVertex3f(26.8, 20, 18);
			glTexCoord2f(0, 1); glVertex3f(28.2, 20, 18);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	// first segment
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 0, 18);
			glTexCoord2f(1, 0); glVertex3f(28, 5, 18);
			glTexCoord2f(1, 1); glVertex3f(28, 5, 9);
			glTexCoord2f(0, 1); glVertex3f(28, 0, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 0, 6);
			glTexCoord2f(1, 0); glVertex3f(28, 1.5, 6);
			glTexCoord2f(1, 1); glVertex3f(28, 1.5, 9);
			glTexCoord2f(0, 1); glVertex3f(28, 0, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, thirdpart);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 3.5, 6);
			glTexCoord2f(1, 0); glVertex3f(28, 5, 6);
			glTexCoord2f(1, 1); glVertex3f(28, 5, 9);
			glTexCoord2f(0, 1); glVertex3f(28, 3.5, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	
	// chamber
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 1.5, 6);
			glTexCoord2f(1, 0); glVertex3f(26, 1.5, 6);
			glTexCoord2f(1, 1); glVertex3f(26, 1.5, 9);
			glTexCoord2f(0, 1); glVertex3f(28, 1.5, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 3.5, 6);
			glTexCoord2f(1, 0); glVertex3f(26, 3.5, 6);
			glTexCoord2f(1, 1); glVertex3f(26, 3.5, 9);
			glTexCoord2f(0, 1); glVertex3f(28, 3.5, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(26, 1.5, 6);
			glTexCoord2f(1, 0); glVertex3f(26, 3.5, 6);
			glTexCoord2f(1, 1); glVertex3f(26, 3.5, 9);
			glTexCoord2f(0, 1); glVertex3f(26, 1.5, 9);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28, 1.5, 6);
			glTexCoord2f(1, 0); glVertex3f(26, 1.5, 6);
			glTexCoord2f(1, 1); glVertex3f(26, 3.5, 6);
			glTexCoord2f(0, 1); glVertex3f(28, 3.5, 6);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	
	// first segment border
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, -0.2, 6);
			glTexCoord2f(3, 0); glVertex3f(28.1, -0.2, 16);
			glTexCoord2f(3, 1); glVertex3f(28.1, 0.3, 16);
			glTexCoord2f(0, 1); glVertex3f(28.1, 0.3, 6);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, 5, 6);
			glTexCoord2f(3, 0); glVertex3f(28.1, 5, 16);
			glTexCoord2f(3, 1); glVertex3f(28.1, 4.5, 16);
			glTexCoord2f(0, 1); glVertex3f(28.1, 4.5, 6);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, 4.5, 16);
			glTexCoord2f(1, 0); glVertex3f(28.1, 0.3, 16);
			glTexCoord2f(1, 1); glVertex3f(28.1, 0.3, 15.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, 4.5, 15.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(28.1, 4.5, 6);
			glTexCoord2f(1, 0); glVertex3f(28.1, 0.3, 6);
			glTexCoord2f(1, 1); glVertex3f(28.1, 0.3, 6.5);
			glTexCoord2f(0, 1); glVertex3f(28.1, 4.5, 6.5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


	// big tower
	glPushMatrix(); {
		glColor3f(1, 1, 1);
		glTranslatef(28, 21.5, 1.5);
		GLUquadric *quad;
		quad = gluNewQuadric();
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(8, 10, 5); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, back_tower);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 1.5, 1.5, 16.5, 20, 20);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		
	}
	glPopMatrix();
	glPushMatrix(); {
		glColor3f(1, 1, 1);
		glTranslatef(28, 21.5, 0);
		GLUquadric *quad;
		quad = gluNewQuadric();
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(8, 1, 5); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, back_tower_base);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 1.5, 1.5, 1.5, 20, 20);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		
	}
	glPopMatrix();
	
	glPushMatrix(); {
		glColor3f(1, 1, 1);
		glTranslatef(28, 21.5, 18);
		GLUquadric *quad;
		quad = gluNewQuadric();
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(8, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 1.5, 1.5, 1, 20, 20);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		
	}
	glPopMatrix();
}

// done
void back() {
	thirdPart(-1);
	secondPart(-1); 
	firstPart(-1);
}

// done
void sentryRoom(bool roof) {
	GLUquadric *quad = gluNewQuadric();
	
	if (!roof) {
		
		// first base
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(60, 1, 1); // This scaling controls the number of texture repetitions 
			glBindTexture(GL_TEXTURE_2D, border);
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
					glBindTexture(GL_TEXTURE_2D, smallwall_top);
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glDisable(GL_TEXTURE_2D);
					
					


				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3);

					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, smallwall_top);
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
			glBindTexture(GL_TEXTURE_2D, border);
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
	glBindTexture(GL_TEXTURE_2D, thirdpart);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(7, -4, 3);
	glTexCoord2f(1, 0); glVertex3f(-7, -4, 3);
	glTexCoord2f(1, 1); glVertex3f(-7, 4, 3);
	glTexCoord2f(0, 1); glVertex3f(7, 4, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, thirdpart);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(7, 4, 3);
	glTexCoord2f(1, 0); glVertex3f(-7, 4, 3);
	glTexCoord2f(1, 1); glVertex3f(0, 8, 3);
	glTexCoord2f(0, 1); glVertex3f(0, 8, 3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, thirdpart);
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
				glBindTexture(GL_TEXTURE_2D, border);
				gluQuadricNormals(quad, GLU_SMOOTH);
				gluQuadricTexture(quad, GLU_TRUE);

				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 4-i, 4-i, 1, 6, 100);
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
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 0.3, 0.3, 1, 60, 100);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 0.2, 0.2, 5, 60, 100);
			glDisable(GL_TEXTURE_2D);
			glPushMatrix(); {
				glTranslatef(0, 0, 5);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, smallwall_top);
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
		double theta2 = (2 * 3.1416 / 6) * ((i+1)%6);
		double x2 = r*sin(theta2);
		double y2 = r*cos(theta2);
		double z2 = 10;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, border);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 0); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2);
		glTexCoord2f(1, 1); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2 - 1);
		glTexCoord2f(0, 1); glVertex3f(x1, y1, z1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, border);
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
			glBindTexture(GL_TEXTURE_2D, border);
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
			glBindTexture(GL_TEXTURE_2D, smallwall_top);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);
			gluCylinder(quad, 4 - i, 4 - i, 0.5, 8, 100);
			glDisable(GL_TEXTURE_2D);
			
		}
		glPopMatrix();
		
	}
	
	
	
}

// done
void roof() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, border);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 18);
	glTexCoord2f(5, 0); glVertex3f(27, 0, 18);
	glTexCoord2f(5, 5); glVertex3f(27, 20, 18);
	glTexCoord2f(0, 5); glVertex3f(0, 20, 18);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix(); {
		glTranslatef(24, 3, 18);
		glScalef(0.5, 0.5, 0.5);
		sentryRoom(false);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(28, 21, 18);
		glScalef(0.5, 0.5, 0.5);
		sentryRoom(true);
	}
	glPopMatrix();
	
}

// done
void smallWall(int i) {
	double x = 28 + 5*i;
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 0, 0);
			glTexCoord2f(1, 0); glVertex3f(x + 5, 0, 0);
			glTexCoord2f(1, 1); glVertex3f(x + 5, 0, 5);
			glTexCoord2f(0, 1); glVertex3f(x, 0, 5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 5, 0);
			glTexCoord2f(1, 0); glVertex3f(x + 5, 5, 0);
			glTexCoord2f(1, 1); glVertex3f(x + 5, 5, 5);
			glTexCoord2f(0, 1); glVertex3f(x, 5, 5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 0, 5);
			glTexCoord2f(1, 0); glVertex3f(x + 5, 0, 5);
			glTexCoord2f(1, 1); glVertex3f(x + 5, 5, 5);
			glTexCoord2f(0, 1); glVertex3f(x, 5, 5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
 
	

	if (i == 0) {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, border);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(x, 0, 6);
				glTexCoord2f(1, 0); glVertex3f(x, 5, 6);
				glTexCoord2f(1, 1); glVertex3f(x, 5, 5);
				glTexCoord2f(0, 1); glVertex3f(x, 0, 5);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
	}
	else if (i == 5) {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, border);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON); {
				glTexCoord2f(0, 0); glVertex3f(x+5, 0, 6);
				glTexCoord2f(1, 0); glVertex3f(x+5, 5, 6);
				glTexCoord2f(1, 1); glVertex3f(x+5, 5, 5);
				glTexCoord2f(0, 1); glVertex3f(x+5, 0, 5);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 0, 6);
			glTexCoord2f(1, 0); glVertex3f(x + 5, 0, 6);
			glTexCoord2f(1, 1); glVertex3f(x + 5, 0, 5);
			glTexCoord2f(0, 1); glVertex3f(x, 0, 5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, smallwall_top);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 5, 6);
			glTexCoord2f(1, 0); glVertex3f(x + 5, 5, 6);
			glTexCoord2f(1, 1); glVertex3f(x + 5, 5, 5);
			glTexCoord2f(0, 1); glVertex3f(x, 5, 5);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

// done
void watchTower() {
	// bottom
	GLUquadric *quad = gluNewQuadric();
	
	glEnable(GL_TEXTURE_2D); {
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); {
			glScalef(8, 1, 1); 
			glBindTexture(GL_TEXTURE_2D, border);
			gluQuadricNormals(quad, GLU_SMOOTH);
			gluQuadricTexture(quad, GLU_TRUE);

			glMatrixMode(GL_MODELVIEW);
			gluCylinder(quad, 15, 15, 10, 8, 50);
			glMatrixMode(GL_TEXTURE);
		} glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix(); {
		glPushMatrix(); {
			glTranslatef(0, 0, 10);
			glEnable(GL_TEXTURE_2D); {
				glMatrixMode(GL_TEXTURE);
				glPushMatrix(); {
					glScalef(60, 1, 1);
					glBindTexture(GL_TEXTURE_2D, border);
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					glMatrixMode(GL_MODELVIEW);
					gluCylinder(quad, 17, 17, 2, 8, 100);
					glMatrixMode(GL_TEXTURE);
				} glPopMatrix();
			}

			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
			// floor
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 1); glVertex3f(-12, -12, 0);
				glTexCoord2f(0, 1); glVertex3f(12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(15, 0, 0);
				glTexCoord2f(1, 1); glVertex3f(15, 0, 0);
				glTexCoord2f(0, 1); glVertex3f(12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-15, 0, 0);
				glTexCoord2f(1, 1); glVertex3f(-15, 0, 0);
				glTexCoord2f(0, 1); glVertex3f(-12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 1); glVertex3f(0, 15, 0);
				glTexCoord2f(0, 1); glVertex3f(0, 15, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, -12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, -12, 0);
				glTexCoord2f(1, 1); glVertex3f(0, -15, 0);
				glTexCoord2f(0, 1); glVertex3f(0, -15, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();	
		// second base khaj
		glTranslatef(0, 0, 7);
		glColor3f(1, 1, 1);
		for (int i = 0; i < 8; i++) {
			double theta = (2 * 3.1416 / 8) * i;
			double r = 17;
			double x1 = r*sin(theta);
			double y1 = r*cos(theta);
			double theta2 = (2 * 3.1416 / 8) * ((i + 1) % 8);
			double x2 = r*sin(theta2);
			double y2 = r*cos(theta2);
			double delx = (x2 - x1) / 3;
			double dely = (y2 - y1) / 3;
			r = 15;
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
					glBindTexture(GL_TEXTURE_2D, smallwall_top); // here texid corresponds a bitmap image.
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glDisable(GL_TEXTURE_2D);

				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3);
					glEnable(GL_TEXTURE_2D); {
						glBindTexture(GL_TEXTURE_2D, smallwall_top);
						glNormal3f(1.0, 0.0, 0.0);
						glBegin(GL_POLYGON);
						glTexCoord2f(0, 0); glVertex3f(x1 + delx*j, y1 + dely*j, 0);
						glTexCoord2f(1, 0); glVertex3f(x3 + delx2*j, y3 + dely2*j, 0);
						glTexCoord2f(1, 1); glVertex3f(x3 + delx2*j, y3 + dely2*j, -2);
						glTexCoord2f(0, 1); glVertex3f(x1 + delx*j, y1 + dely*j, -0.5);
						glEnd();
					}
					glDisable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}

		}
	}
	glPopMatrix();
	// third base
	glPushMatrix(); {
		glTranslatef(0, 0, 9);
		// vitorer cylinder (main room)
		for (double i = 0; i < 0.5; i += 0.1) {
			glPushMatrix(); {
				glTranslatef(0, 0, 2);
				glEnable(GL_TEXTURE_2D); {
					glMatrixMode(GL_TEXTURE);
					glPushMatrix(); {
						glScalef(60, 1, 1);
						glBindTexture(GL_TEXTURE_2D, border);
						gluQuadricNormals(quad, GLU_SMOOTH);
						gluQuadricTexture(quad, GLU_TRUE);
						glMatrixMode(GL_MODELVIEW);
						gluCylinder(quad, 13 - i, 13 - i, 1, 8, 100);
						glMatrixMode(GL_TEXTURE);
					} glPopMatrix();
				}

				glDisable(GL_TEXTURE_2D);
				glMatrixMode(GL_MODELVIEW);
				
			}
			glPopMatrix();
		}
		// columns
		for (int i = 0; i < 8; i++) {
			double theta = (2 * 3.1416 / 8) * i;
			double r = 13;
			double x1 = r*sin(theta);
			double y1 = r*cos(theta);
			double theta2 = (2 * 3.1416 / 8) * ((i + 1) % 8);
			double x2 = r*sin(theta2);
			double y2 = r*cos(theta2);
			double delx = (x2 - x1) / 3;
			double dely = (y2 - y1) / 3;
			for (int j = 0; j < 3; j++) {
				glPushMatrix(); {
					glTranslatef(x1 + delx*j, y1 + dely*j, 3);
					//gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, border); // here texid corresponds a bitmap image.
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.2, 0.2, 5, 60, 100);
					glDisable(GL_TEXTURE_2D);
					glPushMatrix(); {
						glTranslatef(0, 0, 5);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, border); // here texid corresponds a bitmap image.
						gluQuadricNormals(quad, GLU_SMOOTH);
						gluQuadricTexture(quad, GLU_TRUE);
						gluCylinder(quad, 0.3, 0.3, 2, 60, 100);
						glDisable(GL_TEXTURE_2D);
						
					}
					glPopMatrix();

				}
				glPopMatrix();
				
			}

		}
		// triangular small gates
		for (int i = 0; i < 8; i++) {
			double theta = (2 * 3.1416 / 8) * i;
			double r = 13;
			double x1 = r*sin(theta);
			double y1 = r*cos(theta);
			double z1 = 8;
			double theta2 = (2 * 3.1416 / 8) * ((i + 1) % 8);
			double x2 = r*sin(theta2);
			double y2 = r*cos(theta2);
			double z2 = 10;

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, border);
			glNormal3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex3f(x1, y1, z2);
			glTexCoord2f(1, 0); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2);
			glTexCoord2f(1, 1); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2 - 1);
			glTexCoord2f(0, 1); glVertex3f(x1, y1, z1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, border);
			glNormal3f(1.0, 0.0, 0.0); 
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex3f(x2, y2, z2);
			glTexCoord2f(1, 0); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2);
			glTexCoord2f(1, 1); glVertex3f((x1 + x2) / 2, (y1 + y2) / 2, z2 - 1);
			glTexCoord2f(0, 1); glVertex3f(x2, y2, z1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		
		}

		
	}
	glPopMatrix();
	// fourth base
	glPushMatrix(); {
		glPushMatrix(); {
			glTranslatef(0, 0, 20);
			glEnable(GL_TEXTURE_2D); {
				glMatrixMode(GL_TEXTURE);
				glPushMatrix(); {
					glScalef(60, 1, 1);
					glBindTexture(GL_TEXTURE_2D, border);
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					glMatrixMode(GL_MODELVIEW);
					gluCylinder(quad, 17, 17, 2, 8, 100);
					glMatrixMode(GL_TEXTURE);
				} glPopMatrix();
			}

			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
			// floor

			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 1); glVertex3f(-12, -12, 0);
				glTexCoord2f(0, 1); glVertex3f(12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(15, 0, 0);
				glTexCoord2f(1, 1); glVertex3f(15, 0, 0);
				glTexCoord2f(0, 1); glVertex3f(12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-15, 0, 0);
				glTexCoord2f(1, 1); glVertex3f(-15, 0, 0);
				glTexCoord2f(0, 1); glVertex3f(-12, -12, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, 12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, 12, 0);
				glTexCoord2f(1, 1); glVertex3f(0, 15, 0);
				glTexCoord2f(0, 1); glVertex3f(0, 15, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, thirdpart);
				glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex3f(12, -12, 0);
				glTexCoord2f(1, 0); glVertex3f(-12, -12, 0);
				glTexCoord2f(1, 1); glVertex3f(0, -15, 0);
				glTexCoord2f(0, 1); glVertex3f(0, -15, 0);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
		// second base khaj
		glTranslatef(0, 0, 17);
		glColor3f(1, 1, 1);
		for (int i = 0; i < 8; i++) {
			double theta = (2 * 3.1416 / 8) * i;
			double r = 17;
			double x1 = r*sin(theta);
			double y1 = r*cos(theta);
			double theta2 = (2 * 3.1416 / 8) * ((i + 1) % 8);
			double x2 = r*sin(theta2);
			double y2 = r*cos(theta2);
			double delx = (x2 - x1) / 3;
			double dely = (y2 - y1) / 3;
			r = 15;
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
					glBindTexture(GL_TEXTURE_2D, smallwall_top); // here texid corresponds a bitmap image.
					gluQuadricNormals(quad, GLU_SMOOTH);
					gluQuadricTexture(quad, GLU_TRUE);
					gluCylinder(quad, 0.3, 0.3, 2.1, 4, 100);
					glDisable(GL_TEXTURE_2D); 


				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 0, 3); 
					glEnable(GL_TEXTURE_2D); {
						glBindTexture(GL_TEXTURE_2D, smallwall_top);
						glNormal3f(1.0, 0.0, 0.0);
						glBegin(GL_POLYGON);
						glTexCoord2f(0, 0); glVertex3f(x1 + delx*j, y1 + dely*j, 0);
						glTexCoord2f(1, 0); glVertex3f(x3 + delx2*j, y3 + dely2*j, 0);
						glTexCoord2f(1, 1); glVertex3f(x3 + delx2*j, y3 + dely2*j, -2);
						glTexCoord2f(0, 1); glVertex3f(x1 + delx*j, y1 + dely*j, -0.5);
						glEnd();
					}
					glDisable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}

		}
	}
	glPopMatrix();
	glPushMatrix(); {
		glScalef(1.5, 1.5, 1.5);
		glTranslatef(0, 0, 14);
		sentryRoom(false);
	}
	glPopMatrix();
	
}

// done
void baseWall(int i) {
	double x = 5.7 * i;
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, basewall);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(x, 0, 0);
			glTexCoord2f(1, 0); glVertex3f(x + 5.7, 0, 0);
			glTexCoord2f(1, 1); glVertex3f(x + 5.7, 0, 10);
			glTexCoord2f(0, 1); glVertex3f(x, 0, 10); 
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	
	
	
	glPushMatrix(); {
		glEnable(GL_TEXTURE_2D); {
			glScalef(0.7, 0.7, 1);
			glTranslatef(95, 0, 0);
			glMatrixMode(GL_TEXTURE);
			glPushMatrix(); {
				glScalef(7, 1, 1);
				GLUquadric *quad = gluNewQuadric();
				glBindTexture(GL_TEXTURE_2D, basewall); // here texid corresponds a bitmap image.
				gluQuadricNormals(quad, GLU_SMOOTH);
				
				gluQuadricTexture(quad, GLU_TRUE);
				glMatrixMode(GL_MODELVIEW);
				gluCylinder(quad, 15, 15, 10, 8, 50);
				glMatrixMode(GL_TEXTURE);
			}
			glPopMatrix();			

		}
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);		
	}
	glPopMatrix();
}

// done
void baseWallRight(int i) {
	double y = 5.7 * i;
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, basewall);
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON); {
			glTexCoord2f(0, 0); glVertex3f(70, y, 0);
			glTexCoord2f(1, 0); glVertex3f(70, y + 5.7, 0);
			glTexCoord2f(1, 1); glVertex3f(70, y + 5.7, 10);
			glTexCoord2f(0, 1); glVertex3f(70, y, 10);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);


}

void base() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, base_tex);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(0, 0, -1);
	glTexCoord2f(5, 0); glVertex3f(69.5, 0, -1);
	glTexCoord2f(5, 5); glVertex3f(69.5, 86, -1);
	glTexCoord2f(0, 5); glVertex3f(0, 86, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void part() {
	firstPart(1);
	secondPart(1);
	thirdPart(1);
	right();
	for (double x = 5; x <= 15; x += 5) {
		rightSym(x);
	}
	back();
	roof();
	for (int i = 0; i < 6; i++) {
		smallWall(i);
	}
	glPushMatrix(); {
		glScalef(0.7, 0.7, 0.7);
		glTranslatef(95, 0, 0);
		watchTower();
	}
	glPopMatrix();
	for (int i = 0; i < 10; i++) {
		glPushMatrix(); {
			glTranslatef(0, 0, -10);
			baseWall(i);
			
		}
		glPopMatrix();
	}
	for (int i = 0; i < 15; i++) {
		glPushMatrix(); {
			glTranslatef(0, 0, -10);
			baseWallRight(i);
		}
		glPopMatrix();
	}
	base();
}

void drawTowers() {
	glPushMatrix(); {
		glTranslatef(0, 9, 18);
		dome(true);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(-15, 9, 18);
		glScalef(0.7, 0.7, 0.7);
		dome(true);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(15, 9, 18);
		glScalef(0.7, 0.7, 0.7);
		dome(true);
	}
	glPopMatrix();
}

void drawGate() {
	
	part();
	glPushMatrix(); {
		glScalef(-1, 1, 1);
		part();
	}
	glPopMatrix();
	drawTowers();
	
	//gateTop();
	//watchTower();

	
}

