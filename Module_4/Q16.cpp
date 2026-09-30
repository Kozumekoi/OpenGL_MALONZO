#include "common.h"

void display() {
    // glDrawArrays version: 6 vertices / 18 floats, with two duplicated corners.
    const GLfloat expanded[] = {
        -0.9f,-0.45f,0, -0.15f,-0.45f,0, -0.15f,0.45f,0,
        -0.9f,-0.45f,0, -0.15f,0.45f,0, -0.9f,0.45f,0
    };
    // glDrawElements version: 4 unique vertices / 12 floats plus six indices.
    const GLfloat corners[] = { 0.15f,-0.45f,0, 0.9f,-0.45f,0, 0.9f,0.45f,0, 0.15f,0.45f,0 };
    const GLubyte indices[] = { 0,1,2,0,2,3 };
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f,0.75f,1.0f); enableVertices(expanded); glDrawArrays(GL_TRIANGLES,0,6); disableVertices();
    glColor3f(1.0f,0.42f,0.2f); enableVertices(corners); glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,indices); disableVertices();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500); glutCreateWindow("Q16 - Array and Indexed Quad Comparison");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
