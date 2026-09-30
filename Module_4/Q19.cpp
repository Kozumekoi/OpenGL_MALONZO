#include "common.h"

void display() {
    // Interleaved x,y,z,r,g,b records, indexed in polygon order.
    const GLfloat data[] = {
         0.0f, 0.75f,0, 1.0f,0.15f,0.15f,
         0.65f,0.38f,0, 1.0f,0.65f,0.1f,
         0.65f,-0.38f,0, 0.8f,1.0f,0.15f,
         0.0f,-0.75f,0, 0.1f,0.85f,0.35f,
        -0.65f,-0.38f,0, 0.1f,0.55f,1.0f,
        -0.65f,0.38f,0, 0.75f,0.25f,1.0f
    };
    const GLubyte indices[] = { 0,1,2,3,4,5 };
    const GLsizei stride = 6 * sizeof(GLfloat);
    glClear(GL_COLOR_BUFFER_BIT); glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3,GL_FLOAT,stride,data); glColorPointer(3,GL_FLOAT,stride,data+3);
    glDrawElements(GL_POLYGON,6,GL_UNSIGNED_BYTE,indices);
    glDisableClientState(GL_COLOR_ARRAY); glDisableClientState(GL_VERTEX_ARRAY); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q19 - Interleaved Indexed Hexagon");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
