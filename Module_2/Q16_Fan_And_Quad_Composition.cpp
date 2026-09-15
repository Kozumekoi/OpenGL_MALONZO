#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void drawCircle() {
    const int segments = 60;
    const float pi = 3.14159265f;
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.95f, 0.80f); glVertex2f(0.0f, 0.28f);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * pi * i / segments;
            float t = static_cast<float>(i) / segments;
            glColor3f(1.0f, 0.25f + 0.65f * t, 0.45f + 0.45f * (1.0f - t));
            glVertex2f(0.0f + 0.34f * std::cos(angle),
                       0.28f + 0.34f * std::sin(angle));
        }
    glEnd();
}

void drawBase() {
    glColor3f(0.25f, 0.65f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.24f, -0.62f);
        glVertex2f( 0.24f, -0.62f);
        glVertex2f( 0.24f,  0.02f);
        glVertex2f(-0.24f,  0.02f);
    glEnd();
}

void display() {
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBase();
    drawCircle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Fan and Quad Composition");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
