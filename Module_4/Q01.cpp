#include "common.h"

void display() {
    const GLfloat points[] = {
        -0.65f, -0.65f, 0.0f, -0.65f, 0.65f, 0.0f,
         0.65f, -0.65f, 0.0f,  0.65f, 0.65f, 0.0f,
         0.0f,   0.0f,  0.0f
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.25f, 0.85f, 1.0f);
    glPointSize(18.0f);
    enableVertices(points);
    glDrawArrays(GL_POINTS, 0, 5);
    disableVertices();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q01 - X Pattern Points");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
