#include "common.h"

void display() {
    // A stepped profile represented by a single GL_QUAD_STRIP.
    const GLfloat vertices[] = {
        -0.8f,-0.65f,0, -0.8f,-0.15f,0,
        -0.4f,-0.65f,0, -0.4f, 0.10f,0,
         0.0f,-0.65f,0,  0.0f, 0.35f,0,
         0.4f,-0.65f,0,  0.4f, 0.60f,0,
         0.8f,-0.65f,0,  0.8f, 0.80f,0
    };
    const GLfloat colors[] = {
        1,0.25f,0.2f, 1,0.25f,0.2f,  0.2f,0.85f,0.35f, 0.2f,0.85f,0.35f,
        0.2f,0.55f,1, 0.2f,0.55f,1,  1,0.7f,0.15f, 1,0.7f,0.15f,
        0.8f,0.3f,0.95f, 0.8f,0.3f,0.95f
    };
    glClear(GL_COLOR_BUFFER_BIT); glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices); glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUAD_STRIP, 0, 10);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500); glutCreateWindow("Q14 - Colored Staircase Quad Strip");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
