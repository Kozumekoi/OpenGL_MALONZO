#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.55f, 0.95f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.72f, -0.42f);
        glVertex2f(-0.72f,  0.42f);
        glVertex2f( 0.72f, -0.42f);
        glVertex2f( 0.72f,  0.42f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q09 - Rectangle from Triangle Strip");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
