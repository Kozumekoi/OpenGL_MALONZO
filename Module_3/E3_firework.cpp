#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int MAX_BURSTS = 10;

struct Burst
{
    bool active;
    int type;          // 1 = squares, 2 = diamonds, 3 = triangles
    float x;
    float y;
    float radius;
    float brightness;
};

Burst bursts[MAX_BURSTS];
int currentMode = 1;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

string modeName()
{
    if (currentMode == 1) return "Concentric Squares";
    if (currentMode == 2) return "Diamond Lattice";
    return "Starburst Triangles";
}

int activeBurstCount()
{
    int count = 0;

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
        {
            count++;
        }
    }

    return count;
}

void spawnBurst(int type)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (!bursts[i].active)
        {
            bursts[i].active = true;
            bursts[i].type = type;

            // Random position inside the play area
            bursts[i].x = -0.70f + (rand() % 140) / 100.0f;
            bursts[i].y = -0.55f + (rand() % 110) / 100.0f;

            bursts[i].radius = 0.03f;
            bursts[i].brightness = 1.0f;

            currentMode = type;
            cout << "Burst created." << endl;
            return;
        }
    }

    cout << "Maximum active bursts reached." << endl;
}

void drawSquares(const Burst& burst)
{
    glColor3f(burst.brightness, 0.3f * burst.brightness,
              1.0f * burst.brightness);

    for (int i = 1; i <= 3; i++)
    {
        float r = burst.radius * i;

        glBegin(GL_LINE_LOOP);
            glVertex2f(burst.x - r, burst.y - r);
            glVertex2f(burst.x + r, burst.y - r);
            glVertex2f(burst.x + r, burst.y + r);
            glVertex2f(burst.x - r, burst.y + r);
        glEnd();
    }
}

void drawDiamonds(const Burst& burst)
{
    glColor3f(0.2f * burst.brightness, 1.0f * burst.brightness,
              0.8f * burst.brightness);

    for (int i = 1; i <= 3; i++)
    {
        float r = burst.radius * i;

        glBegin(GL_LINE_LOOP);
            glVertex2f(burst.x, burst.y + r);
            glVertex2f(burst.x + r, burst.y);
            glVertex2f(burst.x, burst.y - r);
            glVertex2f(burst.x - r, burst.y);
        glEnd();
    }
}

void drawStarburst(const Burst& burst)
{
    glColor3f(1.0f * burst.brightness, 0.7f * burst.brightness,
              0.1f * burst.brightness);

    float r = burst.radius * 3.0f;

    // Eight triangles around the center
    for (int i = 0; i < 8; i++)
    {
        float angle1 = i * 45.0f * 3.14159f / 180.0f;
        float angle2 = (i + 1) * 45.0f * 3.14159f / 180.0f;

        glBegin(GL_TRIANGLES);
            glVertex2f(burst.x, burst.y);
            glVertex2f(burst.x + r * cos(angle1),
                       burst.y + r * sin(angle1));
            glVertex2f(burst.x + r * cos(angle2),
                       burst.y + r * sin(angle2));
        glEnd();
    }
}

void drawBurst(const Burst& burst)
{
    if (burst.type == 1)
    {
        drawSquares(burst);
    }
    else if (burst.type == 2)
    {
        drawDiamonds(burst);
    }
    else
    {
        drawStarburst(burst);
    }
}

void drawSidebar()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.95f, 0.88f, "FIREWORKS STUDIO");
    drawText(-0.95f, 0.76f, "1: Concentric Squares");
    drawText(-0.95f, 0.66f, "2: Diamond Lattice");
    drawText(-0.95f, 0.56f, "3: Starburst Triangles");
    drawText(-0.95f, 0.46f, "SPACE: Random Burst");

    drawText(-0.95f, -0.78f,
             "Active Bursts: " + to_string(activeBurstCount()));
    drawText(-0.95f, -0.90f, "Mode: " + modeName());
}

void updateBursts(int value)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
        {
            bursts[i].radius += 0.008f;
            bursts[i].brightness -= 0.012f;

            // Expire the burst after it fades
            if (bursts[i].brightness <= 0.0f)
            {
                bursts[i].active = false;
            }
        }
    }

    glutPostRedisplay();

    // Repeats animation continuously
    glutTimerFunc(16, updateBursts, 0);
}

void display()
{
    glClearColor(0.01f, 0.01f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
        {
            drawBurst(bursts[i]);
        }
    }

    drawSidebar();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            spawnBurst(1);
            break;

        case '2':
            spawnBurst(2);
            break;

        case '3':
            spawnBurst(3);
            break;

        case ' ':
            spawnBurst((rand() % 3) + 1);
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand(time(0));

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        bursts[i].active = false;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Machine Problem 3 - Fireworks Studio");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBursts, 0);

    glutMainLoop();

    return 0;
}