#include <GL/glut.h>

/** @brief The Taj Mahal structure drawn using OpenGL commands.
*/
class tajMahal {
	private:
		int x,y,z;		/**<positons x,y,z*/
	public:
		/**This function draws a cornor wall
		*/
		void draw_cornerWindow(float x);
		/**This function draws a window
		*/
		void draw_window(float x);	
		/**This function draws the exterior portion of tajmahal
		*/
		void draw_ext(float x);
		/** Draws dome of the Taj
		*/	
		void draw_dome();
		/**This function draws a side pillar
		*/
		void draw_cornorPillars();
		/**This function draws necessary fills and some extra decorations 
		*/
		void draw_fill1();
		/**Calls functions for drawing the primitives required for drawing the Taj.
		*/
		void draw_Taj();
};
