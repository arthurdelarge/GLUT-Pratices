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

GLdouble translation_x, translation_y, rotation;

void orthogonal_projection(GLdouble left_coord, GLdouble right_coord, GLdouble base_coord,
               GLdouble top_coord, GLdouble closer_d, GLdouble further_d){

    GLdouble m[4][4] = {0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0};

    m[0][0] = 2 / (right_coord - left_coord);
    m[1][1] = 2 / (top_coord - base_coord);
    m[2][2] = -2 / (further_d - closer_d);
    m[3][0] = -(right_coord + left_coord) / (right_coord - left_coord);
    m[3][1] = -(top_coord + base_coord) / (top_coord - base_coord);
    m[3][2] = -(further_d + closer_d) / (further_d - closer_d);
    m[3][3] = 1;
}

void Initialize(){
   translation_x = 0; translation_y = 0; rotation = 0;

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void Display(){
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 1.0, 0.0);

   glLoadIdentity (); 
    
   glRotatef(rotation,0.0,0.0,1.0);
   glTranslatef(translation_x,translation_y,0.0);

   glScalef (0.5, 0.5, 0.5);

   glutWireCube (1.0);

   glFlush ();
}

void Reshape(int w, int h){
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   orthogonal_projection(-0.5, 0.5, -0.5, 1.0, -1, 2);

   glMatrixMode (GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27:
		exit(0);
		break;

    case 'w':
        translation_y += 0.1;
        break;
    case 's':
	      translation_y -= 0.1;
	      break;
    case 'a':
        translation_x -= 0.1;
        break;
    case 'd':
        translation_x += 0.1;
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
   glutCreateWindow("\"WASD\" TO MOVE \"QE\" TO ROTATE");
   Initialize();
   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMainLoop();
   return 0;
}