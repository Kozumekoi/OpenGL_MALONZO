#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.65f, 0.1f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.85f, -0.45f);
        glVertex2f(-0.50f,  0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f( 0.20f,  0.45f);
        glVertex2f( 0.55f, -0.45f);
        glVertex2f( 0.85f,  0.35f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q03 - Zig-Zag Line Strip");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
