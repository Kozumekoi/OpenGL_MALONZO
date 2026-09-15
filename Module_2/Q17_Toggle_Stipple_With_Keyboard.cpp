#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

bool stippleOn = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.75f, 0.95f);
    glLineWidth(4.0f);
    if (stippleOn) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.60f, -0.60f);
        glVertex2f( 0.60f, -0.60f);
        glVertex2f( 0.60f,  0.60f);
        glVertex2f(-0.60f,  0.60f);
    glEnd();
    if (stippleOn) glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 's' || key == 'S') {
        stippleOn = !stippleOn;
        glutPostRedisplay();
    }
    if (key == 27) std::exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Toggle Stipple (press S)");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
