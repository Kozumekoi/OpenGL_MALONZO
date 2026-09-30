#include "common.h"

void display() {
    const GLfloat vertices[] = { 0.0f, 0.72f, 0.0f, -0.72f, -0.58f, 0.0f, 0.72f, -0.58f, 0.0f };
    const GLfloat colors[] = { 1.0f, 0.15f, 0.15f, 0.15f, 1.0f, 0.2f, 0.2f, 0.35f, 1.0f };
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices); glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q07 - Vertex and Color Arrays");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
