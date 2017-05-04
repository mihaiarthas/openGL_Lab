//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 
#include <windows.h>
#include<gl/freeglut.h>
#include<math.h>
#include <iostream>

using namespace std;

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

float fractionSpeed = 0.02f;
float fraction = fractionSpeed;


enum {
	NOAPTE, ZI
};

int rendermode = NOAPTE;

void menu(int selection)
{
	rendermode = selection;
	glutPostRedisplay();
}


void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);


	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void drawTree()
{
	glColor3f(0.000, 0.392, 0.000);

	glTranslatef(5.0f, -.5f, 0.0f);
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.0f, 5.0f, 30, 20);
	glPopMatrix();

}

void keyboard()
{
	fraction = fractionSpeed;
	cout << "SPEED : " << fraction << endl;

	if (GetAsyncKeyState(65)) // A
	{
		angle -= 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if (GetAsyncKeyState(68)) // D
	{
		angle += 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if (GetAsyncKeyState(87)) // W
	{
		x += lx * fraction;
		z += lz * fraction;
	}
	if (GetAsyncKeyState(83)) // S
	{
		x -= lx * fraction;
		z -= lz * fraction;
	}

	//if (GetAsyncKeyState(75)) // K
	//{
	//	fractionSpeed += 0.01f;
	//}

	//if (GetAsyncKeyState(77)) // M
	//{
	//	fractionSpeed -= 0.01f;
	//}

	if (GetAsyncKeyState(27)) // ESC
	{
		exit(0);
	}
}

void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	keyboard();

	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);


	switch (rendermode) {

	case NOAPTE:
		glClearColor(0.000, 0.000, 0.000, 0.0);
		break;

	case ZI:
		glClearColor(0.529, 0.808, 0.980, 0.0);
		break;
	};

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}


	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawTree();
			glPopMatrix();
		}

	glutSwapBuffers();
}




void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
	case 'k':
		if(fraction <= 0.6f)
			fractionSpeed += 0.02f;
		break;
	case 'm':
		if (fraction >= -0.2f)
			fractionSpeed -= 0.02f;
		break;
	}
}
//
//void processSpecialKeys(int key, int xx, int yy) {
//
//	float fraction = 0.1f;
//
//	switch (key) {
//	case GLUT_KEY_LEFT:
//		angle -= 0.01f;
//		lx = sin(angle);
//		lz = -cos(angle);
//		break;
//	case GLUT_KEY_RIGHT:
//		angle += 0.01f;
//		lx = sin(angle);
//		lz = -cos(angle);
//		break;
//	case GLUT_KEY_UP:
//		x += lx * fraction;
//		z += lz * fraction;
//		break;
//	case GLUT_KEY_DOWN:
//		x -= lx * fraction;
//		z -= lz * fraction;
//		break;
//	}
//}


int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	glutCreateMenu(menu);
	glutAddMenuEntry("Noapte", NOAPTE);
	glutAddMenuEntry("Zi", ZI);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// enter GLUT event processing cycle
	glutMainLoop();

}

