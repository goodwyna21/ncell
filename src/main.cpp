/*
Terminal based spreadsheet program with vim-like bindings
*/

/*  Working On
*  Colors and cursor navigation work now (you can run program and move the cursor around), but no values actaully work 
*
*  still of course need to add file support (saving, and reading)
*  Long term goals:
*       - file support (reading and writing)
*       - formula support
*       - interface configuration
*       - keymap config file (able to set keymaps)
*       - ':' command support
*           > every action should be mapped to :<some command> and then keymaps should just map to something like <Tab> -> :<command> so that its easily configurable, I'm thinking something like a map.txt file in config/ that has entries like <Tab> : ":command" that the program reads at startup to set keybinds
*   
*   Reasonable Goals:
*      - Add writing to cells
*      - add more commands, like insert, change, which will allow you to change the values in cells
*      - add displaying cells with values (search TODO in displaySheet)
*
*   Just finished:
*       - Keymap loading works
*
*  generally search TODO in all files (' fg'), should give you enough of a start
*/
#include <ncurses.h>
#include <unordered_map>
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

    if (COLORS < 256) {
        printw("Your terminal does not support 256 colors\n");
        return false;
    }

    curs_set(0);     
    cbreak();
    noecho();
    keypad(stdscr, true);
    
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
    
    //initialize colors
    curseMap colorMap, colorPairMap;
    errType ret = loadColors(colorMap, colorPairMap);

    if(!ret.success){
        printw("Failed to load colors, \"");
        printw(ret.errMessage.c_str());
        printw("\"\n");
        refresh();
        getch();
        endwin();
        return 1;
    }

    //initialize keymaps
    keymapMap keymap;
    ret = loadKeymap(keymap);

    if(!ret.success){
        printw("Failed to load keymap, \"");
        printw(ret.errMessage.c_str());
        printw("\"\n");
        refresh();
        getch();
        endwin();
        return 1;
    }


//    testColors(colorPairMap);
    Sheet s("my sheet");
    s.setColors(colorPairMap);
    

    s.startMainLoop(keymap);

    endwin();

    return 0;
}
