#include "common.h"

void display() {
    // Each vertex record is x,y,z,r,g,b (six floats, non-zero stride).
    const GLfloat interleaved[] = {
        -0.65f,-0.55f,0.0f, 1.0f,0.1f,0.1f,
         0.65f,-0.55f,0.0f, 0.1f,1.0f,0.2f,
         0.65f, 0.55f,0.0f, 0.1f,0.3f,1.0f,
        -0.65f, 0.55f,0.0f, 1.0f,0.8f,0.1f
    };
    const GLsizei stride = 6 * sizeof(GLfloat);
    glClear(GL_COLOR_BUFFER_BIT); glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, stride, interleaved);
    glColorPointer(3, GL_FLOAT, stride, interleaved + 3);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q12 - Interleaved Quad");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
