/** @brief Implementation of the TR algorithm for drawing tidier trees.

    @author Sai Rajesh BN, Arpan Sarangi, Sai Nishanth Kurra

*/
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "bresenham.h"
#include "tree.h"

using namespace std;


int choice;	/*<Stores what option user choses*/
int s[4094];	/*<Array storing if a node is present or not*/


/** Creates a random array which corresponds to subset of a full binary tree. The array element is 1 if the node is present, els it is zero.
*/
void createRandomArrayForTree(int b[]){
	int x,m=0,n=0;
	b[0]=1;
	for(int j=1; j<4094; j++){
		x=rand()%2;	
		// Biased random numbers allocation according to height
		if(x==0 and m<5 and j<7){
			m++;
			j--;
		} else if(x==0 and n<3 and j<20){
			n++;
			j--;
		} else {
			b[j]=x;
			m=n=0;
		}	
	}
}



void timer(int);	//for use of double buffers


void display();

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
}


void reshape(int,int);

int main (int argc, char** argv){
	
	cout<<"\t\tWelcome!\n";
	cout<<"Choose an option:\n";
	cout<<"1. Tic-tac-toe example\n2. Random Tree Slideshow\n3. Input a tree\n";
	g:
	cin>>choice;
	if(choice<1 or choice>3)
	{
		cout<<"Invalid choice. Enter again:";
		goto g;
	}
	if(choice==3){
		int nodes;
		cout<<"\nInput number of nodes:";
		cin>>nodes;
	    
		for(int i=0;i<4094;i++){	///Initialises every element to zero
			s[i]=0;
		}
		cout<<"\nEnter the elements\n";
		int a;
		for(int i=0;i<nodes;i++){	///Makes element one if the node is present
			cin>>a;
			s[a]=1;
		}	
	}

				
			
	glutInit(&argc,argv);//Main Initialisation
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);// Display Mode
	glutInitWindowPosition(0,0);//Initialises the start position on the laptop screen
	glutInitWindowSize(1200,700);//Initialises window size
	
	glutCreateWindow("TR Algorithm");//New window is created
	
	glutDisplayFunc(display);//where display happens
	glutReshapeFunc(reshape);//reshape happens here
	glutTimerFunc(0,timer,0);//calls a func after a specific amount of time
	init();

	
	glutMainLoop();   
}

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT); //Clears screen, i.e, makes all pixels black
	glLoadIdentity(); //Loads Identity
	
	if(choice==1){	///Draws the corresponding lines and circles for a tic-tac-toe game grid
		bresenhamLine(-175,525,-175,-525);
		bresenhamLine(175,525,175,-525);
		bresenhamLine(-525,175,525,175);
		bresenhamLine(-525,-175,525,-175);
		bresenhamLine(-450,100,-250,-100);
		bresenhamLine(-450,-100,-250,100);
		bresenhamLine(-100,450,100,250);
		bresenhamLine(-100,250,100,450);
		bresenhamLine(250,450,450,250);
		bresenhamLine(250,250,450,450);
		bresenhamLine(-100,-450,100,-250);
		bresenhamLine(-100,-250,100,-450);
		bresenhamLine(250,-250,450,-450);
		bresenhamLine(450,-250,250,-450);
		bresenhamCircle(0,0,100);
		bresenhamCircle(-350,350,100);
		bresenhamCircle(-350,-350,100);
		bresenhamCircle(350,0,100);
	}
	
	if(choice ==2){
		createRandomArrayForTree(s);
	}
    if(choice == 2 || choice == 3){
    	node *t = new node;	///Creates root of the tree
		t->lLink=NULL;
		t->rLink=NULL;
		virtualiseTree(t,0,4094,s);
		extreme rm,lm;
		setup(t,0, rm, lm);
		petrify(t,0);
		drawTree(t,0,0);
	}
	glutSwapBuffers();//Swaps buffers

}



void reshape(int w,int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h); //view port dimensions
	glMatrixMode(GL_PROJECTION);// matrix mode 
	glLoadIdentity();// identity loaded
	gluOrtho2D(-1200,1200,-700,700);//This is 2D Orthographic view
	glMatrixMode(GL_MODELVIEW);//matrix mode
}

void timer(int){
	glutPostRedisplay();// calls display function
	glutTimerFunc(1500,timer,0);//calls timer function after 1500ms

}

