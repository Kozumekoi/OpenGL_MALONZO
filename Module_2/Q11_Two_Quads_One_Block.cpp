#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0.95f, 0.25f, 0.20f); glVertex2f(-0.85f, -0.45f);
        glColor3f(0.95f, 0.25f, 0.20f); glVertex2f(-0.20f, -0.45f);
        glColor3f(0.95f, 0.25f, 0.20f); glVertex2f(-0.20f,  0.45f);
        glColor3f(0.95f, 0.25f, 0.20f); glVertex2f(-0.85f,  0.45f);

        glColor3f(0.20f, 0.55f, 0.95f); glVertex2f(0.20f, -0.45f);
        glColor3f(0.20f, 0.55f, 0.95f); glVertex2f(0.85f, -0.45f);
        glColor3f(0.20f, 0.55f, 0.95f); glVertex2f(0.85f,  0.45f);
        glColor3f(0.20f, 0.55f, 0.95f); glVertex2f(0.20f,  0.45f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q11 - Two Quads in One Block");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
