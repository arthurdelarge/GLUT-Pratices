#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define DRAW_RED glColor3f (1.0, 0.0, 0.0);
#define DRAW_GREEN glColor3f (0.0, 1.0, 0.0);
#define DRAW_BLUE glColor3f (0.0, 0.0, 1.0);
#define DRAW_BLACK glColor3f (0.0, 0.0, 0.0);
#define DRAW_WHITE glColor3f (1.0, 1.0, 1.0);
#define DRAW_YELLOW glColor3f (1.0, 1.0, 0.0);

int N_STEPS;
typedef struct point_struct {
    GLfloat x;
    GLfloat y;
struct point_struct *next;
} POINT_ST;

typedef struct curve_struct{
    GLuint n_points;
    POINT_ST *points;
} CURVE_ST;

CURVE_ST* curve_create(){
    CURVE_ST* curve = (CURVE_ST*)malloc (sizeof(CURVE_ST));
    curve->n_points = 0;
    curve->points = NULL;

    return curve;
}


POINT_ST* create_point (GLfloat x, GLfloat y){
    POINT_ST* newpoint = (POINT_ST*)malloc (sizeof(POINT_ST));
    newpoint->x = x;
    newpoint->y = y;
    newpoint->next = NULL;

    return newpoint;
    }

POINT_ST sum_points(POINT_ST p1, POINT_ST p2){
    p1.x += p2.x;
    p1.y += p2.y;

    return p1;
}


POINT_ST mult_points (POINT_ST p, GLfloat constant){
    p.x *= constant;
    p.y *= constant;

    return p;
}


void add_point (CURVE_ST* curve, GLfloat x, GLfloat y){
    POINT_ST *newpoint = create_point (x, y);

    newpoint->next = curve->points;
    curve->points = newpoint;

    curve->n_points++;

    return;
}

void del_point (POINT_ST* point){
    POINT_ST* nextpoint = point->next;

    while(nextpoint != NULL){
        free(point);
        point = nextpoint;
        nextpoint = nextpoint->next;
    }

    free(point);

    return;
}

void del_curve (CURVE_ST* curve){
    if (curve->points != NULL)
        del_point(curve->points);

    free(curve);

    return;
}

void draw_curve (CURVE_ST* curve){
    POINT_ST* actualpoint = curve->points;


    glBegin(GL_LINE_STRIP);

    while (actualpoint != NULL){
        glVertex2f (actualpoint->x, actualpoint->y);
        actualpoint = actualpoint->next;
    }

    glEnd();

    return;
}

POINT_ST recursive_bezier(POINT_ST* point, GLfloat t, GLint level){

    if (level == 0)
        return (*point);
    else
        return sum_points(
                mult_points(recursive_bezier(point, t, level-1), t),
                mult_points(recursive_bezier(point->next, t, level-1), 1.0-t)
        );
}

POINT_ST cubic_bezier(POINT_ST* point, GLfloat t){
    POINT_ST P1, P2, P3, P4;
    P1 = *point;
    P2 = *(P1.next);
    P3 = *(P2.next);
    P4 = *(P3.next);

    return sum_points (
                        mult_points(P1, t*t*t),
                        sum_points(
                                    mult_points(P2, 3*t*t*(1-t)),
                                    sum_points(
                                                mult_points(P3, 3*t*(1-t)*(1-t)),
                                                mult_points(P4, (1-t)*(1-t)*(1-t))
                                                )
                                    )
                        );
}

POINT_ST quadratic_bezier(POINT_ST* point, GLfloat t){
    POINT_ST P1, P2, P3;
    P1 = *point;
    P2 = *(P1.next);
    P3 = *(P2.next);
    return sum_points(
                       mult_points(P1, t*t),
                       sum_points(
                                   mult_points(P2, 2*t*(1-t)),
                                   mult_points(P3, (1-t)*(1-t))
                                   )
                       );
}

CURVE_ST* create_bezier (CURVE_ST* curve, GLint steps){
    POINT_ST point;
    CURVE_ST* bezier = curve_create();
    GLfloat t=0, dt = 1.0/(steps-1.0);

    if (steps < 2 || curve->n_points < 2)
        return bezier;

    while(steps--){
        if (curve->n_points == 3)
            point = quadratic_bezier (curve->points, t);
        else if (curve->n_points == 4)
            point = cubic_bezier (curve->points, t);
        else
            point = recursive_bezier (curve->points, t, curve->n_points-1);

        t += dt;
        if (t>1)
            t=1;

        add_point (bezier , point.x, point.y);
    }

    return bezier;
}

void draw(){
    CURVE_ST* curve = curve_create();
    CURVE_ST* bezier;
    GLint i;

    glClear(GL_COLOR_BUFFER_BIT);

    DRAW_BLACK
    glBegin (GL_LINES);
        glVertex2f (-10.0,0.0);
        glVertex2f (+10.0,0.0);
        glVertex2f (0.0,-10.0);
        glVertex2f (0.0,+10.0);
    glEnd();

    DRAW_RED
    glPointSize(5);
    glBegin (GL_POINTS);
        for (i=-10; i<=10; i++){
            glVertex2f (i, 0);
            glVertex2f (0, i);
        }
    glEnd();

    add_point (curve, -8, 0);
    add_point (curve, -5, 10);
    add_point (curve, 5, 5);
    add_point (curve, +8, 3);
    add_point (curve, +8, 2);
    add_point (curve, -2, -4);
    add_point (curve, +9, -3);
    add_point (curve, -6, -1);
    add_point (curve, +1, 0);
    add_point (curve, -0, 7);
    add_point (curve, +7, 3);
    add_point (curve, 9, 6);

    bezier = create_bezier (curve, N_STEPS);

    DRAW_BLACK
    draw_curve (bezier);

    del_curve(curve);
    del_curve(bezier);

    glFlush();
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    scanf("%d", &N_STEPS);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("BEZIER CURVES");
    glClearColor(1,1,1,0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D(-10.0,10.0,-10.0,10.0);
    glutDisplayFunc(draw);

    glutMainLoop();
}
