#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    const int count = 4;
    const float start = -0.8f;
    const float size = 1.6f / count;
    for (int row = 0; row < count; ++row) {
        for (int col = 0; col < count; ++col) {
            if ((row + col) % 2 == 0) glColor3f(0.95f, 0.95f, 0.95f);
            else glColor3f(0.1f, 0.35f, 0.65f);
            float x0 = start + col * size;
            float y0 = start + row * size;
            glBegin(GL_POLYGON);
                glVertex2f(x0,        y0);
                glVertex2f(x0 + size, y0);
                glVertex2f(x0 + size, y0 + size);
                glVertex2f(x0,        y0 + size);
            glEnd();
        }
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - 4x4 Checkerboard");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
