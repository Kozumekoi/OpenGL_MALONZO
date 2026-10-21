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

GLuint vbo;

void init() {
    GLfloat p[] = {
        0, .65f, 0,
        -.6f, -.45f, 0,
        .6f, -.45f, 0
    };
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(p),p,GL_STATIC_DRAW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(.3f,1,.3f);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,3);
    glFlush();
}

void key(unsigned char k,int,int) {
    if(k==27) {
        // Undo enabled vertex-array state.
        glDisableClientState(GL_VERTEX_ARRAY);
        // Undo the current VBO binding.
        glBindBuffer(GL_ARRAY_BUFFER,0);
        // Release the VBO storage.
        glDeleteBuffers(1,&vbo);
        std::exit(0);
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - VBO Cleanup Checklist");
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
