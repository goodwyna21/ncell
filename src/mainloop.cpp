#include "worksheet.h"

#include <ncurses.h>


void Sheet::startMainLoop(const keymapMap& keymap){
    display();

    char inp;
    std::string sequence;
    std::string action;
    while((inp = getch()) != 'q'){
        sequence = std::string(1, inp);

        if(keymap.find(sequence) == keymap.end()){
            continue;
        }
        action = keymap.at(sequence);

        if(action == "curs_left"){
            mvCurs(-1, 0);
        } else if(action == "curs_right"){
            mvCurs(1, 0);
        } else if(action == "curs_down"){
            mvCurs(0, 1);
        } else if(action == "curs_up"){
            mvCurs(0, -1);
        }
    }
}
