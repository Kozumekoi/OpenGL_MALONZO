#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

const int STRIPE_COUNT = 9;
const float pi = 3.14159265f;

void drawStripes() {
    const float left = -0.9f, right = 0.9f;
    const float bottom = -0.75f, top = 0.75f;
    const float stripeHeight = (top - bottom) / STRIPE_COUNT;
    for (int i = 0; i < STRIPE_COUNT; ++i) {
        if (i % 2 == 0) glColor3f(0.85f, 0.1f, 0.18f);
        else glColor3f(1.0f, 1.0f, 1.0f);
        float y0 = bottom + i * stripeHeight;
        float y1 = y0 + stripeHeight;
        glBegin(GL_POLYGON);
            glVertex2f(left,  y0);
            glVertex2f(right, y0);
            glVertex2f(right, y1);
            glVertex2f(left,  y1);
        glEnd();
    }
}

void drawStar() {
    const float cx = -0.64f, cy = 0.48f;
    const float outerRadius = 0.20f;
    const float innerRadius = 0.085f;
    glColor3f(1.0f, 0.85f, 0.1f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; ++i) {
        float outerAngle = pi / 2.0f + i * 2.0f * pi / 5.0f;
        float innerAngle1 = outerAngle - pi / 5.0f;
        float innerAngle2 = outerAngle + pi / 5.0f;

        // One triangle forms each point of the star.
        glVertex2f(cx + outerRadius * std::cos(outerAngle),
                   cy + outerRadius * std::sin(outerAngle));
        glVertex2f(cx + innerRadius * std::cos(innerAngle1),
                   cy + innerRadius * std::sin(innerAngle1));
        glVertex2f(cx + innerRadius * std::cos(innerAngle2),
                   cy + innerRadius * std::sin(innerAngle2));

        // A second triangle fills the matching section of the center.
        glVertex2f(cx, cy);
        glVertex2f(cx + innerRadius * std::cos(innerAngle1),
                   cy + innerRadius * std::sin(innerAngle1));
        glVertex2f(cx + innerRadius * std::cos(innerAngle2),
                   cy + innerRadius * std::sin(innerAngle2));
    }
    glEnd();
}

void display() {
    glClearColor(0.12f, 0.18f, 0.28f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawStripes();
    drawStar();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 520);
    glutCreateWindow("Q20 - Procedural Striped Flag with Star");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
