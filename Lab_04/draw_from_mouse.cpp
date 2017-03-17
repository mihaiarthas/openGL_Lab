#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>

using namespace std;



struct punct
{
	int x,y;

	punct operator-(const punct& other)
	{
		punct c;
		c.x = x - other.x;
		c.y = y - other.y;
		return c;
	}
};


punct ProdVec(punct a, punct b)
{
	return b - a;
}

bool Conv(punct a, punct b, punct c)
{
	punct u = ProdVec(a,b);
	punct v = ProdVec(b,c);

	int semn = u.x * v.y - u.y * v.x;
	cout << semn << endl;
	return true;
}

punct vector[100];
int numar_puncte = 0;
bool introduc_puncte = true;

void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void desen (void) // procedura desenare  
{
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare


	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < numar_puncte; i++)
			glVertex2i(vector[i].x,vector[i].y);

	glEnd();
	
	glColor3f(0.0,0.0,1.0);
	glPointSize(26);
	glBegin(GL_POINTS);
		for(int i = 0; i < numar_puncte; i++)
		{
			glVertex2i(vector[i].x,vector[i].y);
			punct aux =  ProdVec(vector[i - 1], vector[i]);
			cout << aux.x << " " << aux.y << endl;
		}

	glEnd();

 
   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}

void OnMouseClick(int button, int state, int x, int y)
{
  if (introduc_puncte && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  { 
	  vector[numar_puncte].x = x;
	  vector[numar_puncte].y = 600 - y;	
	  numar_puncte++;
  }
  else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
	  // functia triangulare
  }
}


void main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (800, 600); // dimensiunile ferestrei 
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	glEnable(GL_POINT_SMOOTH);
	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

	glutMouseFunc(OnMouseClick);

	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}
