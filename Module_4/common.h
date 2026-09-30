#pragma once

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// The exercises use the compatibility profile APIs taught in the manual.
inline void set2DView() {
    glClearColor(0.08f, 0.09f, 0.13f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

inline void enableVertices(const GLfloat* data) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, data);
}

inline void disableVertices() { glDisableClientState(GL_VERTEX_ARRAY); }

