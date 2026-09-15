#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.7f, 0.8f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.6f,  0.0f);
        glVertex2f(-0.3f,  0.52f);
        glVertex2f( 0.3f,  0.52f);
        glVertex2f( 0.6f,  0.0f);
        glVertex2f( 0.3f, -0.52f);
        glVertex2f(-0.3f, -0.52f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q06 - Hexagon Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
