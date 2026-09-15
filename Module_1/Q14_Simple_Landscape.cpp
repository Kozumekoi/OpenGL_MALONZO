#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void drawSun() {
    const int segments = 60;
    const float pi = 3.14159265f;
    glColor3f(1.0f, 0.85f, 0.1f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.55f, 0.45f);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * pi * i / segments;
            glVertex2f(0.55f + 0.18f * std::cos(angle),
                       0.45f + 0.30f * std::sin(angle));
        }
    glEnd();
}

void display() {
    glClearColor(0.55f, 0.80f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.15f, 0.62f, 0.22f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.25f);
        glVertex2f(-1.0f, -0.25f);
    glEnd();
    drawSun();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q14 - Simple Landscape");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
