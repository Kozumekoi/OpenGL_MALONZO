#include "common.h"

constexpr int teeth = 16;
GLfloat pool[(teeth + 1) * 3];
GLubyte evenIndices[(teeth / 2) * 3];
GLubyte oddIndices[(teeth / 2) * 3];

void buildGear() {
    pool[0] = pool[1] = pool[2] = 0.0f;
    for (int i = 0; i < teeth; ++i) {
        const float a = 2.0f * 3.14159265f * i / teeth;
        const float r = (i % 2 == 0) ? 0.78f : 0.55f;
        const int p = (i + 1) * 3;
        pool[p] = r * std::cos(a); pool[p + 1] = r * std::sin(a); pool[p + 2] = 0.0f;
        GLubyte* out = (i % 2 == 0) ? evenIndices : oddIndices;
        const int k = ((i / 2) * 3);
        out[k] = 0; out[k + 1] = static_cast<GLubyte>(i + 1);
        out[k + 2] = static_cast<GLubyte>(((i + 1) % teeth) + 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); enableVertices(pool);
    glColor3f(0.95f,0.36f,0.14f); glDrawElements(GL_TRIANGLES,teeth/2*3,GL_UNSIGNED_BYTE,evenIndices);
    glColor3f(0.2f,0.65f,1.0f); glDrawElements(GL_TRIANGLES,teeth/2*3,GL_UNSIGNED_BYTE,oddIndices);
    disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    buildGear(); glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q17 - Procedural Indexed Gear");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
