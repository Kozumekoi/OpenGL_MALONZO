#include "common.h"

void display() {
    const GLfloat square[] = {
        -0.55f, -0.55f, 0.0f, 0.55f, -0.55f, 0.0f,
         0.55f,  0.55f, 0.0f, -0.55f,  0.55f, 0.0f
    };
    glClear(GL_COLOR_BUFFER_BIT); enableVertices(square);
    glColor3f(0.15f, 0.45f, 0.95f); glDrawArrays(GL_QUADS, 0, 4);
    glColor3f(1.0f, 0.9f, 0.15f); glLineWidth(4.0f); glDrawArrays(GL_LINE_LOOP, 0, 4);
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q04 - Square and Outline");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
