#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>

float colors[6][3] = {
    {1.0f, 0.2f, 0.2f}, {0.2f, 0.75f, 0.3f}, {0.2f, 0.4f, 1.0f},
    {1.0f, 0.85f, 0.2f}, {0.65f, 0.25f, 0.85f}, {0.1f, 0.75f, 0.8f}
};
const char* colorNames[6] = {"Red", "Green", "Blue", "Yellow", "Purple", "Cyan"};
int selected = 0;

void display() {
    glClearColor(colors[selected][0], colors[selected][1], colors[selected][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key >= '1' && key <= '6') {
        selected = key - '1';
        std::cout << "Background: " << colorNames[selected] << std::endl;
        glutPostRedisplay();
    }
    if (key == 27) std::exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 450);
    glutCreateWindow("Q19 - Color Picker (keys 1-6, ESC quits)");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
