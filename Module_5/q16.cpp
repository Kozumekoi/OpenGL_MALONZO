#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>

void display();
void init();

GLuint sunV, sunI;
GLuint groundV, groundI;
GLuint leavesV, trunkV, cloudV, grassV;

void init() {
    // Eight-pronged sun star: one center plus alternating outer and inner points.
    GLfloat sun[51] = {-0.6f, 0.55f, 0.0f};
    GLubyte sunIndices[48];
    for (int i = 0; i < 16; ++i) {
        float angle = -1.5707963f + i * 3.14159265f / 8.0f;
        float radius = (i % 2 == 0) ? 0.23f : 0.10f;
        sun[3 + i * 3] = -0.6f + cosf(angle) * radius;
        sun[4 + i * 3] = 0.55f + sinf(angle) * radius;
        sun[5 + i * 3] = 0.0f;
        sunIndices[i * 3] = 0;
        sunIndices[i * 3 + 1] = i + 1;
        sunIndices[i * 3 + 2] = (i + 1) % 16 + 1;
    }

    GLfloat ground[] = {
        -1.0f, -0.85f, 0.0f,
         1.0f, -0.85f, 0.0f,
         1.0f, -0.45f, 0.0f,
        -1.0f, -0.45f, 0.0f
    };
    GLubyte groundIndices[] = {0, 1, 2, 0, 2, 3};

    GLfloat leaves[] = {
        0.20f, -0.25f, 0.0f,
        0.80f, -0.25f, 0.0f,
        0.50f,  0.48f, 0.0f
    };
    GLfloat trunk[] = {
        0.43f, -0.80f, 0.0f,
        0.57f, -0.80f, 0.0f,
        0.57f, -0.25f, 0.0f,
        0.43f, -0.25f, 0.0f
    };

    // Three overlapping triangle fans make a simple cloud from VBO geometry.
    GLfloat cloud[42 * 3];
    const float cloudX[] = {0.25f, 0.43f, 0.61f};
    const float cloudRadius[] = {0.12f, 0.16f, 0.12f};
    int cloudVertex = 0;
    for (int circle = 0; circle < 3; ++circle) {
        cloud[cloudVertex * 3] = cloudX[circle];
        cloud[cloudVertex * 3 + 1] = 0.62f;
        cloud[cloudVertex * 3 + 2] = 0.0f;
        ++cloudVertex;
        for (int point = 0; point <= 12; ++point) {
            float angle = point * 6.2831853f / 12.0f;
            cloud[cloudVertex * 3] = cloudX[circle] + cosf(angle) * cloudRadius[circle];
            cloud[cloudVertex * 3 + 1] = 0.62f + sinf(angle) * cloudRadius[circle];
            cloud[cloudVertex * 3 + 2] = 0.0f;
            ++cloudVertex;
        }
    }

    // Five small triangle blades repeated along the top of the ground.
    GLfloat grass[45];
    const float grassX[] = {-0.82f, -0.48f, -0.14f, 0.20f, 0.88f};
    for (int i = 0; i < 5; ++i) {
        int vertex = i * 9;
        grass[vertex] = grassX[i] - 0.10f;
        grass[vertex + 1] = -0.45f;
        grass[vertex + 2] = 0.0f;
        grass[vertex + 3] = grassX[i];
        grass[vertex + 4] = -0.29f;
        grass[vertex + 5] = 0.0f;
        grass[vertex + 6] = grassX[i] + 0.10f;
        grass[vertex + 7] = -0.45f;
        grass[vertex + 8] = 0.0f;
    }

    glGenBuffers(1, &sunV);
    glBindBuffer(GL_ARRAY_BUFFER, sunV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sun), sun, GL_STATIC_DRAW);
    glGenBuffers(1, &sunI);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunI);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sunIndices), sunIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &groundV);
    glBindBuffer(GL_ARRAY_BUFFER, groundV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);
    glGenBuffers(1, &groundI);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundI);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &leavesV);
    glBindBuffer(GL_ARRAY_BUFFER, leavesV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leaves), leaves, GL_STATIC_DRAW);
    glGenBuffers(1, &trunkV);
    glBindBuffer(GL_ARRAY_BUFFER, trunkV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trunk), trunk, GL_STATIC_DRAW);
    glGenBuffers(1, &cloudV);
    glBindBuffer(GL_ARRAY_BUFFER, cloudV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cloud), cloud, GL_STATIC_DRAW);
    glGenBuffers(1, &grassV);
    glBindBuffer(GL_ARRAY_BUFFER, grassV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grass), grass, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, groundV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundI);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.48f, 0.25f, 0.10f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, grassV);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.18f, 0.48f, 0.12f);
    glDrawArrays(GL_TRIANGLES, 0, 15);

    glBindBuffer(GL_ARRAY_BUFFER, trunkV);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.35f, 0.16f, 0.06f);
    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, leavesV);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.04f, 0.30f, 0.08f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, cloudV);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.92f, 0.95f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 14);
    glDrawArrays(GL_TRIANGLE_FAN, 14, 14);
    glDrawArrays(GL_TRIANGLE_FAN, 28, 14);

    glBindBuffer(GL_ARRAY_BUFFER, sunV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunI);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(1.0f, 0.72f, 0.05f);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Module 5 - Sun Ground and Tree");
#ifndef __APPLE__
    if (glewInit() != GLEW_OK) return 1;
#endif
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
