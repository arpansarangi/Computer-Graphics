#include <GL/glut.h>
#include<math.h>

#include "tajmahal.h"


float mycolor [11][4] = {		/**<color array*/
	{1.0,0.0,0.0,1.0},//red-0
	{0.0,1.0,0.0,1.0},//green-1
	{0.0,0.0,1.0,1.0},//blue-2
	{1.0,1.0,1.0,1.0},//white-3
	{0.0,0.0,0.0,1.0}, //black-4
	{1.0,0.65,0.0,1.0},//orange-5
	{0.6,0.6,0.6,1.0}, //gray-6
	{1,1,0,1},//yellow-7
	{0.1,1.0,0.1,1},
	{0,0.39,0,1},
	{0,0.467,0.745}// waterblue
};

/**Draws a cylinder
*/
void draw_cylinder(GLfloat radius,GLfloat height,GLubyte R,GLubyte G,GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /// Draw the tube 
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2.0*3.14 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /// Draw the circle on top of cylinder
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2.0*3.14 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

/**Draws cornor slanted wall
*/
void tajMahal::draw_cornerWindow(float x){
	glBegin(GL_POLYGON);
	glVertex3f(0.425,-0.25,x);
	glVertex3f(0.425,0.2,x);
	glVertex3f(x,0.2,0.425);
	glVertex3f(x,-0.25,0.425);
	glEnd();
}


void tajMahal::draw_window(float x){
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[3]);
	///Drawing side walls
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,x);
	glVertex3f(0.0,0.225,x);
	glVertex3f(0.05,0.225,x);
	glVertex3f(0.05,0.0,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.2,0,x);
	glVertex3f(0.2,0.225,x);	
	glVertex3f(0.25,0.225,x);
	glVertex3f(0.25,0.0,x);
	glEnd();
	glBegin(GL_POLYGON);		///2 triangles
	glVertex3f(0.05,0.15,x);
	glVertex3f(0.05,0.2,x);
	glVertex3f(0.125,0.2,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.125,0.2,x);
	glVertex3f(0.2,0.2,x);
	glVertex3f(0.2,0.15,x);
	glEnd();
	glBegin(GL_POLYGON);		///upper wall
	glVertex3f(0.05,0.2,x);
	glVertex3f(0.05,0.225,x);
	glVertex3f(0.2,0.225,x);
	glVertex3f(0.2,0.2,x);
	glEnd();
}

/**Draws the major exterior parts of the tajmahal
*/
void tajMahal::draw_ext(float x){
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[3]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	glBegin(GL_POLYGON);
	glVertex3f(-0.175,-0.25,x);
	glVertex3f(-0.175,0.25,x);
	glVertex3f(-0.1,0.25,x);
	glVertex3f(-0.1,-0.25,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1,-0.25,x);
	glVertex3f(0.1,0.25,x);	
	glVertex3f(0.175,0.25,x);
	glVertex3f(0.175,-0.25,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.1,0.0,x);
	glVertex3f(-0.1,0.15,x);
	glVertex3f(0.0,0.15,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.15,x);
	glVertex3f(0.1,0.15,x);
	glVertex3f(0.1,0.0,x);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.1,0.15,x);
	glVertex3f(-0.1,0.25,x);
	glVertex3f(0.1,0.25,x);
	glVertex3f(0.1,0.15,x);
	glEnd();
	///Drawing corner window
	draw_cornerWindow(0.5);
	///Drawing straight windows
	glTranslatef(0.175,-0.025,0);
	draw_window(0.5);
	glTranslatef(0.0,-0.225,0);
	draw_window(0.5);
	glTranslatef(-0.6,0,0);
	draw_window(0.5);
	glTranslatef(0,0.225,0);
	draw_window(0.5);	
}


void tajMahal::draw_dome(){
	///The dome is made up of a sphere and three cones arranged in the appropriate fashion.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[3]);
	///Drawing cone 1 
	glPushMatrix();	
	glTranslatef(0, 0.5, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidCone(0.175, 0.2, 90, 10);	
	glPopMatrix();
	///Drawing the sphere
	glPushMatrix();	
	glTranslatef(0, 0.4, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidSphere(0.2,70,12);	
	glPopMatrix();
	///Cone2
	glPushMatrix();	
	glTranslatef(0, 0.3, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidCone(0.05, 0.5, 90, 100);	
	glPopMatrix();
	///Cone3
	glPushMatrix();	
	glTranslatef(0, 0.3, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);	
	glClearColor(0.5,0.5,0.5,1.0);
	draw_cylinder(0.175, 0.3, 1,1,1);	
	glPopMatrix();
}


void tajMahal::draw_cornorPillars(){
	///A pillar is made up of cylinders and tori. They are drawn after applying the convenient transformations.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[3]);	///Color set
	glPushMatrix();
	glRotatef(270,1,0,0);
	draw_cylinder(0.075,0.101,1,1,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.1,0);
	glRotatef(270,1,0,0);
	draw_cylinder(0.055,0.2,1,1,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.3,0);
	glRotatef(270,1,0,0);
	glutSolidTorus(0.015,0.056,15,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.3,0);
	glRotatef(270,1,0,0);
	draw_cylinder(0.05,0.2,1,1,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glRotatef(270,1,0,0);
	glutSolidTorus(0.015,0.051,15,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glRotatef(270,1,0,0);
	draw_cylinder(0.045,0.2,1,1,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.7,0);
	glRotatef(270,1,0,0);
	glutSolidTorus(0.015,0.046,15,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.66,0);
	glScalef(0.25,0.25,0.25);
	draw_dome();
	glPopMatrix();
}

/**Draws some intricate shapes to make tajmahal more complete.
*/
void tajMahal::draw_fill1(){
	glPushMatrix();
	glTranslatef(-0.175,-0.35,0.5);
	glScalef(0.5,0.8,0.5);
	draw_cornorPillars();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.175,-0.35,0.5);
	glScalef(0.5,0.8,0.5);
	draw_cornorPillars();
	glPopMatrix();
}


void tajMahal::draw_Taj(){
	///draws the full tajmahal at appropriate position
	///Drawing the main dome
	///cone 1
	glPushMatrix();	
	glTranslatef(0, 0.5, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidCone(0.175, 0.2, 90, 10);	
	glPopMatrix();
	///sphere
	glPushMatrix();	
	glTranslatef(0, 0.4, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidSphere(0.2,70,12);	
	glPopMatrix();
	///cone2
	glPushMatrix();	
	glTranslatef(0, 0.3, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);	
	glutSolidCone(0.05, 0.5, 90, 100);	
	glPopMatrix();
	///cone3
	glPushMatrix();	
	glTranslatef(0, 0.3, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);	
	glClearColor(0.5,0.5,0.5,1.0);
	glutSolidCone(0.175, 0.3, 90, 10);	
	glPopMatrix();
	///cube1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[3]);
	glTranslatef(0, 0.1, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutSolidCube(0.35);
	glPopMatrix();
	///cube2
	glPushMatrix();
	glTranslatef(0, -0.1, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutSolidCube(0.35);
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.8,-0.25,0.8);
	glVertex3f(-0.8,-0.25,-0.8);
	glVertex3f(0.8,-0.25,-0.8);
	glVertex3f(0.8,-0.25,0.8);
	glEnd();
	///base cuboid
	glBegin(GL_POLYGON);
	glVertex3f(-0.8,-0.35,0.8);
	glVertex3f(-0.8,-0.35,-0.8);
	glVertex3f(0.8,-0.35,-0.8);
	glVertex3f(0.8,-0.35,0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.8,-0.25,0.8);
	glVertex3f(0.8,-0.25,0.8);
	glVertex3f(0.8,-0.35,0.8);
	glVertex3f(-0.8,-0.35,0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.8,-0.25,-0.8);
	glVertex3f(0.8,-0.25,-0.8);
	glVertex3f(0.8,-0.35,-0.8);
	glVertex3f(-0.8,-0.35,-0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.8,-0.25,0.8);
	glVertex3f(-0.8,-0.25,-0.8);
	glVertex3f(-0.8,-0.35,-0.8);
	glVertex3f(-0.8,-0.35,0.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.8,-0.25,0.8);
	glVertex3f(0.8,-0.25,-0.8);
	glVertex3f(0.8,-0.35,-0.8);
	glVertex3f(0.8,-0.35,0.8);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	///Drawing the garden grass
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[8]);	
	glBegin(GL_POLYGON);
	glVertex3f(-1.8,-0.351,1.8);
	glVertex3f(-1.8,-0.351,-1.8);
	glVertex3f(1.8,-0.351,-1.8);
	glVertex3f(1.8,-0.351,1.8);
	glEnd();
	///water
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[10]);
	glBegin(GL_POLYGON);
	glVertex3f(-0.09,-0.35,1.8);
	glVertex3f(-0.09,-0.35,-1.8);
	glVertex3f(0.09,-0.35,-1.8);
	glVertex3f(0.09,-0.35,1.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.8,-0.35,0.09);
	glVertex3f(-1.8,-0.35,-0.09);
	glVertex3f(1.8,-0.35,-0.09);
	glVertex3f(1.8,-0.35,0.09);
	glEnd();
	///side walk
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[6]);
	glBegin(GL_POLYGON);
	glVertex3f(-0.1,-0.35,1.8);
	glVertex3f(-0.1,-0.35,-1.8);
	glVertex3f(-0.17,-0.35,-1.8);
	glVertex3f(-0.17,-0.35,1.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.8,-0.35,-0.17);
	glVertex3f(-1.8,-0.35,-0.1);
	glVertex3f(1.8,-0.35,-0.1);
	glVertex3f(1.8,-0.35,-0.17);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1,-0.35,1.8);
	glVertex3f(0.1,-0.35,-1.8);
	glVertex3f(0.17,-0.35,-1.8);
	glVertex3f(0.17,-0.35,1.8);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.8,-0.35,0.17);
	glVertex3f(-1.8,-0.35,0.1);
	glVertex3f(1.8,-0.35,0.1);
	glVertex3f(1.8,-0.35,0.17);
	glEnd();
	glPopMatrix();
	///roof
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolor[6]);
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex3f(-0.425,0.2,0.5);
	glVertex3f(0.425,0.2,0.5);
	glVertex3f(0.5,0.2,0.425);
	glVertex3f(0.5,0.2,-0.425);
	glVertex3f(0.425,0.2,-0.5);
	glVertex3f(-0.425,0.2,-0.5);
	glVertex3f(-0.5,0.2,-0.425);
	glVertex3f(-0.5,0.2,0.425);
	glEnd();
	///exterior walls
	glPushMatrix();
	draw_ext(0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,1,0);	
	draw_ext(0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180,0,1,0);	
	draw_ext(0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270,0,1,0);	
	draw_ext(0.5);
	glPopMatrix();
	glPushMatrix();	
	///top 4 smaller domes
	glPopMatrix();
	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	glTranslatef(0.6,0.2,0.6);
	draw_dome();
	glTranslatef(0,0,-1.2);
	draw_dome();
	glTranslatef(-1.2,0,0);
	draw_dome();
	glTranslatef(0.,0,1.2);
	draw_dome();
	glPopMatrix();
	///various pillars
	glPushMatrix();
	glTranslatef(0.75,-0.35,0.75);
	draw_cornorPillars();
	glTranslatef(0,0,-1.5);
	draw_cornorPillars();	
	glTranslatef(-1.5,0,0);
	draw_cornorPillars();
	glTranslatef(0,0,1.5);
	draw_cornorPillars();
	glPopMatrix();
	glPushMatrix();
	draw_fill1();
	glRotatef(90,0,1,0);
	draw_fill1();
	glRotatef(90,0,1,0);
	draw_fill1();
	glRotatef(90,0,1,0);
	draw_fill1();	
	glPopMatrix();
}




