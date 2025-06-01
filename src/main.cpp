/*
Terminal based spreadsheet program with vim-like bindings
*/

/*  Working On
*   
*   Clangd fails when compile_commands.json is not in ncell/, the path is changed in the clangd setup but its not working for some reason
*   
*   Also trying to figure out how to get sessions to work so you can just "nvim" in ncell/ and have it open 
*   the appropriate windows, (1 full height in center, 2 stacked on right for things like headers and second working file)
*   ^ using auto-session for that one
*/
#include <ncurses.h>
#include <unordered_map>
#include <iostream>


#include "enums.h"
#include "worksheet.h"
#include "readconfig.h"



/*
*   Working on
* Just finished colors, add colors to alternating columns
* add cursor, selection, writing to cells
*
*
*/

//returns true if successful, false otherwise
bool startCurses(){
     initscr();
    if (!has_colors()) {
        printw("No color support\n");
        return false;
    } 
    start_color();
    if (!can_change_color()) {
        printw("Cannot change colors\n");
        return false;
    }

    //use_default_colors();   // Allow use of default terminal background

    if (COLORS < 256) {
        printw("Your terminal does not support 256 colors\n");
        return false;
    }

         

    return true;
}

typedef std::unordered_map<std::string, int> curseMap;

int main(int argc, char* argv[]){
    if(!startCurses()){
        refresh();
        getch();
        endwin();
        return 1;
    }
    
    endwin();

    //initialize colors
    curseMap colorMap, colorPairMap;
    loadColors(colorMap, colorPairMap);

/*
    short r, g, b;
    color_content(colorMap.at("primaryBG"), &r, &g, &b);
    std::cout << r << " " << g << " " << b << "\n";
    return 1;
*/
    mvprintw(0,0,"testing colors");

    testColors(colorPairMap);
//    Sheet s("my sheet");
//    s.display();

    //mvprintw(0, 0, "press any key to exit...");
    refresh();
    getch();
    endwin();
    return 0;
}
