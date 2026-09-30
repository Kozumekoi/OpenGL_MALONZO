#include "common.h"

void display() {
    // Five vertical grid lines make a shared pool of ten corner vertices.
    const GLfloat pool[] = {
        -0.8f, -0.35f, 0.0f, -0.8f, 0.35f, 0.0f,
        -0.4f, -0.35f, 0.0f, -0.4f, 0.35f, 0.0f,
         0.0f, -0.35f, 0.0f,  0.0f, 0.35f, 0.0f,
         0.4f, -0.35f, 0.0f,  0.4f, 0.35f, 0.0f,
         0.8f, -0.35f, 0.0f,  0.8f, 0.35f, 0.0f
    };
    const GLubyte quads[4][4] = { {0,2,3,1}, {2,4,5,3}, {4,6,7,5}, {6,8,9,7} };
    glClear(GL_COLOR_BUFFER_BIT); enableVertices(pool);
    for (int i = 0; i < 4; ++i) {
        glColor3f((i % 2) ? 0.92f : 0.08f, (i % 2) ? 0.92f : 0.08f, (i % 2) ? 0.92f : 0.08f);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quads[i]);
    }
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500); glutCreateWindow("Q10 - Indexed Checkerboard Row");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
