#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    const float pi = 3.14159265f;
    glColor3f(1.0f, 0.75f, 0.1f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; ++i) {
        float radius = (i % 2 == 0) ? 0.75f : 0.32f;
        float angle = pi / 2.0f + i * pi / 5.0f;
        glVertex2f(radius * std::cos(angle), radius * std::sin(angle));
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Five-Pointed Star Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
