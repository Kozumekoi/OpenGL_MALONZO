#include "common.h"

constexpr int petalsCount = 10;
GLfloat petalVertices[petalsCount * 9];
GLfloat petalColors[petalsCount * 9];
GLfloat discVertices[(petalsCount + 2) * 3];
GLubyte discIndices[petalsCount + 2];

void buildFlower() {
    for (int i = 0; i < petalsCount; ++i) {
        const float a = 2.0f * 3.14159265f * i / petalsCount;
        const float half = 3.14159265f / petalsCount * 0.43f;
        const float angles[3] = { a, a - half, a + half };
        const float radii[3] = { 0.34f, 0.82f, 0.82f };
        const int base = i * 9;
        for (int j = 0; j < 3; ++j) {
            petalVertices[base + j*3] = radii[j] * std::cos(angles[j]);
            petalVertices[base + j*3 + 1] = 0.2f + radii[j] * std::sin(angles[j]);
            petalVertices[base + j*3 + 2] = 0.0f;
            petalColors[base + j*3] = 1.0f;
            petalColors[base + j*3 + 1] = 0.2f + 0.55f * (i % 2);
            petalColors[base + j*3 + 2] = 0.15f + 0.6f * ((i + 1) % 2);
        }
    }
    discVertices[0] = 0.0f; discVertices[1] = 0.2f; discVertices[2] = 0.0f; discIndices[0] = 0;
    for (int i = 0; i <= petalsCount; ++i) {
        const float a = 2.0f * 3.14159265f * i / petalsCount;
        const int p = (i + 1) * 3;
        discVertices[p] = 0.24f * std::cos(a); discVertices[p + 1] = 0.2f + 0.24f * std::sin(a); discVertices[p + 2] = 0.0f;
        discIndices[i + 1] = static_cast<GLubyte>(i + 1);
    }
}

void display() {
    const GLfloat ground[] = { -1,-0.72f,0, 1,-0.72f,0, 1,-0.95f,0, -1,-0.95f,0 };
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,petalVertices); glColorPointer(3,GL_FLOAT,0,petalColors);
    glDrawArrays(GL_TRIANGLES,0,petalsCount*3);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0f,0.78f,0.08f); enableVertices(discVertices);
    glDrawElements(GL_TRIANGLE_FAN,petalsCount+2,GL_UNSIGNED_BYTE,discIndices); disableVertices();
    glColor3f(0.18f,0.62f,0.25f); enableVertices(ground); glDrawArrays(GL_QUADS,0,4); disableVertices(); glFlush();
}

int main(int argc, char** argv) {
    buildFlower(); glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 600); glutCreateWindow("Q20 - Procedural Flower Scene");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
