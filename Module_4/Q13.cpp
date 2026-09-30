#include "common.h"

void display() {
    // Nine unique points: one shared center and two outside points per blade.
    const GLfloat pool[] = { 0,0,0,  0,0.8f,0, 0.38f,0,0, 0.8f,0,0, 0,-0.38f,0,
                              0,-0.8f,0, -0.38f,0,0, -0.8f,0,0, 0,0.38f,0 };
    const GLubyte indices[] = { 0,1,2, 0,3,4, 0,5,6, 0,7,8 };
    glClear(GL_COLOR_BUFFER_BIT); enableVertices(pool);
    const GLfloat bladeColors[4][3] = { {1,0.25f,0.2f}, {0.25f,0.8f,1}, {1,0.8f,0.15f}, {0.6f,0.3f,1} };
    for (int i = 0; i < 4; ++i) {
        glColor3fv(bladeColors[i]); glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices + i * 3);
    }
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q13 - Indexed Pinwheel");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
