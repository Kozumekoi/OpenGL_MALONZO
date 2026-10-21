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
void tick(int);

GLuint shipV,shipC,groundV,groundI;
float shift=0;

void init() {
    GLfloat ship[] = {
        0, .48f, 0,
        0, -.08f, 0,
        .38f, -.08f, 0,
        -.42f, -.16f, 0,
        .42f, -.16f, 0,
        0, -.42f, 0
    };
    GLfloat col[] = {
        1, .75f, .1f,
        1, .75f, .1f,
        .2f, .65f, 1,
        .2f, .65f, 1,
        .2f, .65f, 1,
        .2f, .65f, 1
    };
    GLfloat g[] = {
        -1, -.85f, 0,
        1, -.85f, 0,
        1, -.55f, 0,
        -1, -.55f, 0
    };
    GLubyte ix[]={
        0, 1, 2, 0, 2, 3
    };
    
    glGenBuffers(1,&shipV);
    glBindBuffer(GL_ARRAY_BUFFER,shipV);
    glBufferData(GL_ARRAY_BUFFER,sizeof(ship),ship,GL_DYNAMIC_DRAW);
    glGenBuffers(1,&shipC);
    glBindBuffer(GL_ARRAY_BUFFER,shipC);
    glBufferData(GL_ARRAY_BUFFER,sizeof(col),col,GL_STATIC_DRAW);
    glGenBuffers(1,&groundV);
    glBindBuffer(GL_ARRAY_BUFFER,groundV);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g),g,GL_STATIC_DRAW);
    glGenBuffers(1,&groundI);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundI);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ix),ix,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void tick(int) {
    shift+=.15f;
    if(shift>.8f)shift=-.8f;
    glBindBuffer(GL_ARRAY_BUFFER,shipV);
    GLfloat*m=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    if(m) {
        const GLfloat xOffsets[] = {0, 0, .38f, -.42f, .42f, 0};
        for(int vertex = 0; vertex < 6; ++vertex) {
            m[vertex * 3] = shift + xOffsets[vertex];
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glutPostRedisplay();
    glutTimerFunc(1000, tick, 0);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,groundV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,groundI);
    glColor3f(.2f,.7f,.25f);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);
    glBindBuffer(GL_ARRAY_BUFFER,shipV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,shipC);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,6);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glFlush();
}
void key(unsigned char k,int,int) {
    if(k==27) {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glDeleteBuffers(1,&shipV);
        glDeleteBuffers(1,&shipC);
        glDeleteBuffers(1,&groundV);
        glDeleteBuffers(1,&groundI);
        std::exit(0);
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Animated Ship Over Indexed Ground");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(1000, tick, 0);
    glutMainLoop();
    return 0;
}
