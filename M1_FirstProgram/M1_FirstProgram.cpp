#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
