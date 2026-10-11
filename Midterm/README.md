# Pokémon Field

Pokémon Field is a C++ 2D OpenGL game. The player follows a short Pokémon story, chooses a starter, explores the laboratory, and plays a soccer match against Arceus.

## Submission contents

- `main.cpp` - C++ source code.
- `stb_image.h` - image-loading library implementation used by the source.
- `assets/` - character and Pokémon images loaded by the program.
- `Pokemon_Field_Project_Documentation.pdf` - project documentation, including screenshots in Appendices A and B and 17 test cases.
- `Screenshots/` - the 26 individual screenshots included in the PDF appendices.
- `TEST_CASES.md` - a readable list of the documented functional checks.

## Build and run on Linux

Install a C++ compiler and FreeGLUT/OpenGL development libraries:

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev
```

From this folder, compile and run the program:

```bash
g++ -std=c++11 main.cpp -o PokemonField -lglut -lGL -lGLU
./PokemonField
```

Run the program from this folder so its relative `assets/...` image paths resolve correctly. The project uses compatibility-mode OpenGL functions provided by the system OpenGL and GLUT libraries.

## Controls

- **Enter** starts the story and advances dialogue. Enter confirms a player or rival name only after text has been entered.
- **W, A, S, D** move the player in the laboratory and on the field.
- **Left mouse click** on a Poké Ball opens starter selection; click Bidoof, Magikarp, or Caterpie to choose it.
- **Enter** starts the soccer match from the rival event and continues from victory to the closing screen.
- **R** restarts after defeat. **Enter** exits from defeat; **Enter** or **Escape** exits from the closing screen.

## ChatGPT conversation

The submitted conversation is available here: [Project conversation](codex://threads/01a11a07-7e2f-7192-8d61-4e7faedbc19f)

## Video demonstration

The 8–12 minute video demonstration still needs to be recorded and added to the submission. It is not included in this repository yet.

## Project repository

[OpenGL_MALONZO on GitHub](https://github.com/Kozumekoi/OpenGL_MALONZO)
