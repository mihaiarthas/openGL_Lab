#include <windows.h>
#include <gl/freeglut.h>


GLint winWidth = 900, winHeight = 900;
GLfloat xx0 = 10.0, yy0 = 10.0, zz0 = 10.0;
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;
bool flag; 

int p1 [ ]={2,-4,5};
int p2 [ ]= {3,4,-2};
int p3 [ ]= {4,2,1};
int p4 [ ]= {3.5, 3, -0.5};

GLfloat xwMin = -10.0, ywMin = -10.0, xwMax = 10.0, ywMax = 10.0;

GLfloat dnear = 0.0, dfar = 80.0;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ( );
	gluLookAt (xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

// poligonul p1p2p3p4
void desen1 (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

 
	 glPolygonMode (GL_FRONT, GL_LINE);
     glPolygonMode (GL_BACK, GL_LINE);
	 glLineWidth(6.0);
	 glColor3f(0.0, 0.0, 0.0);

	 glEnable(GL_CULL_FACE);
	 if(flag)
		glCullFace(GL_FRONT);
	 else
		glCullFace(GL_BACK);
	 glFrontFace(GL_CW);

	/* glBegin (GL_POLYGON);
	    glColor3f (1.0, 0.0, 0.0);
		glVertex3iv (p1);
		glColor3f (0.0, 1.0, 0.0);
		glVertex3iv (p2);
		glColor3f (0.0, 0.0, 1.0);
		glVertex3iv (p4);
		glColor3f (1.0, 1.0, 0.0);
		glVertex3iv (p3);
	glEnd ( );

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3iv(p1);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');

	glRasterPos3iv(p2);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');

	glRasterPos3iv(p3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');

	glRasterPos3iv(p4);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');*/


	glutSolidSphere(5,10,10);
	 
	glFlush ( );
}


// POLIGONUL p1p2p3p5

void mouse2(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
			 flag = true;
     /*       xx0 = 10.0, yy0 = -10.0, zz0 = -10.0;
		 init ( );
		 glutPostRedisplay();*/
		 break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
			 flag = false;
      /*      xx0 = -10.0, yy0 = 10.0, zz0 = 10.0;
		 init ( );
		 glutPostRedisplay();*/
		 break;

   }
}
void reshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth,newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Poligoane in context 3D. Fata si spatele unui poligon");

	init ( );
	// glutMouseFunc (desen1);
	glutMouseFunc(mouse2);
	glutDisplayFunc (desen1);
	glutMainLoop ( );
}

