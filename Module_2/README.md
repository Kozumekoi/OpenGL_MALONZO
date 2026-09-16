# Module 2 Part B Solutions

This folder contains one standalone C++/FreeGLUT solution for each exercise Q01-Q20.

## Build on Linux Mint

From the folder containing a source file, run:

```bash
g++ Q01_Plus_Shaped_Colored_Points.cpp -o Q01 -lglut -lGL -lGLU
./Q01
```

Replace the filename and executable name for the exercise you want to run. In the course VS Code workspace, the provided Ctrl+Shift+B build task may be used instead.

## Output Gallery

See [Module 2 Output Gallery](RESULTS.md) for the captured results. Q17 includes an MP4 demonstration of the keyboard-controlled stipple toggle.

## Interactive exercise

- Q17: Press S to toggle line stippling; ESC exits.

Some OpenGL core-profile implementations omit legacy line stippling and GL_QUADS. These exercises follow the manual's compatibility-profile FreeGLUT toolchain.
