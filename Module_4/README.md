# Module 4 — Computer Graphics and Visual Computing

Solutions for the manual's second set of 20 questions (Q01–Q20). Each exercise is a separate, standalone C++ program and demonstrates its named vertex array, indexed rendering, color array, or procedural geometry technique.

## Open in VS Code

1. Install VS Code's **C/C++** extension.
2. Install a C++ compiler and FreeGLUT. On Windows, use the **MSYS2 UCRT64** terminal and install the toolchain with:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-freeglut mingw-w64-ucrt-x86_64-gdb
   ```

3. Add `C:\msys64\ucrt64\bin` to your Windows PATH, then open this folder in VS Code.
4. Open any `Qxx.cpp`. Press **Ctrl+Shift+B** to build it, or run **Tasks: Run Task → Run Current OpenGL Exercise** to build and launch it. The launch configuration debugs the currently open exercise.

Linux builds use `g++` and the `glut`, `GLU`, and `GL` libraries. On macOS, use a FreeGLUT installation and adjust the link flags for that installation if needed.

## Exercises

| File | Topic |
|---|---|
| `Q01.cpp` | X pattern points with a vertex array |
| `Q02.cpp` | Filled hexagon |
| `Q03.cpp` | Two line segments, one array and draw call |
| `Q04.cpp` | Filled square and outline sharing one array |
| `Q05.cpp` | `GLint` coordinates with scaling |
| `Q06.cpp` | Indexed triangle with reordered indices |
| `Q07.cpp` | Per vertex color array |
| `Q08.cpp` | Three triangles in one draw call |
| `Q09.cpp` | Indexed triangle fan pentagon |
| `Q10.cpp` | Indexed checkerboard row with shared corners |
| `Q11.cpp` | Procedurally generated shaded circle |
| `Q12.cpp` | Interleaved position and color quad |
| `Q13.cpp` | Indexed four blade pinwheel |
| `Q14.cpp` | Colored staircase quad strip |
| `Q15.cpp` | Array based landscape scene |
| `Q16.cpp` | `glDrawArrays` and `glDrawElements` comparison |
| `Q17.cpp` | Procedural indexed gear |
| `Q18.cpp` | Keyboard switched triangle, quad, pentagon (`1`–`3`) |
| `Q19.cpp` | Interleaved indexed hexagon |
| `Q20.cpp` | Procedural flower scene |

The reusable compatibility-profile setup is in `common.h`. Generated binaries are written to `build/` and ignored by Git.

## Push to Git

This folder is part of the `OpenGL_MALONZO` repository. From the repository root, stage and push it with:

```bash
git add Module_4
git commit -m "Add Module 4 vertex array exercises"
git push origin main
```
