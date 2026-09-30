#include "common.h"

void display() {
    const GLfloat hexagon[] = {
         0.0f,  0.75f, 0.0f,  0.65f, 0.38f, 0.0f,
         0.65f, -0.38f, 0.0f, 0.0f, -0.75f, 0.0f,
        -0.65f, -0.38f, 0.0f, -0.65f, 0.38f, 0.0f
    };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.95f, 0.45f, 0.15f);
    enableVertices(hexagon); glDrawArrays(GL_POLYGON, 0, 6); disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q02 - Vertex Array Hexagon");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
