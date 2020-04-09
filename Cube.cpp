#include "Cube.h"

// Cube * rubikCube[3][3][3];

GLfloat _animateX = 0.0f;
GLfloat _animateY = 0.0f;
GLfloat _animateZ = 0.0f;

Cube::Cube() {
	inside[3] = {0};
	outside[3] = {0};
	top[3] = {0};
	bottom[3] = {0};
	right[3] = {0};
	left[3] = {0};
	animating = false;
}

void Cube::drawCube(Cube * cube) {
	glBegin(GL_QUADS);

    //All vertices are commented with viewer at center of cube

    //Towards Inside
	glColor3ubv(cube->inside);
	glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(padding - cubeSize, padding - cubeSize, padding - cubeSize);	//Bottom left
    glVertex3f(padding - cubeSize, cubeSize - padding, padding - cubeSize);	//Top left
    glVertex3f(cubeSize - padding, cubeSize - padding, padding - cubeSize);	//Top right
    glVertex3f(cubeSize - padding, padding - cubeSize, padding - cubeSize);	//Bottom right

    //Towards Outside
    glColor3ubv(cube->outside);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(cubeSize - padding, padding - cubeSize, cubeSize - padding);	//Bottom left
    glVertex3f(cubeSize - padding, cubeSize - padding, cubeSize - padding);	//Top left
    glVertex3f(padding - cubeSize, cubeSize - padding, cubeSize - padding);	//Top right
    glVertex3f(padding - cubeSize, padding - cubeSize, cubeSize - padding);	//Bottom right
    
    //Right
    glColor3ubv(cube->right);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(cubeSize - padding, padding - cubeSize, padding - cubeSize);	//Bottom left
    glVertex3f(cubeSize - padding, cubeSize - padding, padding - cubeSize);	//Top left
    glVertex3f(cubeSize - padding, cubeSize - padding, cubeSize - padding);	//Top right
    glVertex3f(cubeSize - padding, padding - cubeSize, cubeSize - padding);	//Bottom right

    //Left
    glColor3ubv(cube->left);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(padding - cubeSize, padding - cubeSize, cubeSize - padding);	//Bottom left
    glVertex3f(padding - cubeSize, cubeSize - padding, cubeSize - padding);	//Top left
    glVertex3f(padding - cubeSize, cubeSize - padding, padding - cubeSize);	//Top right
    glVertex3f(padding - cubeSize, padding - cubeSize, padding - cubeSize);	//Bottom right

    //Top
    glColor3ubv(cube->top);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(padding - cubeSize, cubeSize - padding, padding - cubeSize);	//Bottom left
    glVertex3f(padding - cubeSize, cubeSize - padding, cubeSize - padding);	//Top left
    glVertex3f(cubeSize - padding, cubeSize - padding, cubeSize - padding);	//Top right
    glVertex3f(cubeSize - padding, cubeSize - padding, padding - cubeSize);	//Bottom right

    //Bottom
    glColor3ubv(cube->bottom);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(padding - cubeSize, padding - cubeSize, cubeSize - padding);	//Bottom left
    glVertex3f(padding - cubeSize, padding - cubeSize, padding - cubeSize);	//Top left
    glVertex3f(cubeSize - padding, padding - cubeSize, padding - cubeSize);	//Top right
    glVertex3f(cubeSize - padding, padding - cubeSize, cubeSize - padding);	//Bottom right

    glEnd();
}

void Cube::drawCube(Cube * cube, GLfloat centerX, GLfloat centerY, GLfloat centerZ) {
	glPushMatrix();
	if(cube->animating) {
		glRotatef(_animateX, 1.0f, 0.0f, 0.0f);
		glRotatef(_animateY, 0.0f, 1.0f, 0.0f);
		glRotatef(_animateZ, 0.0f, 0.0f, 1.0f);
	}
	glTranslatef(centerX, centerY, centerZ);
	drawCube(cube);
	glPopMatrix();
}

void Cube::drawRubikCube() {
	drawCube(rubikCube[1][1][1], 0.0f,0.0f,0.0f);	//Center
    drawCube(rubikCube[0][2][1], -2*cubeSize,2*cubeSize,0);	//Left Top
    drawCube(rubikCube[0][1][1], -2*cubeSize,0,0);	//Left center
    drawCube(rubikCube[0][0][1], -2*cubeSize,-2*cubeSize,0);	//Left bottom
    drawCube(rubikCube[1][0][1], 0,-2*cubeSize,0);	//Center Bottom
    drawCube(rubikCube[2][0][1], 2*cubeSize,-2*cubeSize,0);	//Right bottom
    drawCube(rubikCube[2][1][1], 2*cubeSize,0,0);	//Right Center
    drawCube(rubikCube[2][2][1], 2*cubeSize,2*cubeSize,0);	//Right Top
    drawCube(rubikCube[1][2][1], 0,2*cubeSize,0);	//Center Top

    //Outside plane of Z-axis
    drawCube(rubikCube[1][1][2], 0,0,2*cubeSize);	//Center
    drawCube(rubikCube[0][2][2], -2*cubeSize,2*cubeSize,2*cubeSize);	//Left Top
    drawCube(rubikCube[0][1][2], -2*cubeSize,0,2*cubeSize);	//Left center
    drawCube(rubikCube[0][0][2], -2*cubeSize,-2*cubeSize,2*cubeSize);	//Left bottom
    drawCube(rubikCube[1][0][2], 0,-2*cubeSize,2*cubeSize);	//Center Bottom
    drawCube(rubikCube[2][0][2], 2*cubeSize,-2*cubeSize,2*cubeSize);	//Right bottom
    drawCube(rubikCube[2][1][2], 2*cubeSize,0,2*cubeSize);	//Right Center
    drawCube(rubikCube[2][2][2], 2*cubeSize,2*cubeSize,2*cubeSize);	//Right Top
    drawCube(rubikCube[1][2][2], 0,2*cubeSize,2*cubeSize);	//Center Top

    //Inside plane of Z-axis
    drawCube(rubikCube[1][1][0], 0,0,-2*cubeSize);	//Center
    drawCube(rubikCube[0][2][0], -2*cubeSize,2*cubeSize,-2*cubeSize);	//Left Top
    drawCube(rubikCube[0][1][0], -2*cubeSize,0,-2*cubeSize);	//Left center
    drawCube(rubikCube[0][0][0], -2*cubeSize,-2*cubeSize,-2*cubeSize);	//Left bottom
    drawCube(rubikCube[1][0][0], 0,-2*cubeSize,-2*cubeSize);	//Center Bottom
    drawCube(rubikCube[2][0][0], 2*cubeSize,-2*cubeSize,-2*cubeSize);	//Right bottom
    drawCube(rubikCube[2][1][0], 2*cubeSize,0,-2*cubeSize);	//Right Center
    drawCube(rubikCube[2][2][0], 2*cubeSize,2*cubeSize,-2*cubeSize);	//Right Top
    drawCube(rubikCube[1][2][0], 0,2*cubeSize,-2*cubeSize);	//Center Top
}

void Cube::setColors() {
	//Inside
	for(int x = 0;x < 3;x++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[x][y][0]->inside[0] = 0;
			rubikCube[x][y][0]->inside[1] = 0;
			rubikCube[x][y][0]->inside[2] = 255;
		}
	}

	//Outside
	for(int x = 0;x < 3;x++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[x][y][2]->outside[0] = 0;
			rubikCube[x][y][2]->outside[1] = 128;
			rubikCube[x][y][2]->outside[2] = 0;
		}
	}

	//Left
	for(int z = 0;z < 3;z++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[0][y][z]->left[0] = 255;
			rubikCube[0][y][z]->left[1] = 165;
			rubikCube[0][y][z]->left[2] = 0;
		}
	}

	//Right
	for(int z = 0;z < 3;z++) {
		for(int y = 0;y < 3;y++) {
			rubikCube[2][y][z]->right[0] = 255;
			rubikCube[2][y][z]->right[1] = 0;
			rubikCube[2][y][z]->right[2] = 0;
		}
	}

	//Top
	for(int x = 0;x < 3;x++) {
		for(int z = 0;z < 3;z++) {
			rubikCube[x][2][z]->top[0] = 255;
			rubikCube[x][2][z]->top[1] = 255;
			rubikCube[x][2][z]->top[2] = 255;
		}
	}
	//Bottom
	for(int x = 0;x < 3;x++) {
		for(int z = 0;z < 3;z++) {
			rubikCube[x][0][z]->bottom[0] = 255;
			rubikCube[x][0][z]->bottom[1] = 255;
			rubikCube[x][0][z]->bottom[2] = 0;
		}
	}
}

void Cube::initRubikCube() {
	//Allocate memory for the cube
	for(int x = 0;x < 3;x++) {
		for(int y = 0;y < 3;y++) {
			for(int z = 0;z < 3;z++) {
				rubikCube[x][y][z] = new Cube();
			}
		}
	}
	setColors();
}