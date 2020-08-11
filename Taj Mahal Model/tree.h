#include <GL/glut.h>
#include <string>
using namespace std;

/** @brief The tree structure imported from Blender
*/
class Tree{
	private:
		float x,y,z;	/**<coordinates of the tree*/
	public:
		/** Draws tree at a given position.
		*/	
		void draw_tree(float x, float y, float z);
		/** Parses a string to an integer (for versions less than C++11).
		*/
		int stoi(string s);
		/** Parses a string to a floating point value (for versions less than C++11).
		*/
		float stof(string s);
		/** Parser to get the data about vertices and faces from the Wavefront(.obj) file format.
		*/
		void loadModel();
		/** Draws trees for the four sides of the Taj Mahal. Calls draw_tree().
		*/
		void draw_sidetrees();
		/** Calls draw_sidetrees() for the four sides.
		*/
		void draw();
};
