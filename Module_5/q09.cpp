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

GLuint vb,cb;

void init() {
    GLfloat p[] = {
        0, .65f, 0,
        -.6f, -.5f, 0,
        .6f, -.5f, 0
    };
    GLfloat c[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_STATIC_DRAW);
    glGenBuffers(1,&cb);
    glBindBuffer(GL_ARRAY_BUFFER,cb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(c),c,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,cb);
    glColorPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Separate Position and Color VBOs");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
