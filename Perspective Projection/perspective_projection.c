#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLdouble x_translation, y_translation, rotation;

void perspective_projection(GLdouble angle, GLdouble proportion, GLdouble closer_d, GLdouble further_d){
   GLdouble x_height, min_x, min_y, y_width;
   GLdouble PI = M_PI;

   GLdouble m[4][4] = {0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0};

   x_height =  tan( (angle / 2) / 180*PI) * closer_d;
   min_x = -x_height;

   min_y = min_x / proportion;
   y_width = x_height / proportion;

   m[0][0] = (2.0 * closer_d) / (x_height - min_x);
   m[1][1] = (2.0 * closer_d) / (y_width - min_y);
   m[2][2] = -(further_d + closer_d) / (further_d - closer_d);
   m[0][2] = (x_height + min_x) / (x_height - min_x);
   m[1][2] = (y_width + min_y) / (y_width - min_y);
   m[3][2] = -1.0;
   m[2][3] = -(2.0 * further_d * closer_d) / (further_d - closer_d);

   glMultMatrixd(*m);
}

void Initialize(){
   x_translation = 0; y_translation = 0; rotation = 0;

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void Display(){
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 1.0, 0.0);

   glLoadIdentity ();

   gluLookAt(0.0, 0.0, 5.0,
             0.0, 0.0, 0.0,
             0.0, 1.0, 0.0);

   glRotatef(rotation,0.0,0.0,1.0);
   glTranslatef(x_translation,y_translation,0.0);

   glutWireCube (1.0);

   glFlush ();
}

void Reshape(int w, int h){
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   perspective_projection(5.0, 1.0, 5, 20);

   glMatrixMode (GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27:
		exit(0);
		break;

        case 'w':
            y_translation += 1;
            break;
		case 's':
			y_translation -= 1;
			break;
        case 'a':
            x_translation -= 1;
            break;
        case 'd':
            x_translation += 1;
            break;

        case 'e':
            rotation += 5;
            if (rotation >= 360)
            	rotation = 0;
            break;
		case 'q':
			rotation -= 5;
			if (rotation <= -360)
				rotation = 0;
			break;

	}
	Reshape(800, 800);
    Display();
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("\"WASD\" TO MOVE E \"QE\" TO ROTATE");
   Initialize();
   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMainLoop();
   return 0;
}