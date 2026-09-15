#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float centerX = 0.0f;
float centerY = 0.0f;
const float halfSize = 0.12f;
const float step = 0.08f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.75f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(centerX - halfSize, centerY - halfSize);
        glVertex2f(centerX + halfSize, centerY - halfSize);
        glVertex2f(centerX + halfSize, centerY + halfSize);
        glVertex2f(centerX - halfSize, centerY + halfSize);
    glEnd();
    glFlush();
}

void specialKeys(int key, int, int) {
    if (key == GLUT_KEY_LEFT)  centerX -= step;
    if (key == GLUT_KEY_RIGHT) centerX += step;
    if (key == GLUT_KEY_DOWN)  centerY -= step;
    if (key == GLUT_KEY_UP)    centerY += step;
    if (centerX < -1.0f + halfSize) centerX = -1.0f + halfSize;
    if (centerX >  1.0f - halfSize) centerX =  1.0f - halfSize;
    if (centerY < -1.0f + halfSize) centerY = -1.0f + halfSize;
    if (centerY >  1.0f - halfSize) centerY =  1.0f - halfSize;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Move Square with Arrow Keys");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
