#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4.0f);

    glColor3f(0.2f, 0.8f, 0.9f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        glVertex2f(-0.85f,  0.35f);
        glVertex2f( 0.85f,  0.35f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glColor3f(1.0f, 0.45f, 0.15f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
    glBegin(GL_LINES);
        glVertex2f(-0.85f, -0.35f);
        glVertex2f( 0.85f, -0.35f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q14 - Two Stipple Patterns");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
