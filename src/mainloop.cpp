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

        if(actionMap.find(action) != actionMap.end()){
            (this->*actionMap.at(action))();
        } else {
            //do something if action not found
            continue;
        }
    }
}
