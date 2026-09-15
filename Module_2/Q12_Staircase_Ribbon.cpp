#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.75f, 0.45f);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(-0.85f, -0.65f); glVertex2f(-0.85f, -0.35f);
        glVertex2f(-0.30f, -0.65f); glVertex2f(-0.30f, -0.05f);
        glVertex2f( 0.25f, -0.65f); glVertex2f( 0.25f,  0.30f);
        glVertex2f( 0.80f, -0.65f); glVertex2f( 0.80f,  0.70f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 550);
    glutCreateWindow("Q12 - Staircase Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
