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

GLuint leftVBO,rightVBO;

void init() {
    GLfloat a[] = {
        -.65f, .45f, 0,
        -.9f, -.35f, 0,
        -.4f, -.35f, 0
    };
    GLfloat b[] = {
        .65f, .45f, 0,
        .4f, -.35f, 0,
        .9f, -.35f, 0
    };
    glGenBuffers(1,&leftVBO);
    glBindBuffer(GL_ARRAY_BUFFER,leftVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(a),a,GL_STATIC_DRAW);
    glGenBuffers(1,&rightVBO);
    glBindBuffer(GL_ARRAY_BUFFER,rightVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(b),b,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1,.3f,.2f);
    glBindBuffer(GL_ARRAY_BUFFER,leftVBO);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glColor3f(.2f,.5f,1);
    glBindBuffer(GL_ARRAY_BUFFER,rightVBO);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Two Independent Triangles");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
