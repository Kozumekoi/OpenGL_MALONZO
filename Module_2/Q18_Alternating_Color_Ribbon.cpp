#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    const int quadCount = 6;
    const float left = -0.9f;
    const float width = 1.8f / quadCount;

    glShadeModel(GL_FLAT);
    glBegin(GL_QUAD_STRIP);
    for (int pair = 0; pair <= quadCount; ++pair) {
        if (pair % 2 == 0) glColor3f(0.95f, 0.25f, 0.30f);
        else glColor3f(0.15f, 0.70f, 0.90f);
        float x = left + pair * width;
        glVertex2f(x, -0.42f);
        glVertex2f(x,  0.42f);
    }
    glEnd();
    glShadeModel(GL_SMOOTH);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 450);
    glutCreateWindow("Q18 - Alternating-Color Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
