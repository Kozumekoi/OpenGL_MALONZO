# Module 2 Part B Solutions

This folder contains one standalone C++/FreeGLUT solution for each exercise Q01-Q20.

## Build on MSYS2 UCRT64

From the folder containing a source file, run:

```bash
g++ Q01_Plus_Shaped_Colored_Points.cpp -o Q01.exe -lfreeglut -lopengl32 -lglu32
./Q01.exe
```

Replace the filename and executable name for the exercise you want to run. In the course VS Code workspace, the provided Ctrl+Shift+B build task may be used instead.

## Interactive exercise

- Q17: Press S to toggle line stippling; ESC exits.

Some OpenGL core-profile implementations omit legacy line stippling and GL_QUADS. These exercises follow the manual's compatibility-profile FreeGLUT toolchain.
