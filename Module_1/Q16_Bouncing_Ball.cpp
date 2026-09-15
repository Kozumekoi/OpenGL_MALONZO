#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

float ballX = 0.0f, ballY = 0.0f;
float dx = 0.007f, dy = 0.010f;
const float radius = 0.12f;

void drawBall() {
    const int segments = 60;
    const float pi = 3.14159265f;
    glColor3f(1.0f, 0.45f, 0.1f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(ballX, ballY);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * pi * i / segments;
            glVertex2f(ballX + radius * std::cos(angle),
                       ballY + radius * std::sin(angle));
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall();
    glFlush();
}

void timer(int) {
    ballX += dx;
    ballY += dy;
    if (ballX + radius >= 1.0f || ballX - radius <= -1.0f) dx = -dx;
    if (ballY + radius >= 1.0f || ballY - radius <= -1.0f) dy = -dy;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Bouncing Ball");
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
