#include <GL/glut.h> // Provides OpenGL and GLUT functions.
#include <cstdlib>   // Provides exit().
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <cctype>
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

// gamestates for each scene
enum GameState {
    OPENING, PROF_DIALOGUE, NAME_PLAYER, NAME_RIVAL, FIRST_LAB, STARTER,
    SECOND_LAB, RIVAL_EVENT, FIELD, VICTORY, DEFEAT, CLOSING
};

GameState state = OPENING;
int dialogueIndex = 0;

string playerName, rivalName, starterChoice, nameInput;
GLuint bidoofTexture, arceusTexture, magikarpTexture, professor1Texture,
    professor2Texture, caterpieTexture, playerTexture, rivalTexture;
bool rivalEventStarted = false;

float playerX = 100.0f;
float playerY = 100.0f;

const float GOAL_BOTTOM = 240.0f;
const float GOAL_TOP = 360.0f;

float ballX = 400.0f, ballY = 300.0f;
float ballVX = 0.0f, ballVY = 0.0f;

float arceusX = 650.0f, arceusY = 300.0f;
int arceusKickCooldown = 0;
int arceusPause = 0;
const float PLAYER_START_X = 60.0f;
const float PLAYER_START_Y = 270.0f;

int playerGoals = 0;
int arceusGoals = 0;
const int GOALS_TO_WIN = 3;

void resetSoccerPositions();

struct Rect {
    float left, bottom, right, top;
};

const Rect labObstacles[] = {
    {40, 520, 760, 580}, // Top bookshelf
    {40, 340, 160, 460}, // Middle-left bookshelf
    {640, 340, 760, 460}, // Middle-right bookshelf
    {340, 420, 460, 455} // Table
};

const int LAB_OBSTACLE_COUNT =
    sizeof(labObstacles) / sizeof(labObstacles[0]);

const float playerSpeed = 10.0f;
int walkFrame = 0; // Which column to show.
int facingRow = 0; // Which direction row to show.

const int GRID_COLUMNS = 32;
const int GRID_ROWS = 24;
const int GRID_LINE_COUNT = GRID_COLUMNS + GRID_ROWS + 2;

GLfloat gridVertices[GRID_LINE_COUNT * 4];

// Function to draw text on the screen at a specified position and color.
void drawText(float x, float y, const char* text,
              float r = 1.0f, float g = 1.0f, float b = 1.0f) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
}

void drawRect(float left, float bottom, float right, float top) {
    glBegin(GL_QUADS); // Tell OpenGL to draw a four-sided shape.
    glVertex2f(left, bottom); // Add the lower-left corner.
    glVertex2f(right, bottom); // Add the lower-right corner.
    glVertex2f(right, top); // Add the upper-right corner.
    glVertex2f(left, top); // Add the upper-left corner.
    glEnd(); // Finish this shape.
}

void createLabGrid() {
    int i = 0;

    // Vertical grid lines.
    for (int col = 0; col <= GRID_COLUMNS; ++col) {
        float x = col * 25.0f;
        gridVertices[i++] = x;
        gridVertices[i++] = 0.0f;
        gridVertices[i++] = x;
        gridVertices[i++] = 600.0f;
    }

    // Horizontal grid lines.
    for (int row = 0; row <= GRID_ROWS; ++row) {
        float y = row * 25.0f;
        gridVertices[i++] = 0.0f;
        gridVertices[i++] = y;
        gridVertices[i++] = 800.0f;
        gridVertices[i++] = y;
    }
}

void drawLabTiles() {
    glColor3f(0.82f, 0.82f, 0.72f); // Muted beige floor.
    drawRect(0, 0, 800, 600);

    glColor3f(0.56f, 0.59f, 0.49f); // Subtle grout lines.
    glLineWidth(1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, gridVertices);
    glDrawArrays(GL_LINES, 0, GRID_LINE_COUNT * 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

GLuint loadTexture(const char* path) {
    int width, height, channels;

    // Load the PNG pixels and keep transparency by requesting RGBA. (in stb_image.h)
    stbi_uc* pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    if (!pixels) {
        cerr << "Could not load " << path << endl;
        return 0;
    }

    GLuint playerTexture = 0;

    GLuint texture;
    glGenTextures(1, &texture); // Create a texture ID.
    glBindTexture(GL_TEXTURE_2D, texture); // Make it the active texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels); // Upload PNG pixels.

    stbi_image_free(pixels); // Free the loaded pixel data.
    return texture; // Keep the OpenGL texture ID.
}

GLuint selectedStarterTexture() {
    if (starterChoice == "1") return bidoofTexture;
    if (starterChoice == "2") return magikarpTexture;
    if (starterChoice == "3") return caterpieTexture;
    return 0;
}

struct DialogueLine {
    const char* speaker;
    const char* text;
};

DialogueLine professorLines[] = {
    {"Professor Oak", "Hello there! Welcome to the world of Pokemon!"}, //0
    {"Professor Oak", "My name is Professor Oak. People call me the Pokemon Professor."}, //1
    {"Professor Oak", "This world is inhabited by creatures called Pokemon!"}, //2
    {"Professor Oak", "For some people, Pokemon are pets. Others use them for fights."}, //3
    {"Professor Oak", "Myself... I study Pokemon as a profession."}, //4
    {"Professor Oak", "First, what is your name?"}, //5
    {"Professor Oak", ""}, //6
    {"Professor Oak", "This is my grandson. He's been your rival since you were a baby. Erm, what is his name again?"}, //7
    {"Professor Oak", ""}, //8
    {"Professor Oak", ""}, //9
    {"Professor Oak", "Your very own Pokemon legend is about to unfold!"},
    {"Professor Oak", "A world of dreams and adventures with Pokemon awaits! Let's go!"} //11
};

string getProfessorLine(int index) {
    if (index == 6)
        return "Right! So your name is " + playerName;
    if (index == 8)
        return "That's right! I remember now! His name is " + rivalName;
    if (index == 9)
        return playerName + "!";

    return professorLines[index].text;
}

void drawSprite(GLuint texture, float x, float y, float w, float h) {
    if (texture == 0) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + w, y);
    glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
    glTexCoord2f(0, 1); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawSpriteFrame(GLuint texture, float x, float y, float w, float h,
                     int column, int row) {
    if (texture == 0) return;

    float u0 = column / 4.0f;
    float u1 = (column + 1) / 4.0f;
    float v0 = 1.0f - (row + 1) / 4.0f;
    float v1 = 1.0f - row / 4.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(u0, v0); glVertex2f(x, y);
    glTexCoord2f(u1, v0); glVertex2f(x + w, y);
    glTexCoord2f(u1, v1); glVertex2f(x + w, y + h);
    glTexCoord2f(u0, v1); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawBookshelf(const Rect& shelf) {
    glColor3f(0.30f, 0.18f, 0.10f);
    drawRect(shelf.left, shelf.bottom, shelf.right, shelf.top);

    // Repeated colored book spines.
    int book = 0;
    for (float x = shelf.left + 7; x < shelf.right - 12; x += 16) {
        switch (book % 4) {
            case 0: glColor3f(0.65f, 0.16f, 0.12f); break;
            case 1: glColor3f(0.12f, 0.35f, 0.55f); break;
            case 2: glColor3f(0.78f, 0.62f, 0.20f); break;
            default: glColor3f(0.18f, 0.42f, 0.22f); break;
        }

        drawRect(x, shelf.bottom + 7, x + 10, shelf.top - 7);
        ++book;
    }

    // Shelf edge.
    glColor3f(0.48f, 0.29f, 0.16f);
    drawRect(shelf.left, shelf.bottom, shelf.right, shelf.bottom + 6);
}

void drawSquarePokeball(float x, float y, float size) {
    glColor3f(0.85f, 0.12f, 0.12f);
    drawRect(x, y + size / 2, x + size, y + size);

    glColor3f(0.95f, 0.95f, 0.90f);
    drawRect(x, y, x + size, y + size / 2);

    glColor3f(0.10f, 0.10f, 0.10f);
    drawRect(x, y + size / 2 - 2, x + size, y + size / 2 + 2);

    // Square center button.
    glColor3f(0.10f, 0.10f, 0.10f);
    drawRect(x + size * 0.36f, y + size * 0.36f,
             x + size * 0.64f, y + size * 0.64f);
    glColor3f(0.95f, 0.95f, 0.90f);
    drawRect(x + size * 0.41f, y + size * 0.41f,
             x + size * 0.59f, y + size * 0.59f);
}

void drawLabFurniture(bool showPokeballs) {
    drawBookshelf(labObstacles[0]);
    drawBookshelf(labObstacles[1]);
    drawBookshelf(labObstacles[2]);

    // Table beneath the Poké Balls.
    glColor3f(0.48f, 0.29f, 0.16f);
    drawRect(340, 420, 460, 455);
    glColor3f(0.66f, 0.44f, 0.25f);
    drawRect(330, 450, 470, 462);

    // Professor stands in the open space above the left shelf.
    drawSprite(professor2Texture, 205, 430, 60, 80);

    if (showPokeballs) {
        drawSquarePokeball(350, 462, 22);
        drawSquarePokeball(389, 462, 22);
        drawSquarePokeball(428, 462, 22);
    }
}

bool blockedByFurniture(float x, float y) {
    // Slightly inset the player collision box inside the 60x60 sprite.
    float playerLeft = x + 8;
    float playerRight = x + 52;
    float playerBottom = y + 8;
    float playerTop = y + 52;

    for (int i = 0; i < LAB_OBSTACLE_COUNT; ++i) {
        const Rect& obstacle = labObstacles[i];

        if (playerRight > obstacle.left &&
            playerLeft < obstacle.right &&
            playerTop > obstacle.bottom &&
            playerBottom < obstacle.top) {
            return true;
        }
    }

    return false;
}

bool inside(float mouseX, float mouseY, float left, float bottom,
            float right, float top) {
    return mouseX >= left && mouseX <= right &&
           mouseY >= bottom && mouseY <= top;
}

void drawOutlinedRect(float left, float bottom, float right, float top) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
}

void drawSoccerField() {
    // Grass background and white field markings.
    glColor3f(0.34f, 0.53f, 0.25f);
    drawRect(0, 0, 800, 600);

    glColor3f(0.94f, 0.95f, 0.88f);
    glLineWidth(5.0f);

    // Outer boundary and halfway line.
    drawOutlinedRect(24, 24, 776, 576);

    glBegin(GL_LINES);
    glVertex2f(400, 24);
    glVertex2f(400, 576);
    glEnd();

    // Center circle.
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 48; ++i) {
        float angle = 2.0f * 3.14159265f * i / 48.0f;
        glVertex2f(400 + 72 * std::cos(angle),
                   300 + 72 * std::sin(angle));
    }
    glEnd();

    // Penalty areas.
    drawOutlinedRect(24, 150, 145, 450);
    drawOutlinedRect(655, 150, 776, 450);

    // Short horizontal goal markers at the center of both ends.
    drawRect(24, GOAL_BOTTOM, 36, GOAL_TOP);
    drawRect(764, GOAL_BOTTOM, 776, GOAL_TOP);

    glLineWidth(1.0f);
}

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 32; ++i) {
        float angle = 2.0f * 3.14159265f * i / 32.0f;
        glVertex2f(x + radius * std::cos(angle),
                   y + radius * std::sin(angle));
    }
    glEnd();
}

void drawSoccerBall() {
    glColor3f(0.96f, 0.96f, 0.90f);
    drawCircle(ballX, ballY, 12);

    glColor3f(0.12f, 0.12f, 0.12f);
    drawCircle(ballX, ballY, 3);
}

void resolveBallVsRect(float left, float bottom, float right, float top) {
    const float radius = 12.0f;

    float closestX = ballX;
    if (closestX < left) closestX = left;
    if (closestX > right) closestX = right;

    float closestY = ballY;
    if (closestY < bottom) closestY = bottom;
    if (closestY > top) closestY = top;

    float dx = ballX - closestX;
    float dy = ballY - closestY;
    float distanceSquared = dx * dx + dy * dy;

    if (distanceSquared >= radius * radius)
        return;

    float nx, ny, distance, overlap;

    if (distanceSquared > 0.0001f) {
        distance = std::sqrt(distanceSquared);
        nx = dx / distance;
        ny = dy / distance;
        overlap = radius - distance;
    } else {
        // Ball center is inside the rectangle: move it out through the nearest side.
        float gaps[] = {
            ballX - left, right - ballX,
            ballY - bottom, top - ballY
        };

        int side = 0;
        for (int i = 1; i < 4; ++i)
            if (gaps[i] < gaps[side]) side = i;

        nx = (side == 0) ? -1.0f : (side == 1) ? 1.0f : 0.0f;
        ny = (side == 2) ? -1.0f : (side == 3) ? 1.0f : 0.0f;
        overlap = radius + gaps[side];
    }

    // Push the ball outside the Pokémon and bounce it if moving into it.
    ballX += nx * overlap;
    ballY += ny * overlap;

    float velocityIntoPokemon = ballVX * nx + ballVY * ny;
    if (velocityIntoPokemon < 0.0f) {
        ballVX -= 2.0f * velocityIntoPokemon * nx;
        ballVY -= 2.0f * velocityIntoPokemon * ny;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the previous frame.

    if (state == OPENING) { // Draw according to the current state.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the background to black.
        glClear(GL_COLOR_BUFFER_BIT); // Clear again so the new color appears.
        drawText(330, 330, "Pokemon Field");
        drawText(300, 290, "Press ENTER to start");
    } else if (state == PROF_DIALOGUE) {
        drawSprite(professor1Texture, 270, 190, 260, 350);
        glColor3f(0.0f, 0.0f, 0.0f); // Set the text color to black.
        drawRect(30, 25, 770, 150);

        string line = getProfessorLine(dialogueIndex);
        drawText(55, 110, professorLines[dialogueIndex].speaker);
        drawText(55, 80, line.c_str());
        drawText(620, 50, "ENTER: Continue");
    } else if (state == NAME_PLAYER || state == NAME_RIVAL) {
        glColor3f(0.0f, 0.0f, 0.0f); // Set the text color to black.
        drawRect(30, 25, 770, 150);

        if (state == NAME_PLAYER)
            drawText(55, 100, "Enter the player name:");
        else
            drawText(55, 100, "Enter the rival name:");

        drawText(55, 70, nameInput.c_str());
        drawText(620, 45, "ENTER: Confirm");
    } else if (state == FIRST_LAB) {
        drawLabTiles(); // Draw the lab floor and grid.
        drawLabFurniture(true); // Show the three Poké Balls.
        drawSpriteFrame(playerTexture, playerX, playerY, 60, 60,
                        walkFrame, facingRow);

        glColor3f(0.95f, 0.92f, 0.80f);
        drawRect(30, 20, 770, 75);

        drawText(50, 52, "Move using W, A, S, D", 0.0f, 0.0f, 0.0f);
        drawText(50, 32, "Pick your Pokemon by clicking on the table",
                 0.0f, 0.0f, 0.0f);
    } else if (state == STARTER) {
        drawLabTiles();
        drawSprite(bidoofTexture, 100, 280, 120, 120);
        drawSprite(magikarpTexture, 340, 280, 120, 120);
        drawSprite(caterpieTexture, 580, 280, 120, 120);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(120, 250, "1: Bidoof", 0.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(350, 250, "2: Magikarp", 0.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(590, 250, "3: Caterpie", 0.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(270, 100, "Click a Pokemon to choose", 0.0f, 0.0f, 0.0f);
    } else if (state == SECOND_LAB) {
        drawLabTiles();
        drawLabFurniture(false); // Hide Poké Balls after the choice.
        drawSpriteFrame(playerTexture, playerX, playerY, 60, 60,
                        walkFrame, facingRow);
        glColor3f(0.95f, 0.92f, 0.80f);
        drawRect(20, 15, 330, 75);

        drawText(35, 42, "Try moving around and find the exit", 0.0f, 0.0f, 0.0f);
                        
    } else if (state == RIVAL_EVENT) {
        drawLabTiles();
        drawLabFurniture(false);
        drawSprite(rivalTexture, 560, 300, 60, 80);

        glColor3f(0.95f, 0.92f, 0.80f);
        drawRect(30, 25, 770, 150);

        drawText(55, 110, rivalName.c_str(), 0.0f, 0.0f, 0.0f);
        drawText(55, 80, "You finally picked a Pokemon? Let's battle!", 0.0f, 0.0f, 0.0f);
        drawText(620, 45, "Press ENTER", 0.0f, 0.0f, 0.0f);
    } else if (state == FIELD) {
        drawSoccerField();

        drawSprite(arceusTexture, arceusX - 36, arceusY - 36, 72, 72);
        drawSoccerBall();

        // Starter PNGs are static, so draw the full image.
        drawSprite(selectedStarterTexture(), playerX, playerY, 60, 60);

        char scoreText[80];
        std::snprintf(scoreText, sizeof(scoreText),
                      "You: %d   Arceus: %d   First to 3 wins",
                      playerGoals, arceusGoals);
        drawText(300, 580, scoreText);
    } else if (state == VICTORY) {
        drawSoccerField();
        drawSoccerBall();
        drawText(340, 310, "You scored 3 goals! You win!", 0.0f, 0.0f, 0.0f);
        drawText(340, 280, "Press ENTER to continue", 0.0f, 0.0f, 0.0f);
    } else if (state == DEFEAT) {
        drawSoccerField();

        // Dark panel makes the white text readable.
        glColor3f(0.10f, 0.10f, 0.10f);
        drawRect(250, 240, 550, 360);

        drawText(350, 320, "Arceus scored 3 goals!", 1.0f, 1.0f, 1.0f);
        drawText(280, 285, "R: Try again   ENTER: Quit", 1.0f, 1.0f, 1.0f);
    } else if (state == CLOSING) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set a dark background for closing.
        glClear(GL_COLOR_BUFFER_BIT); // Apply the closing background color.
        drawText(400, 320, "Thanks for playing!");
        drawText(335, 280, "Press ENTER or ESC to exit"); // Show a closing message.
    }

    glutSwapBuffers(); // Show the completed frame.
}

void mouse(int button, int action, int mouseX, int mouseY) {
    if (button != GLUT_LEFT_BUTTON || action != GLUT_DOWN)
        return;

    float x = static_cast<float>(mouseX);
    float y = 600.0f - mouseY;

    if (state == FIRST_LAB) {
        if (inside(x, y, 350, 462, 372, 484) ||
            inside(x, y, 389, 462, 411, 484) ||
            inside(x, y, 428, 462, 450, 484)) {
            starterChoice.clear();
            state = STARTER;
            glutPostRedisplay();
        }
        return;
    }

    if (state == STARTER) {
        if (inside(x, y, 100, 280, 220, 400))
            starterChoice = "1"; // Bidoof
        else if (inside(x, y, 340, 280, 460, 400))
            starterChoice = "2"; // Magikarp
        else if (inside(x, y, 580, 280, 700, 400))
            starterChoice = "3"; // Caterpie
        else
            return;

        state = SECOND_LAB;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int mouseX, int mouseY) {
    if (key == 27) { // ASCII 27 is the Escape key.
        std::exit(0); // Close the program.
    }

    if (state == DEFEAT && (key == 'r' || key == 'R')) {
        playerGoals = 0;
        arceusGoals = 0;
        playerX = 60.0f;
        playerY = 270.0f;
        resetSoccerPositions();
        state = FIELD;
        glutPostRedisplay();
        return;
    }

    if (state == DEFEAT && key == 13) {
    std::exit(0);
    }

    if (state == NAME_PLAYER || state == NAME_RIVAL) {
        if (key == 13 && !nameInput.empty()) {
            if (state == NAME_PLAYER) {
                playerName = nameInput;
                dialogueIndex = 6;
            } else {
                rivalName = nameInput;
                dialogueIndex = 8;
            }

            nameInput.clear();
            state = PROF_DIALOGUE;
        } else if (key == 8 || key == 127) {
            if (!nameInput.empty())
                nameInput.pop_back();
        } else if (isprint(static_cast<unsigned char>(key)) &&
                   nameInput.length() < 12) {
            nameInput += static_cast<char>(key);
        }

        glutPostRedisplay();
        return;
    }

    if (state == FIRST_LAB || state == SECOND_LAB || state == FIELD) {
        float nextX = playerX;
        float nextY = playerY;
        bool moved = false;

        if (key == 'w' || key == 'W') {
            nextY += playerSpeed * 1.5f;
            facingRow = 3; // Set to the sheet's up-facing row.
            moved = true;
        } else if (key == 's' || key == 'S') {
            nextY -= playerSpeed * 1.5f;
            facingRow = 0; // Set to the down-facing row.
            moved = true;
        } else if (key == 'a' || key == 'A') {
            nextX -= playerSpeed;
            facingRow = 1; // Set to the left-facing row.
            moved = true;
        } else if (key == 'd' || key == 'D') {
            nextX += playerSpeed;
            facingRow = 2; // Set to the right-facing row.
            moved = true;
        }

        if (state == SECOND_LAB &&
            (key == 's' || key == 'S') &&
            nextY <= 80 &&
            !rivalEventStarted) {
            rivalEventStarted = true;
            state = RIVAL_EVENT;
            glutPostRedisplay();
            return;
        }

        if (moved) {
            // Keep the 60x60 sprite inside the 800x600 window.
            if (nextX < 0) nextX = 0;
            if (nextX > 740) nextX = 740;
            if (nextY < 0) nextY = 0;
            if (nextY > 540) nextY = 540;

            bool inLab = (state == FIRST_LAB || state == SECOND_LAB);

            if ((!inLab || !blockedByFurniture(nextX, nextY)) &&
                (nextX != playerX || nextY != playerY)) {
                playerX = nextX;
                playerY = nextY;
                walkFrame = (walkFrame + 1) % 4;
            }

            if (state == FIELD &&
                std::fabs((nextX + 30.0f) - ballX) < 42.0f &&
                std::fabs((nextY + 30.0f) - ballY) < 42.0f) {
                if (key == 'a' || key == 'A') ballVX = -5.0f;
                if (key == 'd' || key == 'D') ballVX = 5.0f;
                if (key == 'w' || key == 'W') ballVY = 5.0f;
                if (key == 's' || key == 'S') ballVY = -5.0f;
            }

            glutPostRedisplay();
            return;
        }
    }

    if (key == 13 && state == OPENING) {
        state = PROF_DIALOGUE;
        dialogueIndex = 0;
    } else if (key == 13 && state == PROF_DIALOGUE) {
        if (dialogueIndex == 5)
            state = NAME_PLAYER;
        else if (dialogueIndex == 7)
            state = NAME_RIVAL;
        else if (dialogueIndex == 11)
            state = FIRST_LAB;
        else
            dialogueIndex++;
    }

    if (key == 13 && state == RIVAL_EVENT) {
        playerGoals = 0;
        arceusGoals = 0;
        resetSoccerPositions();
        state = FIELD;
        glutPostRedisplay();
        return;
    }

    if (key == 13 && state == VICTORY) {
        state = CLOSING;
        glutPostRedisplay();
        return;
    }

    if (key == 13 && state == CLOSING) {
        std::exit(0);
    }
    glutPostRedisplay();
}


void resetSoccerPositions() {
    ballX = 400.0f;
    ballY = 300.0f;
    ballVX = 0.0f;
    ballVY = 0.0f;
    arceusX = 650.0f;
    arceusY = 300.0f;
    arceusKickCooldown = 0;
    arceusPause = 0;
    playerX = PLAYER_START_X;
    playerY = PLAYER_START_Y;
}

void updateField(int) {
    if (state == FIELD) {
        float dx = ballX - arceusX;
        float dy = ballY - arceusY;
        float distance = std::sqrt(dx * dx + dy * dy);

        // Arceus moves toward the ball.
        if (arceusPause > 0) {
            --arceusPause;
        } else {
            float dx = ballX - arceusX;
            float dy = ballY - arceusY;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance > 55.0f) {
                arceusX += (dx / distance) * 1.5f;
                arceusY += (dy / distance) * 1.5f;
            } else if (arceusKickCooldown <= 0) {
                ballVX = -5.0f;
                ballVY = (300.0f - ballY) * 0.04f;
                arceusKickCooldown = 45;
                arceusPause = 35; // About 1.2 seconds at a 33 ms timer.
            }
        }

        if (arceusKickCooldown > 0)
            --arceusKickCooldown;

        if (arceusX < 60.0f) arceusX = 60.0f;
        if (arceusX > 740.0f) arceusX = 740.0f;
        if (arceusY < 60.0f) arceusY = 60.0f;
        if (arceusY > 540.0f) arceusY = 540.0f;

        ballX += ballVX;
        ballY += ballVY;

        // Slow the ball gradually.
        ballVX *= 0.985f;
        ballVY *= 0.985f;

        // Ball collides with the player Pokémon and Arceus.
        resolveBallVsRect(playerX, playerY, playerX + 60, playerY + 60);
        resolveBallVsRect(arceusX - 36, arceusY - 36,
                          arceusX + 36, arceusY + 36);

        // Player scores at the right goal.
        if (ballX >= 764.0f &&
            ballY >= GOAL_BOTTOM && ballY <= GOAL_TOP) {
            ++playerGoals;
            resetSoccerPositions();

            if (playerGoals >= GOALS_TO_WIN)
                state = VICTORY;
        }
        // Arceus scores at the left goal.
        else if (ballX <= 36.0f &&
                 ballY >= GOAL_BOTTOM && ballY <= GOAL_TOP) {
            ++arceusGoals;
            resetSoccerPositions();

            if (arceusGoals >= GOALS_TO_WIN)
                state = DEFEAT;
        } else {
            // Bounce off the top and bottom field lines.
            if (ballY < 36.0f) {
                ballY = 36.0f;
                ballVY = std::fabs(ballVY) * 0.8f;
            } else if (ballY > 564.0f) {
                ballY = 564.0f;
                ballVY = -std::fabs(ballVY) * 0.8f;
            }

            // Bounce off the end lines if the ball missed the goal opening.
            if (ballX < 36.0f) {
                ballX = 36.0f;
                ballVX = std::fabs(ballVX) * 0.8f;
            } else if (ballX > 764.0f) {
                ballX = 764.0f;
                ballVX = -std::fabs(ballVX) * 0.8f;
            }
        }

        glutPostRedisplay();
    }

    glutTimerFunc(33, updateField, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT using the program arguments.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Use smooth double-buffered color.
    glutInitWindowSize(800, 600); // Set the starting window dimensions.
    glutCreateWindow("Pokemon Field"); // Create the game window.

    glEnable(GL_BLEND); // Allow PNG transparency.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(true); // Match image orientation to OpenGL.
    professor1Texture = loadTexture("assets/professor1.png");
    professor2Texture = loadTexture("assets/professor2.png");
    playerTexture = loadTexture("assets/player.png");
    rivalTexture = loadTexture("assets/rival.png");
    magikarpTexture = loadTexture("assets/magikarp.png");
    caterpieTexture = loadTexture("assets/caterpie.png");
    bidoofTexture = loadTexture("assets/bidoof.png");
    arceusTexture = loadTexture("assets/arceus.png");

    createLabGrid();

    glMatrixMode(GL_PROJECTION); // Set up how 2D coordinates map to the window.
    glLoadIdentity(); // Reset the projection settings.
    glOrtho(0, 800, 0, 600, -1, 1); // Use window-like coordinates: x 0–800, y 0–600.
    glMatrixMode(GL_MODELVIEW); // Select the matrix used for drawing objects.
    glLoadIdentity(); // Start with no extra transformations.

    glutDisplayFunc(display); // Tell GLUT which function draws each frame.
    glutKeyboardFunc(keyboard); // Tell GLUT which function handles keyboard input.
    glutMouseFunc(mouse);
    glutTimerFunc(33, updateField, 0);
    glutMainLoop(); // Start waiting for input and drawing frames.

    return 0; // Marks normal program completion.
}