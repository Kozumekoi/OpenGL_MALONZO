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

GLuint vbo;

void init() {
    GLfloat p[] = {
        -.6f, -.6f, 0,
        .6f, -.6f, 0,
        .6f, .6f, 0,
        -.6f, .6f, 0
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.2f, .8f, 1);
    glLineWidth(4);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Line Loop Square");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
