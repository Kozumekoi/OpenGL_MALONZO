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

GLuint vb,cb;
int scheme=0;

void init() {
    GLfloat p[] = {
        0, .6f, 0,
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
    glBufferData(GL_ARRAY_BUFFER,sizeof(c),c,GL_DYNAMIC_DRAW);
}

void key(unsigned char k,int,int) {
    if(k=='c' || k=='C') {
        scheme=(scheme+1)%3;
        GLfloat sets[3][9]={
            {
                1,0, 0,
                0, 1, 0,
                0, 0, 1
            },{
                1, 1, 0,
                1, 0, 1,
                0, 1, 1
            },{
                1, .4f, 0,
                .2f, .8f, .3f,
                .3f, .4f, 1
            }
        };
        glBindBuffer(GL_ARRAY_BUFFER,cb);
        GLfloat*m=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
        if(m) {
            for(int i=0;i<9;++i)m[i]=sets[scheme][i];
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glutPostRedisplay();
    }
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
    glutCreateWindow("Module 5 - Keyboard Color Cycle");
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
