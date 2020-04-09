/*
*
* To compile:
*   g++ RubikCube.cpp -lglut -lGL -lGLU
*
*/

//Includes
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include<vector>
#include <algorithm>
#include <iterator>
#include "Cube.h"

//Defines

#define rotationSpeed 2.0f

using namespace std;

void drawScene();

//Rotation variables
float _angleX = 0.0f;
float _angleY = 0.0f;
float _angleZ = 0.0f;

//Translation variables
float translateX = 0.0f;
float translateY = 0.0f;
float translateZ = -20.0f;

//Animation variables
GLfloat _animateX = 0.0f;
GLfloat _animateY = 0.0f;
GLfloat _animateZ = 0.0f;


void rotateAboutX(bool clockwise, int pos) {
	//Set animation flag
	for(int z = 0;z < 3;z++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[pos][y][z]->animating = true;
		}
	}
		//Animate
	while(_animateX < 90.0f && _animateX > -90.0f) {
		_animateX += clockwise ? rotationSpeed : (-rotationSpeed);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		drawScene();
	}

		//Reset animation flag
	for(int z = 0;z < 3;z++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[pos][y][z]->animating = false;
		}
	}

	_animateX = 0.0f;	//Reset animation progress angle

	//Storing new config
	//Rotate Matrice (2D)
	//Rotate step 1: Transpose matrix
	for(int y = 0;y < 3;y++) {
		for(int z = y+1;z < 3;z++) {
			Cube * temp = rubikCube[pos][y][z];
			rubikCube[pos][y][z] = rubikCube[pos][z][y];
			rubikCube[pos][z][y] = temp;
		}
	}
	//Rotate step 2: Reverse column or rows (depending on clockwise or anti-clockwise)
	if(clockwise) {
		for(int z = 0;z < 3;z++) {
			Cube * temp = rubikCube[pos][0][z];
			rubikCube[pos][0][z] = rubikCube[pos][2][z];
			rubikCube[pos][2][z] = temp;
		}
		for(int z = 0;z < 3;z++) {
			for(int y = 0;y < 3;y++) {
				GLbyte arr[3];
				copy(rubikCube[pos][y][z]->top, rubikCube[pos][y][z]->top + 3, arr);
				copy(rubikCube[pos][y][z]->inside, rubikCube[pos][y][z]->inside + 3, rubikCube[pos][y][z]->top);
				copy(rubikCube[pos][y][z]->bottom, rubikCube[pos][y][z]->bottom + 3, rubikCube[pos][y][z]->inside);
				copy(rubikCube[pos][y][z]->outside, rubikCube[pos][y][z]->outside + 3, rubikCube[pos][y][z]->bottom);
				copy(arr, arr + 3, rubikCube[pos][y][z]->outside);
			}		
		}
	} else {
		for(int y = 0;y < 3;y++) {
			Cube * temp = rubikCube[pos][y][0];
			rubikCube[pos][y][0] = rubikCube[pos][y][2];
			rubikCube[pos][y][2] = temp;
		}
		for(int z = 0;z < 3;z++) {
			for(int y = 0;y < 3;y++) {
				GLbyte arr[3];
				copy(rubikCube[pos][y][z]->top, rubikCube[pos][y][z]->top + 3, arr);
				copy(rubikCube[pos][y][z]->outside, rubikCube[pos][y][z]->outside + 3, rubikCube[pos][y][z]->top);
				copy(rubikCube[pos][y][z]->bottom, rubikCube[pos][y][z]->bottom + 3, rubikCube[pos][y][z]->outside);
				copy(rubikCube[pos][y][z]->inside, rubikCube[pos][y][z]->inside + 3, rubikCube[pos][y][z]->bottom);
				copy(arr, arr + 3, rubikCube[pos][y][z]->inside);
			}
		}
	}
}

void rotateAboutY(bool clockwise, int pos) {
	//Set animation flag
	for(int z = 0;z < 3;z++) {
		for(int x = 0;x < 3;x++) {
			rubikCube[x][pos][z]->animating = true;
		}
	}
		//Animate
	while(_animateY < 90.0f && _animateY > -90.0f) {
		_animateY += clockwise ? rotationSpeed : (-rotationSpeed);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		drawScene();
	}

		//Reset animation flag
	for(int z = 0;z < 3;z++) {
		for(int x = 0;x < 3;x++) {
			rubikCube[x][pos][z]->animating = false;
		}
	}

	_animateY = 0.0f;	//Reset animation progress angle

	//Storing new config
	//Rotate Matrice (2D)
	//Rotate step 1: Transpose matrix
	for(int x = 0;x < 3;x++) {
		for(int z = x+1;z < 3;z++) {
			Cube * temp = rubikCube[x][pos][z];
			rubikCube[x][pos][z] = rubikCube[z][pos][x];
			rubikCube[z][pos][x] = temp;
		}
	}
	//Rotate step 2: Reverse column or rows (depending on clockwise or anti-clockwise)
	if(clockwise) {
		for(int x = 0;x < 3;x++) {
			Cube * temp = rubikCube[x][pos][0];
			rubikCube[x][pos][0] = rubikCube[x][pos][2];
			rubikCube[x][pos][2] = temp;
		}
		for(int z = 0;z < 3;z++) {
			for(int x = 0;x < 3;x++) {
				GLbyte arr[3];
				copy(rubikCube[x][pos][z]->left, rubikCube[x][pos][z]->left + 3, arr);
				copy(rubikCube[x][pos][z]->inside, rubikCube[x][pos][z]->inside + 3, rubikCube[x][pos][z]->left);
				copy(rubikCube[x][pos][z]->right, rubikCube[x][pos][z]->right + 3, rubikCube[x][pos][z]->inside);
				copy(rubikCube[x][pos][z]->outside, rubikCube[x][pos][z]->outside + 3, rubikCube[x][pos][z]->right);
				copy(arr, arr + 3, rubikCube[x][pos][z]->outside);
			}		
		}
	} else {
		for(int z = 0;z < 3;z++) {
			Cube * temp = rubikCube[0][pos][z];
			rubikCube[0][pos][z] = rubikCube[2][pos][z];
			rubikCube[2][pos][z] = temp;
		}
		for(int z = 0;z < 3;z++) {
			for(int x = 0;x < 3;x++) {
				GLbyte arr[3];
				copy(rubikCube[x][pos][z]->left, rubikCube[x][pos][z]->left + 3, arr);
				copy(rubikCube[x][pos][z]->outside, rubikCube[x][pos][z]->outside + 3, rubikCube[x][pos][z]->left);
				copy(rubikCube[x][pos][z]->right, rubikCube[x][pos][z]->right + 3, rubikCube[x][pos][z]->outside);
				copy(rubikCube[x][pos][z]->inside, rubikCube[x][pos][z]->inside + 3, rubikCube[x][pos][z]->right);
				copy(arr, arr + 3, rubikCube[x][pos][z]->inside);
			}
		}
	}
}


void rotateAboutZ(bool clockwise, int pos) {
	//Set animation flag
	for(int x = 0;x < 3;x++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[x][y][pos]->animating = true;
		}
	}
		//Animate
	while(_animateZ < 90.0f && _animateZ > -90.0f) {
		_animateZ += clockwise ? rotationSpeed : (-rotationSpeed);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		drawScene();
	}

		//Reset animation flag
	for(int x = 0;x < 3;x++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[x][y][pos]->animating = false;
		}
	}

	_animateZ = 0.0f;	//Reset animation progress angle

	//Storing new config
	//Rotate Matrice (2D)
	//Rotate step 1: Transpose matrix
	for(int y = 0;y < 3;y++) {
		for(int x = y+1;x < 3;x++) {
			Cube * temp = rubikCube[x][y][pos];
			rubikCube[x][y][pos] = rubikCube[y][x][pos];
			rubikCube[y][x][pos] = temp;
		}
	}
	//Rotate step 2: Reverse column or rows (depending on clockwise or anti-clockwise)
	if(clockwise) {
		for(int y = 0;y < 3;y++) {
			Cube * temp = rubikCube[0][y][pos];
			rubikCube[0][y][pos] = rubikCube[2][y][pos];
			rubikCube[2][y][pos] = temp;
		}
		for(int x = 0;x < 3;x++) {
			for(int y = 0;y < 3;y++) {
				GLbyte arr[3];
				copy(rubikCube[x][y][pos]->top, rubikCube[x][y][pos]->top + 3, arr);
				copy(rubikCube[x][y][pos]->right, rubikCube[x][y][pos]->right + 3, rubikCube[x][y][pos]->top);
				copy(rubikCube[x][y][pos]->bottom, rubikCube[x][y][pos]->bottom + 3, rubikCube[x][y][pos]->right);
				copy(rubikCube[x][y][pos]->left, rubikCube[x][y][pos]->left + 3, rubikCube[x][y][pos]->bottom);
				copy(arr, arr + 3, rubikCube[x][y][pos]->left);
			}		
		}
	} else {
		for(int x = 0;x < 3;x++) {
			Cube * temp = rubikCube[x][0][pos];
			rubikCube[x][0][pos] = rubikCube[x][2][pos];
			rubikCube[x][2][pos] = temp;
		}
		for(int x = 0;x < 3;x++) {
			for(int y = 0;y < 3;y++) {
				GLbyte arr[3];
				copy(rubikCube[x][y][pos]->top, rubikCube[x][y][pos]->top + 3, arr);
				copy(rubikCube[x][y][pos]->left, rubikCube[x][y][pos]->left + 3, rubikCube[x][y][pos]->top);
				copy(rubikCube[x][y][pos]->bottom, rubikCube[x][y][pos]->bottom + 3, rubikCube[x][y][pos]->left);
				copy(rubikCube[x][y][pos]->right, rubikCube[x][y][pos]->right + 3, rubikCube[x][y][pos]->bottom);
				copy(arr, arr + 3, rubikCube[x][y][pos]->right);
			}
		}
	}
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
        case 27: //Escape key
        exit(0);

        //Translation with char keys (arrow keys in separate function below)
        case 'i':                   //Scene moves down (Y-axis)
        translateY -= 1.0f;
        break;

        case 'k':                   //Scene moves up (Y-axis)
        translateY += 1.0f;
        break;

        //Rotation (follows right hand thumb rule)
        case 'w':                   //Scene rotates about +ve X-axis
        _angleX += rotationSpeed;
        break;

        case 's':                   //Scene rotates about -ve X-axis
        _angleX -= rotationSpeed;
        break;

        case 'a':                   //Scene rotates about +ve Y-axis
        _angleY += rotationSpeed;
        break;

        case 'd':                   //Scene rotates about -ve Y-axis
	        _angleY -= rotationSpeed;
	        break;

        case 'j':                   //Scene rotates about +ve Z-axis 
	        _angleZ += rotationSpeed;
	        break;

        case 'l':                   //Scene rotates about -ve Z-axis
	        _angleZ -= rotationSpeed;
	        break;

	    /*
	     * y: yellow
	     * g: green
	     * b: Blue
	     * o: orange
	     * p: white 
	     * t: red
	     * 
	     * red and white can be changed later.
	     * Lower case ones are for clockwise rotation
	     * And upper case for anticlockwise rotation.
	     * 
	     */

	    case 'y':
	    	rotateAboutY(true, 0);
	    	break;

	    case 'Y':
	    	rotateAboutY(false, 0);
	    	break;

	    case 'g':
	    	rotateAboutZ(true, 2);
	    	break;

	    case 'G':
	    	rotateAboutZ(false, 2);
	    	break;

	   	case 'b':
	   		rotateAboutZ(true, 0);
	   		break;

	   	case 'B':
	   		rotateAboutZ(false, 0);
	   		break;

	    case 't': //for face with the red center
	    	rotateAboutX(true, 2);
	    	break;

	    case 'T':
	    	rotateAboutX(false, 2);
	    	break;

	    case 'p': //for face with the white center
	    	rotateAboutY(true, 2);
	    	break;

	    case 'P':
	    	rotateAboutY(false, 2);
	    	break;

	    case 'o':
	    	rotateAboutX(true, 0);
	    	break;

	    case 'O':
	    	rotateAboutX(false, 0);
	    	break;



        case 'r':                   //Reset Scene to initial state
        _angleX = 0.0f;
        _angleY = 0.0f;
        _angleZ = 0.0f;

        translateX = 0.0f;
        translateY = 0.0f;
        translateZ = -20.0f;
        break;

    }

    glutPostRedisplay();            //redraw scene
}

//Called when special keys are pressed
void specialInput(int key, int x, int y) {
	switch(key)
	{
        case GLUT_KEY_UP:           //Scene zooms in (Z-axis)
        translateZ += 1.0f;
        break;  
        case GLUT_KEY_DOWN:         //Scene zooms out (Z-axis)
        translateZ -= 1.0f;
        break;
        case GLUT_KEY_LEFT:         //Scene goes left (X-Axis)
        translateX -= 1.0f;
        break;
        case GLUT_KEY_RIGHT:        //Scene goes right (X-Axis)
        translateX += 1.0f;
        break;
    }

    glutPostRedisplay();
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
    //Draw away from camera initial position
	glTranslatef(0,0,-20*cubeSize);
    //Translate/Rotate the entire system (Used for scene interaction)
	glTranslatef(translateX, translateY, translateZ);
	glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);

    //Draw Rubik's cube
	drawRubikCube();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	//Initialize the rubik's cube in memory
	initRubikCube();

    //Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

    //Create the window
	glutCreateWindow("Rubik's Cube");
	initRendering();

    //Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(specialInput);
	glutReshapeFunc(handleResize);

	glutMainLoop();
}