# Conio-Like Console Library (Linux)

This project recreates classic `conio.h`-style console functions on Linux without using external UI libraries.
It uses ANSI escape codes for screen and color control, and POSIX `termios` + `fcntl` for keyboard input.

## Features Implemented

- Screen and cursor
  - `clrscr()`
  - `gotoxy(x, y)`
  - `wherex()`, `wherey()`
  - `insline()`, `deline()`
- Text attributes
  - `textcolor(color)`
  - `textbackground(color)`
  - `highvideo()` / `lowvideo()`
  - `resetcolor()`
- Keyboard input
  - `getch()`
  - `getche()`
  - `kbhit()`
- Output helpers
  - `putch(ch)`
  - `cputs(str)`
  - `cprintf(fmt, ...)`

## How It Works

1. ANSI escape sequences handle cursor positioning, screen clearing, line insert/delete, and colors.
2. `termios` switches the terminal to non-canonical mode for immediate key reads.
3. `fcntl` + `O_NONBLOCK` enables `kbhit`-style non-blocking input checks.

## Build (Linux)

```bash
gcc main.c -o conio_demo
```

## Run

```bash
./conio_demo
```

## Color Constants (0-15)

The library keeps classic DOS-style color indices and maps them to ANSI colors:

```
BLACK=0, BLUE=1, GREEN=2, CYAN=3, RED=4, MAGENTA=5, BROWN=6, LIGHTGRAY=7,
DARKGRAY=8, LIGHTBLUE=9, LIGHTGREEN=10, LIGHTCYAN=11, LIGHTRED=12,
LIGHTMAGENTA=13, YELLOW=14, WHITE=15
```

## Notes and Limitations

- Some terminals ignore blink and faint attributes.
- `wherex` / `wherey` rely on the ANSI cursor position query (`ESC[6n`).
- `kbhit` uses non-blocking input and restores terminal state after each call.

## Example Usage

```c
clrscr();
gotoxy(10, 5);
textcolor(RED);
textbackground(WHITE);
cprintf("Hello from conio-like API\n");
resetcolor();
```

## Suggested Next Steps

- Add a demo menu to exercise every function in one run.
- Add a small animation loop using `usleep` or `nanosleep`.
- Refactor into a header + source pair for reuse in multiple programs.
