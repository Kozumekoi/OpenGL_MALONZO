#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.8f, 0.9f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.85f,  0.45f);
        glVertex2f(-0.20f,  0.45f);
        glVertex2f( 0.45f, -0.65f);
        glVertex2f( 0.45f,  0.10f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q02 - Two Unconnected Lines");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
