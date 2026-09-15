#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.2f, 0.2f); glVertex2f( 0.0f,  0.0f);
        glColor3f(0.2f, 1.0f, 0.2f); glVertex2f( 0.0f,  0.45f);
        glColor3f(0.2f, 0.4f, 1.0f); glVertex2f( 0.0f, -0.45f);
        glColor3f(1.0f, 0.8f, 0.1f); glVertex2f(-0.45f, 0.0f);
        glColor3f(0.8f, 0.2f, 1.0f); glVertex2f( 0.45f, 0.0f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q01 - Plus-Shaped Colored Points");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
