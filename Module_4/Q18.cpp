#include "common.h"

const GLfloat triangle[] = { 0,0.72f,0, -0.7f,-0.55f,0, 0.7f,-0.55f,0 };
const GLfloat quad[] = { -0.65f,-0.55f,0, 0.65f,-0.55f,0, 0.65f,0.55f,0, -0.65f,0.55f,0 };
const GLfloat pentagon[] = { 0,0.75f,0, 0.71f,0.23f,0, 0.44f,-0.61f,0, -0.44f,-0.61f,0, -0.71f,0.23f,0 };
int selected = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.25f,0.8f,0.95f);
    if (selected == 1) { enableVertices(triangle); glDrawArrays(GL_TRIANGLES,0,3); }
    else if (selected == 2) { enableVertices(quad); glDrawArrays(GL_QUADS,0,4); }
    else { enableVertices(pentagon); glDrawArrays(GL_POLYGON,0,5); }
    disableVertices(); glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key >= '1' && key <= '3') { selected = key - '0'; glutPostRedisplay(); }
    if (key == 27) std::exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500); glutCreateWindow("Q18 - Press 1, 2, or 3 to Switch Shape");
    set2DView(); glutDisplayFunc(display); glutKeyboardFunc(keyboard); glutMainLoop(); return 0;
}
