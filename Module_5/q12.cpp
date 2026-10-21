#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>

void display();
void init();
void tick(int);

GLuint vb;
GLfloat x=-.7f;

void init() {
    glPointSize(14);
    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    GLfloat p[] = {
        -.7f, 0, 0
    };
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void tick(int) {
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    GLfloat* m=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    if(m) {
        x+=.15f;
        if(x>.8f)x=-.8f;
        m[0]=x;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glutPostRedisplay();
    glutTimerFunc(1000, tick, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,.4f,.2f);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_POINTS,0,1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Moving Mapped Point");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000,tick,0);
    glutMainLoop();
    return 0;
}
