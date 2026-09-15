#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.25f, 0.8f, 0.35f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.55f, -0.55f);
        glVertex2f( 0.55f, -0.55f);
        glVertex2f( 0.55f,  0.55f);
        glVertex2f(-0.55f,  0.55f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q04 - Square Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
