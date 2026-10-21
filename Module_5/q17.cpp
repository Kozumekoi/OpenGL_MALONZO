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
    GLfloat p[30*2*3];
    for(int i=0;i<30;++i) {
        float a=2.0f*3.14159265f*i/30.0f,
        c=cosf(a),
        s=sinf(a);
        int j=i*6;
        p[j]=.55f*c;
        p[j+1]=.55f*s;
        p[j+2]=0;
        p[j+3]=.75f*c;
        p[j+4]=.75f*s;
        p[j+5]=0;
    }
    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,.8f,.2f);
    glLineWidth(3);
    glBindBuffer(GL_ARRAY_BUFFER,vb);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_LINES,0,60);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Procedural 30 Dash Ring");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
