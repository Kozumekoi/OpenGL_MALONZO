#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdlib>

int activeLight = 0;

void drawCircle(float cx, float cy, float radius, float red, float green, float blue) {
    const int segments = 60;
    const float pi = 3.14159265f;
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * pi * i / segments;
            glVertex2f(cx + radius * std::cos(angle), cy + radius * std::sin(angle));
        }
    glEnd();
}

void display() {
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.32f, -0.85f);
        glVertex2f( 0.32f, -0.85f);
        glVertex2f( 0.32f,  0.85f);
        glVertex2f(-0.32f,  0.85f);
    glEnd();
    drawCircle(0.0f,  0.55f, 0.19f, activeLight == 0 ? 1.0f : 0.25f, 0.0f, 0.0f);
    drawCircle(0.0f,  0.00f, 0.19f, activeLight == 1 ? 1.0f : 0.25f, activeLight == 1 ? 0.85f : 0.20f, 0.0f);
    drawCircle(0.0f, -0.55f, 0.19f, 0.0f, activeLight == 2 ? 1.0f : 0.25f, 0.0f);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'n' || key == 'N') {
        activeLight = (activeLight + 1) % 3;
        glutPostRedisplay();
    }
    if (key == 27) std::exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 650);
    glutCreateWindow("Q17 - Traffic Light (press N)");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
