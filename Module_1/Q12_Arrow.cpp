#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.3f, 0.1f);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.75f, 0.0f);
        glVertex2f( 0.35f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(0.75f,  0.0f);
        glVertex2f(0.30f,  0.35f);
        glVertex2f(0.30f, -0.35f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q12 - Arrow");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
