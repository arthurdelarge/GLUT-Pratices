#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int CIRCLE_RADIUS;

void Display();
void Initialize();
void MidPointCircle(int r);
void CirclePoint(int x,int y);
void Keyboard(unsigned char key, int x, int y);

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(50,50);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("OPTIMIZED CIRCUNFERENCE");

	Initialize();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

    return 0;
}

void Initialize(){
    glClearColor(0.8,0.8,0.8,0.8);
    gluOrtho2D(-100,100,-100,100);
    CIRCLE_RADIUS = 40;
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f (0.0, 0.0, 0.0);

    glBegin (GL_LINES);
    
    glVertex2f (-100.0,0.0);
    glVertex2f (+100.0,0.0);
    glVertex2f (0.0,-100.0);
    glVertex2f (0.0,+100.0);

    glEnd();

    glPointSize(3);

    MidPointCircle(CIRCLE_RADIUS);
    
    glFlush();
}

void MidPointCircle(int r){
    int x, y;
    float d, h;
    x = 0;
    y = r;
    h = 1 - r;
    glBegin(GL_POINTS);

    CirclePoint (x,y);
    while (y > x){
        if (h < 0){
            h = h + 2 * x + 3;
            x++;
        } else {
            h = h + 2 * (x - y) + 5;
            x++;
            y--;
        }
        CirclePoint (x,y);
    }
    glEnd();
}

void CirclePoint (int x,int y){
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(x,y);
    glVertex2i(-x,y);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(x,-y);
    glVertex2i(-x,-y);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(y,x);
    glVertex2i(y,-x);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(-y,x);
    glVertex2i(-y,-x);
}

void Keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        case 'w':
            if (CIRCLE_RADIUS < 99)
                CIRCLE_RADIUS++;
            break;
            
        case 's':
            if (CIRCLE_RADIUS > 1)
                CIRCLE_RADIUS--;
            break;
    }
    Display();
}