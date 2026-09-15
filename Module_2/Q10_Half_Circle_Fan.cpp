#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    const int outerVertices = 8;
    const float pi = 3.14159265f;
    const float radius = 0.72f;
    glColor3f(0.95f, 0.35f, 0.25f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, -0.25f);
        for (int i = 0; i < outerVertices; ++i) {
            float angle = pi * i / (outerVertices - 1);
            glVertex2f(radius * std::cos(angle),
                       -0.25f + radius * std::sin(angle));
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q10 - Half-Circle Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
