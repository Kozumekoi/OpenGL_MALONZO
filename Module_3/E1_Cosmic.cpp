#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

// Player
float shipX = 0.0f;
float shipY = -0.75f;
float shipSize = 0.12f;

// Asteroid 1
float asteroid1X = -0.45f;
float asteroid1Y = 1.10f;
float asteroid1Speed = 0.012f;

// Asteroid 2
float asteroid2X = 0.50f;
float asteroid2Y = 1.45f;
float asteroid2Speed = 0.020f;

int lives = 3;
int score = 0;
bool gameOver = false;

// Draw text
void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Draw spaceship using a triangle and a rectangle
void drawShip()
{
    // Ship body
    glColor3f(0.2f, 0.7f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(shipX, shipY + shipSize);
        glVertex2f(shipX - shipSize, shipY - shipSize);
        glVertex2f(shipX + shipSize, shipY - shipSize);
    glEnd();

    // Ship engine
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(shipX - 0.04f, shipY - shipSize);
        glVertex2f(shipX + 0.04f, shipY - shipSize);
        glVertex2f(shipX + 0.04f, shipY - shipSize - 0.08f);
        glVertex2f(shipX - 0.04f, shipY - shipSize - 0.08f);
    glEnd();
}

// Draw an asteroid as a simple polygon
void drawAsteroid(float x, float y)
{
    glColor3f(0.55f, 0.55f, 0.55f);

    glBegin(GL_POLYGON);
        glVertex2f(x - 0.10f, y);
        glVertex2f(x - 0.06f, y + 0.08f);
        glVertex2f(x + 0.03f, y + 0.10f);
        glVertex2f(x + 0.10f, y + 0.04f);
        glVertex2f(x + 0.08f, y - 0.06f);
        glVertex2f(x, y - 0.10f);
        glVertex2f(x - 0.09f, y - 0.06f);
    glEnd();
}

// Display score and lives
void drawHUD()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.92f, 0.88f, "COSMIC DODGER");
    drawText(-0.92f, 0.78f, "Score: " + to_string(score));
    drawText(-0.92f, 0.68f, "Lives: " + to_string(lives));
    drawText(-0.92f, -0.94f, "Move: W A S D    Restart: R");
}

// Simple distance collision check
bool checkCollision(float asteroidX, float asteroidY)
{
    float dx = shipX - asteroidX;
    float dy = shipY - asteroidY;
    float distance = sqrt(dx * dx + dy * dy);

    return distance < 0.18f;
}

// Reset asteroid to the top
void resetAsteroid1()
{
    asteroid1Y = 1.10f;
    asteroid1X = -0.75f + (rand() % 150) / 100.0f;
}

void resetAsteroid2()
{
    asteroid2Y = 1.25f;
    asteroid2X = -0.75f + (rand() % 150) / 100.0f;
}

// Reset entire game
void resetGame()
{
    shipX = 0.0f;
    shipY = -0.75f;

    asteroid1X = -0.45f;
    asteroid1Y = 1.10f;

    asteroid2X = 0.50f;
    asteroid2Y = 1.45f;

    lives = 3;
    score = 0;
    gameOver = false;

    cout << "Game restarted." << endl;
}

// Timer animation
void updateGame(int value)
{
    if (!gameOver)
    {
        asteroid1Y -= asteroid1Speed;
        asteroid2Y -= asteroid2Speed;

        // Asteroid reached the bottom: player gains a point
        if (asteroid1Y < -1.15f)
        {
            score++;
            resetAsteroid1();
        }

        if (asteroid2Y < -1.15f)
        {
            score++;
            resetAsteroid2();
        }

        // Collision with asteroid 1
        if (checkCollision(asteroid1X, asteroid1Y))
        {
            lives--;
            cout << "Hit by asteroid 1! Lives left: " << lives << endl;
            resetAsteroid1(); // prevents repeated life loss

            if (lives <= 0)
            {
                gameOver = true;
            }
        }

        // Collision with asteroid 2
        if (checkCollision(asteroid2X, asteroid2Y))
        {
            lives--;
            cout << "Hit by asteroid 2! Lives left: " << lives << endl;
            resetAsteroid2(); // prevents repeated life loss

            if (lives <= 0)
            {
                gameOver = true;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

void display()
{
    glClearColor(0.02f, 0.02f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver)
    {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawText(-0.45f, 0.10f, "GAME OVER");

        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-0.65f, -0.10f, "Press R to Restart");
    }
    else
    {
        drawShip();
        drawAsteroid(asteroid1X, asteroid1Y);
        drawAsteroid(asteroid2X, asteroid2Y);
        drawHUD();
    }

    glFlush();
}

// W A S D controls
void keyboard(unsigned char key, int x, int y)
{
    float moveSpeed = 0.08f;

    if (!gameOver)
    {
        switch (key)
        {
            case 'w':
            case 'W':
                shipY += moveSpeed;
                break;

            case 's':
            case 'S':
                shipY -= moveSpeed;
                break;

            case 'a':
            case 'A':
                shipX -= moveSpeed;
                break;

            case 'd':
            case 'D':
                shipX += moveSpeed;
                break;
        }

        // Keep ship inside the play area
        if (shipX < -0.85f) shipX = -0.85f;
        if (shipX > 0.85f) shipX = 0.85f;
        if (shipY < -0.80f) shipY = -0.80f;
        if (shipY > 0.65f) shipY = 0.65f;
    }

    if (key == 'r' || key == 'R')
    {
        resetGame();
    }

    if (key == 27)
    {
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Machine Problem 1 - Cosmic Dodger");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateGame, 0);

    glutMainLoop();

    return 0;
}