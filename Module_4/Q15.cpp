#include "common.h"

void display() {
    const GLfloat sun[] = { -0.55f,0.48f,0, -0.55f,0.82f,0, -0.31f,0.72f,0, -0.22f,0.48f,0,
                             -0.31f,0.24f,0, -0.55f,0.14f,0, -0.79f,0.24f,0, -0.88f,0.48f,0, -0.79f,0.72f,0 };
    const GLubyte sunIndices[] = { 0,1,2,3,4,5,6,7,8,1 };
    const GLfloat mountain[] = { -0.95f,-0.65f,0, -0.45f,0.15f,0, 0.05f,-0.65f,0,
                                  -0.2f,-0.65f,0, 0.35f,0.35f,0, 0.9f,-0.65f,0 };
    const GLfloat ground[] = { -1,-0.65f,0, 1,-0.65f,0, 1,-0.95f,0, -1,-0.95f,0 };
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.78f,0.12f); enableVertices(sun); glDrawElements(GL_TRIANGLE_FAN,10,GL_UNSIGNED_BYTE,sunIndices); disableVertices();
    glColor3f(0.35f,0.48f,0.75f); enableVertices(mountain); glDrawArrays(GL_TRIANGLES,0,6); disableVertices();
    glColor3f(0.18f,0.65f,0.28f); enableVertices(ground); glDrawArrays(GL_QUADS,0,4); disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); glutCreateWindow("Q15 - Array Based Landscape");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
