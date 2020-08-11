#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include "tajmahal.h"
#include "tree.h"


float mycolors [10][4] = {			/**<arrays for colors*/
	{1.0,0.0,0.0,1.0},///red-0
	{0.0,1.0,0.0,1.0},///green-1
	{0.0,0.0,1.0,1.0},///blue-2
	{1.0,1.0,1.0,1.0},///white-3
	{0.0,0.0,0.0,1.0}, ///black-4
	{1.0,0.65,0.0,1.0},///orange-5
	{0.6,0.6,0.6,1.0}, ///gray-6
	{1,1,0,1},///yellow-7
	{0.1,1,0.1,1},
	{0,0.39,0,1}
};


double rotate_y=0; 			/**<Used to yaw*/
double rotate_x=0;			/**<Used to pitch*/
double rotate_z=0;			/**<Used to roll*/
double zoom=1;				/**<Scaling factor*/
GLdouble eyeX,eyeY,eyeZ;		/**<Coordinates of the eye*/
  
///TajMahal and tree objects created.
tajMahal TajMahal;
Tree tree;

/**Function to interact with the scene.
*/
void processNormalKeys(unsigned char key, int x, int y) {
	///a,d - yaw
	///w,s - pitch
	///z,x - roll
	///-,+ - zoom
	///8,2 - pan along y-axis
	///6,4 - pan alng x-axis
	///5,0 - pan along z-axis
	///q - reset to defaults
	
	switch(key){
		case 'a': rotate_y-=1;break;	
		case 's': rotate_x+=1;break;
		case 'w': rotate_x-=1;break;
		case 'd': rotate_y+=1;break;
		case '-': if(zoom>0.01)	zoom-=0.01;break;	///Ensuring zoom always stays positive
		case '+': zoom+=0.01;break;	
		case '8': eyeY+=0.1;break;
		case '2': eyeY-=0.1;break;
		case '6': eyeX+=0.1;break;
		case '4': eyeX-=0.1;break;
		case '5': eyeZ-=0.1;break;
		case '0': eyeZ+=0.1;break;
		case 'z': rotate_z+=1;break;
		case 'x': rotate_z-=1;break;
		case 'q': eyeX=eyeY=eyeZ=rotate_x=rotate_y=rotate_z=0; 
				  zoom=1; break;
	};
		
	/**Redisplay after changing scene
	*/
	glutPostRedisplay();	
}


void init(){
	///Materials initialized
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolors[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mycolors[5]);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);

	///Light setup
	glLightfv(GL_LIGHT0, GL_AMBIENT, mycolors[6]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mycolors[3]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mycolors[5]);
	glLightfv(GL_LIGHT0, GL_POSITION, mycolors[3]);

	glEnable(GL_LIGHTING);                /// so the renderer considers light
	glEnable(GL_LIGHT0);                  /// Turn LIGHT0 on
	glEnable(GL_DEPTH_TEST);              /// so the renderer considers depth
	glEnable(GL_NORMALIZE);
	
	///Tree model loaded
	tree.loadModel();
}


void displayer(){
	///Window cleared.
	///Setting buffer bits.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity;
	
	/**Pushes the current matrix to the stack
	*/
	glPushMatrix();
	///Positions of eye and centre of object set. Up vector also set.
	gluLookAt(eyeX,eyeY,eyeZ+3,eyeX,eyeY,eyeZ,0,1,0);
	///Appropriate matrix transformations done.
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glScalef(zoom,zoom,zoom);
    
	///Color set to white and the objects are drawn.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolors[3]);
	TajMahal.draw_Taj();
	tree.draw();
	/**Pops from the stack
	*/
	glPopMatrix();
	///Screen flushed and the buffers swapped.
	glFlush();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	///Viewport and matrix modes are set.
	gluPerspective(45, 1, 0.1f, 500.0);
	glMatrixMode(GL_MODELVIEW);	
	
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	
	///Window initialized.
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TAJ MAHAL");
	init();
	glEnable(GL_DEPTH_TEST);		///Depth testing enabled.
	///Appropriate callback functions 
	glutDisplayFunc(displayer);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);

	glutMainLoop();
	return 0;
}


