#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

float handAngle = 1.5707963f;
const float pi = 3.14159265f;

void drawClockFace() {
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 72; ++i) {
        float angle = 2.0f * pi * i / 72;
        glVertex2f(0.78f * std::cos(angle), 0.78f * std::sin(angle));
    }
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = 2.0f * pi * i / 12;
        glVertex2f(0.65f * std::cos(angle), 0.65f * std::sin(angle));
        glVertex2f(0.75f * std::cos(angle), 0.75f * std::sin(angle));
    }
    glEnd();
}

void display() {
    glClearColor(0.95f, 0.95f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawClockFace();
    glColor3f(0.8f, 0.1f, 0.1f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.58f * std::cos(handAngle), 0.58f * std::sin(handAngle));
    glEnd();
    glFlush();
}

void idle() {
    handAngle -= 0.0015f;
    if (handAngle < -2.0f * pi) handAngle += 2.0f * pi;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q18 - Rotating Clock Hand");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
