#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void drawCircleOutline(float radius, float red, float green, float blue) {
    const int segments = 72;
    const float pi = 3.14159265f;
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * pi * i / segments;
        glVertex2f(radius * std::cos(angle), radius * std::sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0f);
    drawCircleOutline(0.25f, 1.0f, 0.2f, 0.2f);
    drawCircleOutline(0.50f, 0.2f, 0.8f, 0.3f);
    drawCircleOutline(0.75f, 0.2f, 0.4f, 1.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Concentric Circles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
