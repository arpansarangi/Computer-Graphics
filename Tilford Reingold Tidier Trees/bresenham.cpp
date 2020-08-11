#include <bits/stdc++.h>
#include "bresenham.h"
#include <GL/glut.h>

using namespace std;


void bresenhamLine(int x1, int y1, int x2, int y2) {
	int dy = abs(y2-y1); 
	int dx = abs(x2-x1);
	int x, y;
	int d; /*<decision variable*/
	int incrE, incrNE; /*<increments in the decision variable according to the chosen points */
	int x_dir, y_dir;
	
	/** Whether to increment or decrement x and y
	*/
	x_dir = (x2 > x1) ? 1 : -1;
	y_dir = (y2 > y1) ? 1 : -1;

	if (dy <= dx) {	// |slope| <= 1, scan column-wise
		d = 2*dy - dx;
		incrE = 2 * dy;
		incrNE = 2 * (dy - dx);
	    x = x1; y = y1;
		for(int i=1;i <= dx; i++) {
			if(d <= 0) {	// Line goes below the midpoint 
                d += incrE; // E is selected
			}
 	        else {	//// Line goes above the midpoint 
				d += incrNE;	//NE is selected
				y = y+y_dir;
	        }

			glBegin(GL_POINTS);
			glVertex2i(x, y);
	        glEnd();
	        x = x + x_dir;
		}
	}
	else {	// |slope| >= 1, scan row-wise
		d = 2*dx - dy;
		incrE = 2 * dx;
		incrNE = 2 * (dx - dy);
		y = y1; x = x1;
		for (int i=0; i < dy; i++) {
			if (d < 0) {
				d += incrE;
			}
            else {
				d += incrNE;
				x = x + x_dir;
			}
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
	       	y = y + y_dir;
		}
	}
}


void pointsOfSym(int x, int y, int xc, int yc) {
	// xc and yc denote coordinates of the centre of the circle
	glBegin(GL_POINTS);
	    glVertex2i(x+xc,y+yc);
	    glVertex2i(-x+xc,y+yc);
	    glVertex2i(x+xc,-y+yc);
	    glVertex2i(-x+xc,-y+yc);
	    glVertex2i(y+xc,x+yc);
	    glVertex2i(-y+xc,x+yc);
	    glVertex2i(y+xc,-x+yc);
	    glVertex2i(-y+xc,-x+yc);
	glEnd();
}


void bresenhamCircle(int xc, int yc, int r)
{
	///Scan conversion starts at top most point of the circle.
	int x = 0, y = r;                       /// coordinates assuming centre at (0,0)
	int d = 1-r;                            /*<decision variable*/
	int deltaE = 3, deltaSE = -2 * r + 5;   /// used for updation of decision variable -'d'.


	///Plot the first point
	pointsOfSym(x, y, xc, yc);

	while(y > x)
	{
		if(d < 0)			                /// If d < 0, East coordinate is to be selected.
		{
			d += deltaE;
			deltaE += 2;
			deltaSE += 2; 	
		}
		else
		{
			d += deltaSE;                   /// South-East coordinate is selected.
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		pointsOfSym(x, y, xc, yc);             ///Plot the symmetrical points
	}
}

