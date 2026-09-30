#include "common.h"

void display() {
    const GLfloat segments[] = {
        -0.8f,  0.45f, 0.0f,  0.8f,  0.45f, 0.0f,
        -0.8f, -0.45f, 0.0f,  0.8f, -0.45f, 0.0f
    };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(1.0f, 0.85f, 0.2f); glLineWidth(5.0f);
    enableVertices(segments); glDrawArrays(GL_LINES, 0, 4); disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q03 - Two Lines, One Array");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
