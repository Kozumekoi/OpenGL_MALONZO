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

using namespace std;

// 0 = Red, 1 = Green, 2 = Blue
int playerColor = 0;
int barrierColor = 0;

float playerX = 0.0f;
float playerY = -0.45f;
float playerSize = 0.14f;

float barrierY = 1.10f;
float barrierSpeed = 0.012f;

int score = 0;
bool gameOver = false;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void setColor(int colorCode)
{
    if (colorCode == 0)
        glColor3f(1.0f, 0.0f, 0.0f);
    else if (colorCode == 1)
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(0.0f, 0.4f, 1.0f);
}

string getColorName(int colorCode)
{
    if (colorCode == 0) return "RED";
    if (colorCode == 1) return "GREEN";
    return "BLUE";
}

void drawPlayer()
{
    setColor(playerColor);

    glBegin(GL_QUADS);
        glVertex2f(playerX - playerSize, playerY - playerSize);
        glVertex2f(playerX + playerSize, playerY - playerSize);
        glVertex2f(playerX + playerSize, playerY + playerSize);
        glVertex2f(playerX - playerSize, playerY + playerSize);
    glEnd();
}

void drawBarrier()
{
    setColor(barrierColor);

    // Horizontal barrier with a gap in the center
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, barrierY - 0.06f);
        glVertex2f(-0.23f, barrierY - 0.06f);
        glVertex2f(-0.23f, barrierY + 0.06f);
        glVertex2f(-1.0f, barrierY + 0.06f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.23f, barrierY - 0.06f);
        glVertex2f(1.0f, barrierY - 0.06f);
        glVertex2f(1.0f, barrierY + 0.06f);
        glVertex2f(0.23f, barrierY + 0.06f);
    glEnd();
}

void drawDashboard()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.94f, 0.88f, "CHROMA-SHIFT");
    drawText(-0.94f, 0.76f, "Score: " + to_string(score));
    drawText(-0.94f, 0.64f, "Player Color: " + getColorName(playerColor));

    drawText(-0.94f, -0.82f, "R = Red   G = Green   B = Blue");
    drawText(-0.94f, -0.92f, "Match barrier color to pass. Wrong color = GAME OVER.");
}

bool checkGateCollision()
{
    // The barrier reaches the player's vertical position
    return barrierY <= playerY + playerSize &&
           barrierY >= playerY - playerSize;
}

void spawnNextBarrier()
{
    barrierY = 1.10f;
    barrierColor = rand() % 3;
}

void resetGame()
{
    playerColor = 0;
    barrierColor = 0;
    barrierY = 1.10f;
    barrierSpeed = 0.012f;
    score = 0;
    gameOver = false;

    cout << "Game restarted." << endl;
}

void updateBarrier(int value)
{
    if (!gameOver)
    {
        barrierY -= barrierSpeed;

        if (checkGateCollision())
        {
            if (playerColor == barrierColor)
            {
                score++;
                cout << "Correct match! Score: " << score << endl;

                // Increase speed, but keep it playable
                barrierSpeed += 0.002f;

                if (barrierSpeed > 0.040f)
                {
                    barrierSpeed = 0.040f;
                }

                spawnNextBarrier();
            }
            else
            {
                gameOver = true;
                cout << "Wrong color. Game over!" << endl;
            }
        }

        // If barrier reaches the bottom, reset it
        if (barrierY < -1.10f)
        {
            spawnNextBarrier();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBarrier, 0);
}

void display()
{
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver)
    {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawText(-0.45f, 0.10f, "GAME OVER");

        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-0.62f, -0.10f, "Press R to Restart");
    }
    else
    {
        drawPlayer();
        drawBarrier();
        drawDashboard();
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'r':
        case 'R':
            if (gameOver)
                resetGame();
            else
                playerColor = 0;
            break;

        case 'g':
        case 'G':
            if (!gameOver)
                playerColor = 1;
            break;

        case 'b':
        case 'B':
            if (!gameOver)
                playerColor = 2;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Machine Problem 2 - Chroma Shift");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBarrier, 0);

    glutMainLoop();

    return 0;
}