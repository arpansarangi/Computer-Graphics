/** Draws a line using Bresenham's midpoint algorithm
*/
void bresenhamLine(int x1, int y1, int x2, int y2);

/** Draws the other 7 symmetric points for each point drawn in bresenhamCircle()
*/
void pointsOfSym(int x, int y, int xc, int yc);

/** Draws a quarter of a circle using Bresenham's midpoint algorithm
*/
void bresenhamCircle(int xc, int yc, int r);
