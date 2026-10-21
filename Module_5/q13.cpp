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
void key(unsigned char,int,int);

GLuint a,b;

void init() {
    GLfloat p[] = {
        -.7f, -.5f, 0,
        -.2f, -.5f, 0,
        -.45f, .4f, 0
    };
    GLfloat q[] = {
        .2f, -.5f, 0,
        .7f, -.5f, 0,
        .45f, .4f, 0
    };
    glGenBuffers(1,&a);
    glBindBuffer(GL_ARRAY_BUFFER,a);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_STATIC_DRAW);
    glGenBuffers(1,&b);
    glBindBuffer(GL_ARRAY_BUFFER,b);
    glBufferData(GL_ARRAY_BUFFER,sizeof(q),q,GL_STATIC_DRAW);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,a);
    glVertexPointer(3,GL_FLOAT,0,0);
    glColor3f(1,.3f,.2f);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindBuffer(GL_ARRAY_BUFFER,b);
    glVertexPointer(3,GL_FLOAT,0,0);
    glColor3f(.2f,.6f,1);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}
void key(unsigned char k,int,int) {
    if(k==27) {
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glDeleteBuffers(1,&a);
        glDeleteBuffers(1,&b);
        std::exit(0);
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - ESC Releases Two VBOs");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}
