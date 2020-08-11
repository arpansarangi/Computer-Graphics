#include <bits/stdc++.h>
#include "bresenham.h"
#include "tree.h"
#include <GL/glut.h>

using namespace std;

int minSep=60;

void join2Nodes(int x1, int y1, int x2, int y2, int r){

    float xl, xr, yl, yr;

    //Distance between two nodes.
    float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    //Locate Perimeter point of node to draw line from.
    xl = x1 + r*(x2-x1)/dist;
    yl = y1 + r*(y2-y1)/dist;

    xr = x2 + r*(x1-x2)/dist;
    yr = y2 + r*(y1-y2)/dist;

	//Draw line.
	bresenhamLine(xl, yl, xr, yr);
}


void setup(node* t, int level, extreme &rMost, extreme &lMost){
	node *l=NULL, *r=NULL; //left and right sons
	extreme lr, ll, rr, rl; //lr is the rightmost node on the lowest level of left subtree and so on
	int curSep, rootSep, lOffSum, rOffSum; //separation of current level,current separation at node t
	
	if (t==NULL){	//Avoid selecting as extreme
		lMost.lev=-1;
		rMost.lev=-1;
	} else {
		t->yCoord=level;
		l=t->lLink; //follows contour of left subtree
		r=t->rLink;	//follows contour of right subtree
		setup (l, level+1, lr, ll); //positions subtrees recursively
		setup (r, level+1, rr, rl);
		if (r==NULL && l==NULL){ //leaf
			rMost.addr=t;
			lMost.addr=t;
			rMost.lev=level;
			lMost.lev=level;
			rMost.off=0;
			lMost.off=0;
			t->offSet=0;
		} else {  //t is not a leaf
			//Set up sub tree pushing. placeroots of subtrees minimum distance apart
			curSep=minSep;
			rootSep=minSep;
			lOffSum=0;
			rOffSum=0;
			//Now consider achlevel in turn until one subtree is exhausted, pushing the subtrees apart when necessary
			while (l!=NULL && r!=NULL){
				if (curSep<minSep){	//push
					rootSep+=(minSep-curSep);
					curSep=minSep;
				}
				//Advance l & r
				if (l->rLink!=NULL){
					lOffSum+=l->offSet;
					curSep-=l->offSet;
					l=l->rLink;					
				} else {
					lOffSum-=l->offSet;
					curSep+=l->offSet;
					l=l->lLink;
				}
				if (r->lLink!=NULL){
					rOffSum-=r->offSet;
					curSep-=r->offSet;
					r=r->lLink;
				} else {
					rOffSum+=r->offSet;
					curSep+=r->offSet;
					r=r->rLink;
				}				
			}
			//Set the offset in node t and include it inn accumulated offsets for l and r
			t->offSet=(rootSep+1)/2;
			lOffSum-=t->offSet;
			rOffSum+=t->offSet;
			//update extreme desendents information
			if (rl.lev>ll.lev || t->lLink==NULL){
				lMost=rl;
				lMost.off+=t->offSet;
			} else {
				lMost=ll;
				lMost.off-=t->offSet;
			}
			if (lr.lev>rr.lev || t->rLink==NULL){
				rMost=lr;
				rMost.off-=t->offSet;
			} else {
				rMost=rr;
				rMost.off+=t->offSet;
			}
			//if subtrees of t were of uneven heights, checkto see if threading is necessary. At most 1 thread needs to be inserted
			if (l!=NULL && l!=t->lLink){
				rr.addr->thread=true;
				rr.addr->offSet=abs((rr.off+t->offSet)-lOffSum);
				if (lOffSum-t->offSet <= rr.off){
					rr.addr->lLink=l;
				} else {
					rr.addr->rLink=l;
				}
			} else if (r!=NULL && r!=t->rLink){
				ll.addr->thread=true;
				ll.addr->offSet=abs((ll.off+t->offSet)-rOffSum);
				if (rOffSum+t->offSet >= ll.off){
					ll.addr->rLink=r;
				} else {
					ll.addr->lLink=r;
				}
			}
		}
	}
}


void petrify(node *t, int xPos) {
    if(t != NULL){
        t->xCoord=xPos;
        if(t->thread) {
            t->thread=false;
            t->rLink=NULL; // threaded node must be a leaf
            t->lLink=NULL;
        }
        petrify(t->lLink, xPos - t->offSet);
        petrify(t->rLink, xPos + t->offSet);
    }
}


void drawTree(node *n, int cx=0, int cy=0){
	int dx = (n->xCoord);
	int dy = (n->yCoord)*(-70)+400; //adjustments to get the nodes at appropriate height
	if (cx == 0 && cy == 0){ //initial call to the function (node)
		cx = dx;
		cy = dy;
	}
	if (n->lLink != NULL) //draw the left subtree 
		drawTree(n->lLink, dx, dy);
	if (n->rLink != NULL) //draw the root -> rlink subtree
		drawTree(n->rLink, dx, dy);	
	bresenhamCircle(dx,dy,10);
	join2Nodes(dx, dy, cx, cy,10); //it calls bresenham line function
	cout<<n->m<<endl; 	
}


void virtualiseTree (node *n, int cur, int size, int a[]){
	if(a[cur]==0){	// node is not present
		return;
	} else {
		int check=2*cur+1;	/*<left child*/
		if(check>size-1 ){	//check for size
			return;
		} else if(a[check]){
			//creation of left node
			node *nl=new node;
			nl->lLink=NULL;
			nl->rLink=NULL;			
			n->lLink=nl;	
			virtualiseTree(nl,check,size,a);	//virtualising left subtree
		}
		if(check+1>size-1){	//check for size
			return;
		} else if(a[check+1]){
			//creation of right node
			node *nr=new node;
			nr->lLink=NULL;
			nr->rLink=NULL;
			n->rLink=nr;
			virtualiseTree(nr,check+1,size,a);	//virtualising right subtree
		}	
	}
}

