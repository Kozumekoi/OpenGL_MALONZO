#include "common.h"

constexpr int segments = 48;
GLfloat vertices[(segments + 2) * 3];
GLfloat colors[(segments + 2) * 3];

void buildCircle() {
    vertices[0] = vertices[1] = vertices[2] = 0.0f;
    colors[0] = 1.0f; colors[1] = 1.0f; colors[2] = 1.0f;
    for (int i = 0; i <= segments; ++i) {
        const float a = 2.0f * 3.14159265f * i / segments;
        const int p = (i + 1) * 3;
        vertices[p] = 0.72f * std::cos(a); vertices[p + 1] = 0.72f * std::sin(a); vertices[p + 2] = 0.0f;
        colors[p] = 0.5f + 0.5f * std::cos(a);
        colors[p + 1] = 0.5f + 0.5f * std::cos(a - 2.0943951f);
        colors[p + 2] = 0.5f + 0.5f * std::cos(a + 2.0943951f);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices); glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY); glFlush();
}

int main(int argc, char** argv) {
    buildCircle(); glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q11 - Procedural Shaded Circle");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
