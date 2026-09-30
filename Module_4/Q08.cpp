#include "common.h"

void display() {
    const GLfloat triangles[] = {
        -0.72f, 0.25f, 0.0f, -0.95f, -0.35f, 0.0f, -0.49f, -0.35f, 0.0f,
        -0.23f, 0.55f, 0.0f, -0.46f, -0.05f, 0.0f, 0.0f, -0.05f, 0.0f,
         0.50f, 0.25f, 0.0f,  0.27f, -0.35f, 0.0f, 0.73f, -0.35f, 0.0f
    };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.95f, 0.6f, 0.2f);
    enableVertices(triangles); glDrawArrays(GL_TRIANGLES, 0, 9); disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500); glutCreateWindow("Q08 - Three Triangles, One Array");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
