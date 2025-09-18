#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <ncurses.h>
    #include <unistd.h>
#endif

#define MAX_RAGE 100

int rage = 0;

const char* calm_messages[] = {
    "Take a deep breath...",
    "Relax your shoulders.",
    "It’s okay — slow down.",
    "Stretch for a moment.",
    "Sip some water."
};
int calm_count = sizeof(calm_messages) / sizeof(calm_messages[0]);

/* ------------------------- WINDOWS MODE ------------------------- */
#ifdef _WIN32
void windows_firework(int max_y, int max_x) {
    int y = rand() % max_y;
    int x = rand() % max_x;
    COORD pos = { (SHORT)x, (SHORT)y };
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(h, pos);
    printf("*");
    if (y > 0) { pos.Y = y-1; pos.X = x; SetConsoleCursorPosition(h, pos); printf("o"); }
    if (y+1 < max_y) { pos.Y = y+1; pos.X = x; SetConsoleCursorPosition(h, pos); printf("o"); }
    if (x > 0) { pos.Y = y; pos.X = x-1; SetConsoleCursorPosition(h, pos); printf("+"); }
    if (x+1 < max_x) { pos.Y = y; pos.X = x+1; SetConsoleCursorPosition(h, pos); printf("+"); }
}

void windows_rage_bar(int max_x) {
    printf("\nRAGE: ");
    int width = (rage * max_x) / MAX_RAGE;
    for (int i = 0; i < width && i < max_x-7; i++) {
        printf("#");
    }
    printf("\n");
}

void windows_calm_message(int max_x) {
    if (rage > 60 && rand() % 5 == 0) {
        const char* msg = calm_messages[rand() % calm_count];
        int pad = (max_x - (int)strlen(msg)) / 2;
        for (int i = 0; i < pad; i++) printf(" ");
        printf("%s\n", msg);
    }
}

void run_windows_mode() {
    int ch;
    int max_x = 80, max_y = 25; // assume typical console size
    system("cls");
    printf("Windows Stress Reliever - smash keys! Press 'q' to quit.\n");

    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'q') break;
            windows_firework(max_y-2, max_x);
            rage += 5;
            if (rage > MAX_RAGE) rage = MAX_RAGE;
        } else {
            rage -= 1;
            if (rage < 0) rage = 0;
        }

        windows_rage_bar(max_x);
        windows_calm_message(max_x);

        Sleep(50); // 50ms
    }
}
#endif

/* ------------------------- LINUX/MAC MODE ------------------------- */
#ifndef _WIN32
void draw_firework(int max_y, int max_x) {
    int y = rand() % max_y;
    int x = rand() % max_x;
    int colour = 1 + rand() % 6;

    attron(COLOR_PAIR(colour));
    mvprintw(y, x, "*");
    mvprintw(y-1 >= 0 ? y-1 : y, x, "o");
    mvprintw(y, x+1 < max_x ? x+1 : x, "+");
    mvprintw(y+1 < max_y ? y+1 : y, x, "o");
    mvprintw(y, x-1 >= 0 ? x-1 : x, "+");
    attroff(COLOR_PAIR(colour));
}

void draw_rage_bar(int max_y, int max_x) {
    int width = (rage * max_x) / MAX_RAGE;
    mvprintw(max_y-1, 0, "RAGE: ");
    attron(COLOR_PAIR(2));
    for (int i = 0; i < width && i < max_x-7; i++) {
        mvprintw(max_y-1, 6+i, "#");
    }
    attroff(COLOR_PAIR(2));
}

void maybe_calm_message(int max_y, int max_x) {
    if (rage > 60 && rand() % 5 == 0) {
        const char* msg = calm_messages[rand() % calm_count];
        mvprintw(max_y/2, (max_x - (int)strlen(msg))/2, "%s", msg);
    }
}

void run_ncurses_mode() {
    srand(time(NULL));
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE); // non-blocking input
    keypad(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    }

    int ch;
    while (1) {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        ch = getch();
        if (ch != ERR) {
            if (ch == 'q') break; // quit
            draw_firework(max_y-2, max_x);
            rage += 5;
            if (rage > MAX_RAGE) rage = MAX_RAGE;
        } else {
            rage -= 1;
            if (rage < 0) rage = 0;
        }

        clear();
        draw_rage_bar(max_y, max_x);
        maybe_calm_message(max_y, max_x);
        refresh();

        usleep(50000); // 50ms
    }

    endwin();
}
#endif

/* ------------------------- MAIN ------------------------- */
int main() {
    srand(time(NULL));
    printf("Stress Reliever\n");
    printf("=====================\n");
#ifdef _WIN32
    printf("Running on Windows...\n");
    run_windows_mode();
#else
    printf("Running on Linux/macOS...\n");
    run_ncurses_mode();
#endif
    return 0;
}
