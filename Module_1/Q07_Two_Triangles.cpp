#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.75f, -0.4f);
        glVertex2f(-0.45f,  0.45f);
        glVertex2f(-0.15f, -0.4f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.45f,  0.45f);
        glVertex2f(0.75f, -0.4f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q07 - Two Triangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
