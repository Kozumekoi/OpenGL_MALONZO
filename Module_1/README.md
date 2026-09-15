# Module 1 Part B Solutions

This folder contains one standalone C++/FreeGLUT solution for each exercise Q01-Q20.

## Build on MSYS2 UCRT64

From the folder containing a source file, run:

```bash
g++ Q01_Red_Center_Point.cpp -o Q01.exe -lfreeglut -lopengl32 -lglu32
./Q01.exe
```

Replace the filename and executable name for the exercise you want to run. In the course VS Code workspace, the provided Ctrl+Shift+B build task may be used instead.

## Interactive exercises

- Q15: Move the square with the arrow keys.
- Q17: Press N to advance the traffic light; ESC exits.
- Q19: Press 1-6 to select a background color; ESC exits.

Q16 and Q18 animate continuously.
