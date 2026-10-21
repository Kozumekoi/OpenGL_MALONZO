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

GLuint vb;

void init() {
    GLfloat p[] = {
        0, .6f, 0,
        -.6f, -.5f, 0,
        .6f, -.5f, 0
    };
    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_DYNAMIC_DRAW);
    GLfloat* m=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    if(m) {
        m[1]+=.35f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f,1,.4f);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glEnableClientState(GL_VERTEX_ARRAY);
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
    glutCreateWindow("Module 5 - One-Shot Mapped Vertex Shift");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
