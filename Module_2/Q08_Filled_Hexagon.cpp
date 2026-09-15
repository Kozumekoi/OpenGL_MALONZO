#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.08f, 0.10f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.15f, 0.75f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f,  0.00f);
        glVertex2f(-0.28f,  0.52f);
        glVertex2f( 0.35f,  0.52f);
        glVertex2f( 0.62f,  0.00f);
        glVertex2f( 0.35f, -0.52f);
        glVertex2f(-0.28f, -0.52f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q08 - Filled Hexagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
