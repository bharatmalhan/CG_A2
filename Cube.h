#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include<vector>
#include <algorithm>
#include <iterator>

#define cubeSize 5.0f	//Actual cube size is double to avoid float division
#define padding 0.1f



class Cube {
	public:

		Cube();

		GLubyte inside[3];
		GLubyte outside[3];
		GLubyte top[3];
		GLubyte bottom[3];
		GLubyte right[3];
		GLubyte left[3];
		bool animating = false;

		void drawCube(Cube * cube);
		void drawCube(Cube * cube, GLfloat centerX, GLfloat centerY, GLfloat centerZ);
		void setColors();
		void drawRubikCube();
		void initRubikCube();
};

extern Cube * rubikCube[3][3][3];

#endif