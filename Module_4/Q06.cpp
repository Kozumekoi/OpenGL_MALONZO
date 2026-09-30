#include "common.h"

void display() {
    const GLfloat vertices[] = {
        -0.7f, -0.55f, 0.0f,  0.7f, -0.55f, 0.0f,  0.0f, 0.7f, 0.0f
    };
    // Visit top, bottom-left, bottom-right; the storage order differs.
    const GLubyte indices[] = { 2, 0, 1 };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.3f, 0.9f, 0.45f);
    enableVertices(vertices); glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q06 - Indexed Triangle Order");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
