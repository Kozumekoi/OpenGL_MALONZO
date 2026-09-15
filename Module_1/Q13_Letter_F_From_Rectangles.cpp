#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawRect(float x0, float y0, float x1, float y1) {
    glBegin(GL_POLYGON);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.7f, 0.8f);
    drawRect(-0.55f, -0.75f, -0.30f, 0.75f);
    drawRect(-0.30f,  0.50f,  0.55f, 0.75f);
    drawRect(-0.30f, -0.05f,  0.35f, 0.20f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q13 - Letter F");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
