#include <iostream>
#include <GL/glut.h> 

using namespace std;


/**Defines a 2D point
*/
struct point
{
	float x;
	float y;
};

int n;					/*<Number of control points*/
///Degree is n-1
point points[200];		/*<Array for control points*/
int draggedTo;			/*<New location of a dragged point*/
bool dragging = false;	/*<Indicates whether dragging is going on*/


/**Plots a point on the screen with given color and size
*/
void plot(int x, int y, int color){
	///Red color for control points
	if(color==1){
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(4.5);
	}
	///Yellow color for the curve
	else {
		glColor3f(1.0, 1.0, 0.0);
		glPointSize(2);
	}
	glBegin(GL_POINTS);
	glVertex2i(x, y);		///plotting the point
    glEnd();
}


/**Clears screen
*/
void clearScreen(){
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);	
}


/**Linear Interpolation
*/
point lerp(float t, point a, point b){
	point p;
	p.x = (1-t)*a.x + t*b.x;
	p.y = (1-t)*a.y + t*b.y;
	return p;
}


/**Implements de Casteljau's algorithm
*/
point deCasteljau(float t, point p[], int n){
	///New array is created which will have the interpolated values
	point q[n];
	for(int i=0; i<n-1; i++){
		q[i]=lerp(t, p[i], p[i+1]);
	}
	
	///Recursion stops if there are only two points
	if(n==2){
		return q[0];
	}
	return deCasteljau(t, q, n-1);		///Recursive call
}


/**Draws the curve and the control points
*/
void draw(){
	clearScreen();
	
	///Plotting the control points
	for(int i=0; i<n; i++){
		plot(points[i].x, points[i].y, 1);
	}
	
	///No need to draw curve for one or no elements
	if(n<2){
		glFlush();
		return;
	}
	///Drawing the curve
	for (float t=0; t<=1; t+=0.0002){
		point p = deCasteljau(t, points, n);
		plot(p.x, p.y, 2);
	}
	glFlush();
}


/**Display callback function
*/
void display(){
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
}


/**Checks if the cursor is near a control point.
*/
int nearTo(int x, int y){
	for(int i=0; i<n; i++){
		if(abs(x-points[i].x)<=2 && abs(y-points[i].y)<=2){
			return i;										///Returns the index of the point near to the cursor
		}
	}
	return -1;
}


/**Keyboard callback function
*/
void keyboard(unsigned char key, int x, int y){
	///key represents the key pressed.
	if(key=='c'){
		cout<<"Clearing screen"<<endl;
		n = 0;							///Makes size zero
		clearScreen();				
		glFlush();
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
}


/**Mouse callback function
*/
void mouse(int button, int state, int x, int y){
	///button is the mouse button clicked
	///state represents if the button is pressed or released
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		int index = nearTo(x,y);
		if(index==-1){
			///New point added to the control points array
			point p;
			p.x=x;
			p.y=y;
			points[n++]=p;
			cout<<"Plotting ("<<x<<","<<y<<")\n";
		} 
		else {					
			cout<<"Dragging\n";
			draggedTo = index;			///stores the index which is to be changed
			dragging = true;			///indicates that dragging is happening
		}
	}
	
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
		if(dragging){				
			///new coordinates of the point
			points[draggedTo].x = x;	
			points[draggedTo].y = y;
			dragging = false;			///dragging stops
			cout<<"Dragged to ("<<x<<","<<y<<")\n";
		}
	}
	
	///Deleting on right click
	else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		int index = nearTo(x,y);
		if(index!=-1){
			cout<<"Deleting ("<<points[index].x<<","<<points[index].y<<")\n";
			///shifting the elements to left to fill up the space
			for(int i=index; i<n-1; i++){
				points[i].x = points[i+1].x;
				points[i].y = points[i+1].y;
			}
			n--;								///reducing size
		}
	}
	
}


/**Callback function for passive movement of the mouse
*/
void passiveMotion(int x, int y){
	int index = nearTo(x,y);
	if(index==-1)
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	else										///cursor is near a control point			
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}


void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	///Display Mode
	glutInitWindowPosition(0, 0);					///Initialises the start position on the laptop screen
	glutInitWindowSize(700, 500);					///Initialises window size
	glutCreateWindow("Bezier Curve");
	gluOrtho2D(0, 700, 500, 0);						///This is 2D Orthographic view
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);			
	clearScreen();
}


int main(int argc, char** argv) {
	cout<<"Press 'c' to clear the screen.\n";
	
	glutInit(&argc, argv);            			///Initialize GLUT
	init();	
	
	///Registering the event handler callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	clearScreen();
	glutMainLoop();			///Control goes into the event processing loop
}
