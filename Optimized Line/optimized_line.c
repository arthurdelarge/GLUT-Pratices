#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/glut.h>

void inc_line(int x1, int y1, int x2, int y2){
	int dx, dy, incE, incNE, d, x, y;

	dx = x2 - x1;
	dy = y2 - y1;
	d = 2 * dy - dx;

	incE = 2 * dy;
	incNE = 2 * (dy - dx);

	x = x1;
	y = y1;

	glBegin(GL_POINTS);
	glVertex2i(x, y);

	while(x < x2){
		if(d <= 0){
			d += incE;
			x++;
		}else{
			d += incNE;
			x++;
			y++;
		}
		glVertex2i(x, y);
	}

	glEnd();
}

void Display (void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0,0.0,0.0);
	inc_line(100, 100, 350, 360);

	glColor3f(1.0,1.0,1.0);
	inc_line(100, 100, 300, 200);

	glFlush();
}

void Definitions(void){
    glMatrixMode (GL_PROJECTION);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	gluOrtho2D (0, 400, 0, 400);
}

int main (){
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (300, 100);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow ("OPTIMIZED LINE");
	Definitions();
	glutDisplayFunc(Display);
	glutMainLoop();
}
