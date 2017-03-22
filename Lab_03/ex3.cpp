#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>

using namespace std;


struct punct
{
	int x, y;

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

bool Semn(punct a, punct b, punct c)
{
	punct u = ProdVec(a, b);
	punct v = ProdVec(b, c);

	int semn = u.x * v.y - u.y * v.x;
	if (semn >= 0)
	{
		cout << "mai mare decat 0" << endl;
		return true;
	}
	cout << "mai mic decat 0" << endl;
	return false;
}

punct vector[100];
float culoare[100];
int culIndex = 0;
int numar_puncte = 0;
bool introduc_puncte = true;
bool press = true;
bool final = false;


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void desen(void) // procedura desenare  
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numar_puncte; i++)
		glVertex2i(vector[i].x, vector[i].y);

	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glPointSize(26);
	glBegin(GL_POINTS);

	for (int i = 0; i < numar_puncte; i++)
	{
		glVertex2i(vector[i].x, vector[i].y);
	}

	glEnd();

	if (final == true)
	{
		glPointSize(26);
		glBegin(GL_POINTS);

		for (int i = 0; i < numar_puncte; i++)
		{
			glColor3f(culoare[i] + 1, 0.0, culoare[i]);
			glVertex2i(vector[i].x, vector[i].y);
		}

		glEnd();
	}


	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (introduc_puncte && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (press == true)
		{
			vector[numar_puncte].x = x;
			vector[numar_puncte].y = 600 - y;
			numar_puncte++;
		}
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		press = false;
		int X = INT_MAX;
		punct extrem;
		int poz;
		bool semnConvex;
		for (int i = 0; i < numar_puncte; i++)
		{
			if (vector[i].x < X)
			{
				extrem = vector[i];
				X = vector[i].x;
				poz = i;
			}
		}
		cout << extrem.x << " " << extrem.y << " " << poz << endl;

		if (poz == numar_puncte - 1)
		{
			cout << "ultim" << endl;
			semnConvex = Semn(vector[0], vector[numar_puncte - 1], vector[numar_puncte - 2]);
		}
		else if (poz == 0)
		{
			cout << "prim" << endl;
			semnConvex = Semn(vector[numar_puncte - 1], vector[0], vector[1] );
		}
		else
		{
			semnConvex = Semn(vector[poz - 1], vector[poz], vector[poz + 1]);
		}

		cout << endl << endl << endl;

		for (int i = 0; i < numar_puncte; i++)
		{
			bool semn;
			if (i == 0)
			{
				semn = Semn(vector[numar_puncte - 1], vector[0], vector[1]);
			}
			else if (i == numar_puncte - 1)
			{
				semn = Semn(vector[numar_puncte - 2], vector[numar_puncte - 1], vector[0]);
			}
			else
			{
				semn = Semn(vector[i - 1], vector[i], vector[i + 1]);
			}

			if (semnConvex == semn)
			{
				cout << "Convex " << i << endl;
				culoare[i] = 0.3;
			}
			else
			{
				cout << "Concav " << i << endl;
				culoare[i] = 1;
			}
		}
		final = true;
		
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(800, 600); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	glEnable(GL_POINT_SMOOTH);
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

	glutMouseFunc(OnMouseClick);

	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}