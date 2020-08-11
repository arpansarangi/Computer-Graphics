#include <GL/glut.h>
#include <iostream>
#include <string> 
#include <vector>
#include <fstream>	///for file handling
#include <sstream>	///for splitting and parsing strings
#include "tree.h"
using namespace std;

float mycolr [11][4] = {		/**<arrays for colors*/
	{1.0,0.0,0.0,1.0},//red-0
	{0.0,1.0,0.0,1.0},//green-1
	{0.0,0.0,1.0,1.0},//blue-2
	{1.0,1.0,1.0,1.0},//white-3
	{0.0,0.0,0.0,1.0}, //black-4
	{1.0,0.65,0.0,1.0},//orange-5
	{0.6,0.6,0.6,1.0}, //gray-6
	{1,1,0,1},//yellow-7
	{0.1,1,0.1,1},
	{0,0.39,0,1},
	{0,0.467,0.745}// waterblue
};

vector<vector<float> > vertices;	/**<vertices of the faces in the Wavefront(.obj) file*/
vector<int> indices; 			/**<indices of the vertices of the triangulated faces*/

int Tree::stoi(string s){		
	stringstream stream(s); 	///This uses a stream buffer
	int x = 0; 
	stream >> x; 			///Integer fetched from the buffer
	return x;
}

float Tree::stof(string s){
	stringstream stream(s); 
	float x = 0; 
	stream >> x; 
	return x;
}

void Tree::draw_sidetrees(){
/// draw_tree() is called at the appropriate positions
	draw_tree(0.3,-0.3,0.9);
	draw_tree(-0.3,-0.3,0.9);
	draw_tree(0.3,-0.3,1.1);
	draw_tree(-0.3,-0.3,1.1);
	draw_tree(0.3,-0.3,1.3);
	draw_tree(-0.3,-0.3,1.3);
	draw_tree(0.3,-0.3,1.5);
	draw_tree(-0.3,-0.3,1.5);
	draw_tree(0.6,-0.3,0.9);
	draw_tree(-0.6,-0.3,0.9);
	draw_tree(0.6,-0.3,1.1);
	draw_tree(-0.6,-0.3,1.1);
	draw_tree(0.6,-0.3,1.3);
	draw_tree(-0.6,-0.3,1.3);
	draw_tree(0.6,-0.3,1.5);
	draw_tree(-0.6,-0.3,1.5);
	
}

void Tree::draw(){
	glPushMatrix();
	draw_sidetrees();
	glRotatef(90,0,1,0);		///Rotation such that draw_sidetrees() is drawn at the next side of Taj Mahal
	draw_sidetrees();
	glRotatef(90,0,1,0);
	draw_sidetrees();
	glRotatef(90,0,1,0);
	draw_sidetrees();
	glPopMatrix();
	
}

void Tree::draw_tree(float x, float y, float z){
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolr[1]);	///set green color
	glTranslatef(x,y,z);
	glScalef(0.05,0.05,0.05);
	///The following code draws the triangulated faces by drawing a polygon using the appropriate vertices.
	///Each face has three vertices, so we traverse through the indices array increasing our variable three at a time.
	int size = indices.size()/3;	/**<number of faces*/
	for(int i=0; i<size; i+=3){
		glBegin(GL_POLYGON);
		///Coordinates are given appropriately.
		glVertex3f(vertices[indices[i]][0],vertices[indices[i]][1],vertices[indices[i]][2]);
		glVertex3f(vertices[indices[i+1]][0],vertices[indices[i+1]][1],vertices[indices[i+1]][2]);
		glVertex3f(vertices[indices[i+2]][0],vertices[indices[i+2]][1],vertices[indices[i+2]][2]);
		glEnd();
	}
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolr[9]);	///Set a different shade of green for other two trees
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.05,0.05,0.05);
	glRotatef(10,0,1,0);
	size = indices.size()/3;
	for(int i=0; i<size; i+=3){
		glBegin(GL_POLYGON);
		glVertex3f(vertices[indices[i]][0],vertices[indices[i]][1],vertices[indices[i]][2]);
		glVertex3f(vertices[indices[i+1]][0],vertices[indices[i+1]][1],vertices[indices[i+1]][2]);
		glVertex3f(vertices[indices[i+2]][0],vertices[indices[i+2]][1],vertices[indices[i+2]][2]);
		glEnd();
	}
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mycolr[9]);
		glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.05,0.05,0.05);
	glRotatef(30,0,1,0);
	size = indices.size()/3;
	for(int i=0; i<size; i+=3){
		glBegin(GL_POLYGON);
		glVertex3f(vertices[indices[i]][0],vertices[indices[i]][1],vertices[indices[i]][2]);
		glVertex3f(vertices[indices[i+1]][0],vertices[indices[i+1]][1],vertices[indices[i+1]][2]);
		glVertex3f(vertices[indices[i+2]][0],vertices[indices[i+2]][1],vertices[indices[i+2]][2]);
		glEnd();
	}
	glPopMatrix();
}

void Tree::loadModel(){
	ifstream fin;
	fin.open("tree2final.obj");	///Wavefront(.obj) file opened
	if(!fin){				///Checking if the file exists
		cout<<"file not found\n";
		return;
	}
	
	int nAsize;		/**<Size of the vertices array*/
	string str;		/**<Line to be scanned*/
	while(true){
		string line;
		vector<string> result;
		getline(fin,str);
		///The line is split into parts with space as a delimiter.
		stringstream data(str);
		while(getline(data,line,' ')){
			result.push_back(line);
		}

		if(result[0]=="v"){		///If result[0] is "v", the line has data about a vertex.
			vector<float> v(3);	///The coordinates of the vertex are parsed and it is pushed into the vertices vector.
			v[0]=stof(result[1]);
			v[1]=stof(result[2]);
			v[2]=stof(result[3]);
			vertices.push_back(v);
			nAsize++;
		}

		else if(result[0]=="f"){	///If result[0] is "f", the line has indices of the vertices making a face.
			nAsize*=3;
			break;
		}
	}

	while(fin){	
		string line;
		vector<string> result;
		stringstream data(str);
		while(getline(data,line,' ')){
			result.push_back(line);
		}
		if(result[0]!="f"){		///Once the first element is not "f", we break out of the loop.
			getline(fin,str);
			continue;
		}
		vector<string> vertex1,vertex2,vertex3;
		string line1,line2,line3;
		///The elements of result[] are split with '/' delimiter and the elements are stored in vertex1, vertex2 and vertex3.
		stringstream data1(result[1]);
		while(getline(data1,line1,'/')){
			vertex1.push_back(line1);
		}
		stringstream data2(result[2]);
		while(getline(data2,line2,'/')){
			vertex2.push_back(line2);
		}
		stringstream data3(result[3]);
		while(getline(data3,line3,'/')){
			vertex3.push_back(line3);
		}
		///The first element of vertex 1 denotes the index of the vertex in the vertices array.
		///These indices follow 1-indexing. But our vectors follow 0-indexing. Hence 1 is subtracted.
		int currVertexIndex = stoi(vertex1[0])-1;	/**<current index of the vertex in the vertices array*/
		indices.push_back(currVertexIndex);
		currVertexIndex = stoi(vertex2[0])-1;
		indices.push_back(currVertexIndex);
		currVertexIndex = stoi(vertex3[0])-1;
		indices.push_back(currVertexIndex);

		getline(fin,str);		///Fetching next line from the file.
	}
	
	fin.close();
}
