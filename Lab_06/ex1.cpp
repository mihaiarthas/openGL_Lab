 
// TRIUNGHI ROTIT / STATIC

#include <windows.h>
#include <gl/freeglut.h>

int i;
double scale = 1;


void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity (  );
     
	glMatrixMode (GL_PROJECTION); // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (-800.0, 800.0, -600.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	
}

void rotireTriunghi (void)
{
	glClear(GL_COLOR_BUFFER_BIT); 

	// TRIUNGHIUL ORIGINAL  
	glLineWidth(6.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glBegin (GL_TRIANGLES);
	glColor3f (0,0,1);
	glVertex2f(100,100);
	glColor3f (0,1,0);
	glVertex2f(500,100);
	glColor3f (1,0,0);
	glVertex2f(300,400);
	glEnd( );

	// CENTRUL DE GREUTATE
	glColor3f(0,0,0);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2f(300,200);
	glEnd( );

	// APLICAREA TRANSFORMARII ASUPRA TRIUNGHIULUI 
	i++;
	scale += 0.01;
	glPushMatrix ( );
		glTranslated(300,200,0);
		glRotated(i, 0, 0, 1);
		glScaled(scale,scale,0);

		glTranslated(-300,-200,0);

		glPushMatrix();

		
		glBegin (GL_TRIANGLES);
		glColor3f (0,0,1);
		glVertex2f(100,100);
		glColor3f (0,1,0);
		glVertex2f(500,100);
		glColor3f (1,0,0);
		glVertex2f(300,400);
		glEnd( );

		glPopMatrix ( );

	glPopMatrix ( );


	glutSwapBuffers();
	glutPostRedisplay();
	glFlush ( );

}
void main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (1200, 800); // dimensiunile ferestrei 
	glutCreateWindow ("Triunghi rotit in jurul centrului de greutate"); // creeaza fereastra 
	init ();
	glutDisplayFunc (rotireTriunghi); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
   
}
