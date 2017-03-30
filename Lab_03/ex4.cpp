#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
#include <math.h>

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

double Distanta(punct a, punct b)
{
	int x = b.x - a.x;
	int y = b.y - a.y;
	return sqrt(x * x + y * y);
}

double Arie(punct a, punct b, punct c)
{
	int delta = a.x * b.y + b.x * c.y + c.x * a.y - ( c.x * b.y + c.y * a.x + a.y * b.x );
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

punct vector[100];
int numar_puncte = 0;
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
	glBegin(GL_TRIANGLES);
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


	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (press && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numar_puncte <= 3)
	{

			vector[numar_puncte].x = x;
			vector[numar_puncte].y = 600 - y;
			numar_puncte++;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && numar_puncte == 4)
	{
		press = false;

		if (Interior(vector[0], vector[1], vector[2], vector[3]) == true)
		{
			cout << "In interior" << endl;
		}
		else cout << "In exterior" << endl;

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
