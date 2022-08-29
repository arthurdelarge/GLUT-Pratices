#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/glut.h>

void Definitions(){
	glMatrixMode (GL_PROJECTION);
	glClearColor(0.2,0.2,0.2,0.0);
	gluOrtho2D(0,250,0,250);
}

void Display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	//RED SQUARE (STANDARD)
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex2f(10,50);
	glVertex2f(10,100);
	glVertex2f(60,100);
	glVertex2f(60,50);
	glEnd();

	//GREEN SQUARE (SCALE)
	glScalef(2,2,1);
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex2f(10,50);
	glVertex2f(10,100);
	glVertex2f(60,100);
	glVertex2f(60,50);
	glEnd();

	glLoadIdentity();

	//YELLOW SQUARE (ROTATE)
	glRotatef (30.0, 0.0, 0.0, 1.0);

	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glVertex2f(75,50);
	glVertex2f(75,100);
	glVertex2f(125,100);
	glVertex2f(125,50);
	glEnd();

    glLoadIdentity();

    //BLUE QUARE (TRANSLATE)
	glTranslatef(40.0f, -15.0f, 0.0f);

	glColor3f(0,0,1);
	glBegin(GL_QUADS);
	glVertex2f(10,50);
	glVertex2f(10,100);
	glVertex2f(60,100);
	glVertex2f(60,50);
	glEnd();

	glFlush();
}

int main(){
	glutInitWindowSize(800,600);
	glutInitWindowPosition(10,50);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("TRANSFORMATIONS");
	Definitions();
	glutDisplayFunc(Display);
	glutMainLoop();
}