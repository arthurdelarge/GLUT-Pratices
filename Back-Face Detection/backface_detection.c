#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int test = 0;

void Initialize(void);
void Spin(void);
void Display();
void Reshape(int, int);
void Keyboard(unsigned char, int, int);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("PRESS \"T\" TO HIDE SURFACE");
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(Spin);
  Initialize();

  glutMainLoop();
  return 0;
}

void Initialize(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Spin(void) {
  glutPostRedisplay();
}

void Display() {
  if (test){  //SWITCH SURFACE
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  }else{
    glDisable(GL_CULL_FACE);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.0, 0.0, -8.0);

  glBegin(GL_QUADS);

  //BACK
  glColor3f(0.77, 0.49, 0.17);
  glVertex3f(-1.0, 1.0, 1.0);
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(1.0, 1.0, 1.0);

  //FRONT
  glColor3f(0.8, 0.48, 0.13);
  glVertex3f(1.0, 1.0, -1.0);
  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f(-1.0, 1.0, -1.0);

  //LEFT
  glColor3f(0.8, 0.53, 0.22);
  glVertex3f(-1.0, 1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(-1.0, 1.0, 1.0);

  //RIGHT
  glColor3f(0.75, 0.45, 0.12);
  glVertex3f(1.0, 1.0, 1.0);
  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(1.0, 1.0, -1.0);

  //UP
  glColor3f(0.92, 0.62, 0.28);
  glVertex3f(-1.0, 1.0, -1.0);
  glVertex3f(-1.0, 1.0, 1.0);
  glVertex3f(1.0, 1.0, 1.0);
  glVertex3f(1.0, 1.0, -1.0);

  //DOWN (BLLUE)
  glColor3f(0.55, 0.34, 0.11);
  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(-1.0, -1.0, -1.0);

  glEnd();

  glutSwapBuffers();
}

void Reshape(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1, 2.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
  if (key == 27) exit(0);
  if (key == 't'){
    if(test) test = 0;
    else test = 1;
  }
}
