#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.55f, 0.25f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(-0.65f, -0.45f);
        glVertex2f( 0.55f, -0.58f);
        glVertex2f( 0.72f,  0.48f);
        glVertex2f(-0.48f,  0.65f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q07 - One Quadrilateral");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
