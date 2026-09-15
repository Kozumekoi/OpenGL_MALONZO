#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255, 140, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f( 0.0f,  0.68f);
        glVertex2f(-0.65f, -0.48f);
        glVertex2f( 0.65f, -0.48f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q06 - Orange Triangle with glColor3ub");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
