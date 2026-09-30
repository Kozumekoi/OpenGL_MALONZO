#include "common.h"

void display() {
    const GLint triangle[] = { 0, 75,  -75, -55,  75, -55 };
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.9f, 0.3f, 0.75f);
    glPushMatrix(); glScalef(0.01f, 0.01f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY); glPopMatrix(); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q05 - GLint Triangle");
    set2DView(); glutDisplayFunc(display); glutMainLoop(); return 0;
}
