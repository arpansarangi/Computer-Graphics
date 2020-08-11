class node{
	public:
		node *lLink, *rLink; /**<pointers to the subtrees*/
		int yCoord, xCoord; /**<coordinates of this node*/
		int offSet; /**<distance from each son*/
		bool thread; 
		int m;
};

/** @brief keeps track of the leftmost and rightmost nodes
*/
class extreme{
	public:
		node* addr; /**<address*/
		int off;  /**<offset from root of subtree*/
		int lev; /**<tree level*/
};


/** Joins two nodes with a line taking care that the line segment inside the circle is not visible.
*/	
void join2Nodes(int x1, int y1, int x2, int y2, int r);

/** Sets up the relative coordinates while doing a post-order traversal
*/	
void setup(node* t, int level, extreme &rMost, extreme &lMost);

/** Computes the final position (absolute coordinates) of each node through a preorer traversal and erases all the threads
*/	
void petrify(node *t, int xPos);

/** Draws the tree by drawing the the component circles and lines
*/	
void drawTree(node *n, int cx, int cy);

/** Converts the array input into a tre
*/	
void virtualiseTree (node *n, int cur, int size, int a[]);



