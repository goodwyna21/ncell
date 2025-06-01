#include "worksheet.h"
#include <ncurses.h>

void Sheet::startMainLoop(){
    display();

    char inp;
    while((inp = getch()) != 'q'){
        switch(inp){
            case 'h':
                mvCurs(-1, 0);
                break;
            case 'l':
                mvCurs(1, 0);
                break;
            case 'j':
                mvCurs(0, 1);
                break;
            case 'k':
                mvCurs(0, -1);
                break;
        }
    }
    
}
