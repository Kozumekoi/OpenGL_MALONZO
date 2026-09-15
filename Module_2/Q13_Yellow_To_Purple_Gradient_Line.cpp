#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glLineWidth(14.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(-0.80f, 0.0f);
        glColor3f(0.65f, 0.1f, 0.85f); glVertex2f(0.80f, 0.0f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q13 - Yellow-to-Purple Gradient Line");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
