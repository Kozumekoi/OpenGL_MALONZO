#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0f, 0.1f, 0.15f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.75f, -0.55f);
        glVertex2f( 0.25f, -0.55f);
        glVertex2f( 0.25f,  0.45f);
        glVertex2f(-0.75f,  0.45f);
    glEnd();

    glColor4f(0.1f, 0.35f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, -0.35f);
        glVertex2f( 0.75f, -0.35f);
        glVertex2f( 0.75f,  0.65f);
        glVertex2f(-0.25f,  0.65f);
    glEnd();

    glDisable(GL_BLEND);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Alpha-Blended Quads");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
