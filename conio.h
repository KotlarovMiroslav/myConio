#ifndef conio_h
#define conio_h

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15

#define KEY_UP       256
#define KEY_DOWN     257
#define KEY_RIGHT    258
#define KEY_LEFT     259
#define KEY_HOME     260
#define KEY_END      261
#define KEY_INSERT   262
#define KEY_DELETE   263
#define KEY_PAGEUP   264
#define KEY_PAGEDOWN 265
#define KEY_F1       266
#define KEY_F2       267
#define KEY_F3       268
#define KEY_F4       269
#define KEY_F5       270
#define KEY_F6       271
#define KEY_F7       272
#define KEY_F8       273
#define KEY_F9       274
#define KEY_F10      275
#define KEY_F11      276
#define KEY_F12      277

void textcolor(int color);
void textbackground(int color);
void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void deline();
void insline();
void highvideo();
void lowvideo();
int getch();
int getche();
int kbhit();
void resetcolor();
int putch(int ch);
int cputs(const char *str);
int cprintf(const char *fmt, ...);

#endif /* conio_h */
