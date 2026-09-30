#include "common.h"

void display() {
    // Center is stored once; the last outer index closes the fan.
    const GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f,  0.0f, 0.75f, 0.0f,  0.71f, 0.23f, 0.0f,
        0.44f, -0.61f, 0.0f, -0.44f, -0.61f, 0.0f, -0.71f, 0.23f, 0.0f
    };
    const GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 1 };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.9f, 0.35f, 0.75f);
    enableVertices(vertices); glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, indices);
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q09 - Indexed Pentagon Fan");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
