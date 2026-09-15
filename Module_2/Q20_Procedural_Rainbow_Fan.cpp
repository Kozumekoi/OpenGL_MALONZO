#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int SEGMENT_COUNT = 96;
const float pi = 3.14159265f;

void rainbowColor(float t, float& red, float& green, float& blue) {
    red   = 0.5f + 0.5f * std::sin(2.0f * pi * t);
    green = 0.5f + 0.5f * std::sin(2.0f * pi * t + 2.0f * pi / 3.0f);
    blue  = 0.5f + 0.5f * std::sin(2.0f * pi * t + 4.0f * pi / 3.0f);
}

void display() {
    glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    const float radius = 0.78f;
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= SEGMENT_COUNT; ++i) {
            float t = static_cast<float>(i) / SEGMENT_COUNT;
            float angle = 2.0f * pi * t;
            float red, green, blue;
            rainbowColor(t, red, green, blue);
            glColor3f(red, green, blue);
            glVertex2f(radius * std::cos(angle), radius * std::sin(angle));
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutCreateWindow("Q20 - Procedural Rainbow Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
