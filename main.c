#include <stdio.h>
#include <unistd.h>
#include "conio.h"

int main(void)
{
    int colors[] = {
        RED, YELLOW, LIGHTGREEN, LIGHTCYAN, LIGHTBLUE, LIGHTMAGENTA, WHITE
    };
    int backgrounds[] = {
        BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN
    };
    int steps = (int)(sizeof(colors) / sizeof(colors[0]));
    int i;

    clrscr();
    highvideo();
    textcolor(YELLOW);
    gotoxy(10, 2);
    cputs("Demo: proverka na funkciite ot conio.h");
    resetcolor();

    textcolor(LIGHTGRAY);
    gotoxy(8, 4);
    cputs("Tekstat shte smenya poziciya, cvyat i fon.");
    gotoxy(8, 5);
    cputs("Sled animaciyata shte ima test na putch, cprintf, getche i getch.");

    for (i = 0; i < steps; i++) {
        textcolor(colors[i]);
        textbackground(backgrounds[i]);
        gotoxy(10 + i * 7, 8 + i);
        cprintf(" Step %d ", i + 1);
        resetcolor();
        sleep(1);
    }

    gotoxy(8, 17);
    textcolor(WHITE);
    textbackground(BLUE);
    cputs(" textcolor + textbackground + gotoxy rabotyat ");
    resetcolor();

    gotoxy(8, 19);
    highvideo();
    textcolor(LIGHTGREEN);
    cputs("highvideo: yark tekst");
    resetcolor();

    gotoxy(8, 20);
    lowvideo();
    textcolor(LIGHTGREEN);
    cputs("lowvideo: priglushen tekst");
    resetcolor();

    gotoxy(8, 22);
    cputs("putch test: ");
    putch('O');
    putch('K');
    putch('!');

    gotoxy(8, 24);
    textcolor(LIGHTCYAN);
    cprintf("cprintf test: chislo=%d, tekst=%s", 123, "uspeshno");
    resetcolor();

    gotoxy(8, 26);
    cputs("getche test - natisni edin klavish: ");
    getche();

    gotoxy(8, 28);
    cputs("getch test - natisni edin klavish za krai (nyama da se pokazhe): ");
    getch();

    resetcolor();
    clrscr();
    gotoxy(1, 1);
    cputs("Demo priklyuchi uspeshno.\n");

    return 0;
}
