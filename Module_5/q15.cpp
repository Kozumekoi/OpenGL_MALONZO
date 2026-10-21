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
GLfloat offset=0.0f,dir=.025f;

void init() {
    GLfloat p[] = {
        -.35f, -.2f, 0,
        .35f, -.2f, 0,
        .35f, .2f, 0,
        -.35f, .2f, 0
    };
    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void tick(int) {
    offset+=dir;
    if(offset>.55f||offset<-.55f) {
        dir=-dir;
        offset+=dir;
    }
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    GLfloat*m=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    if(m) {
        for(int i=1;i<12;i+=3)m[i]=((i==1||i==4)?-.2f:.2f)+offset;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glutPostRedisplay();
    glutTimerFunc(30, tick, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.2f,.7f,1);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_QUADS,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Bouncing Mapped Quad");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(30,tick,0);
    glutMainLoop();
    return 0;
}
