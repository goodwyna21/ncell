#include <ncurses.h>

int main(){
    initscr();
    if (has_colors()) {
        start_color();
        init_color(COLOR_RED, 1000, 0, 0);
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        printw("This is red on black\n");
        attroff(COLOR_PAIR(1));
    } else {
        printw("No color support\n");
    }
    refresh();
    getch();
    endwin();
}
