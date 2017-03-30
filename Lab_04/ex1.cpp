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

punct vector[100];
float culoare[100];
int culIndex = 0;
int numar_puncte = 0;
bool introduc_puncte = true;
bool press = true;
bool final = false;

double Arie(punct a, punct b, punct c)
{
	int delta = a.x * b.y + b.x * c.y + c.x * a.y - (c.x * b.y + c.y * a.x + a.y * b.x);
	if (delta < 0) delta *= -1;

	return 0.5 * delta;
}

bool Interior(punct a, punct b, punct c, punct m)
{
	double ABC = Arie(a, b, c);
	double AMB = Arie(a, m, b);
	double AMC = Arie(a, m, c);
	double BMC = Arie(b, m, c);

	double asd = AMB + AMC + BMC;

	if (ABC == AMB + AMC + BMC) return true;
	return false;
}

void checkPrincipal(punct vec[], int n, int poz)
{
	for (int i = 0; i < n; i++)
	{
		bool in = false;
		if (i != poz)
		{
			if (poz == 0 && i != n - 1 && i != 1)
			{
				in = Interior(vec[n - 1], vec[0], vec[1], vec[i]);
			}
			else if (poz == n - 1 && i != n - 2 && i != 0)
			{
				in = Interior(vec[n - 2], vec[n - 1], vec[0], vec[i]);
			}
			else if (i != poz - 1 && i != poz + 1)
			{
				in = Interior(vec[poz - 1], vec[poz], vec[poz + 1], vec[i]);
			}
			if (in == true)
			{
				culoare[poz] = 1;
				cout << i + 1<< " este in interior\n";
			}
		}
	}
}

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
		return true;
	}
	return false;
}




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

	glColor3f(0.0, 0.0, 0.0);
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
			glColor3f(0.0 , culoare[i], 0.0);
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

		if (poz == numar_puncte - 1)
		{
			semnConvex = Semn(vector[0], vector[numar_puncte - 1], vector[numar_puncte - 2]);
		}
		else if (poz == 0)
		{
			semnConvex = Semn(vector[numar_puncte - 1], vector[0], vector[1]);
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

			if (semnConvex != semn)
			{
				culoare[i] = 0.3;
				cout << i + 1 << " este convex" << endl;
				checkPrincipal(vector, numar_puncte, i);
				cout << endl;
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