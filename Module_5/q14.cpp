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

GLuint vb,ib;

void init() {
    GLfloat p[] = {
        0, 0, 0,
        0, .7f, 0,
        .67f, .22f, 0,
        .41f, -.57f, 0,
        -.41f, -.57f, 0,
        -.67f, .22f, 0
    };

    GLubyte ix[]={
        0, 1, 2, 3, 4, 5, 1
    };

    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_STATIC_DRAW);
    glGenBuffers(1,&ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ix),ix,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,.5f,.1f);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ib);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLE_FAN,7,GL_UNSIGNED_BYTE,0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Indexed Triangle Fan Pentagon");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
