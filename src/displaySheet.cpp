#include <ncurses.h>
#include <format>

#include "worksheet.h"

namespace DisplayConsts {
    const int rowIdWidth = 6; //chars in row ids (6 allows for whitespace around up to 9999)
    const int cellsBeginX = rowIdWidth + 1; //x of first cell
    const int cellsBeginY = 4; //y of first cell
    const int defaultColWidth = 10;
}

std::string getColId(int n){
    std::string s = "";
    do{
        int rem = n % 26;
        s += static_cast<char>('A' + rem);
        n = n / 26 - 1;
    }while(n > 0);
    std::reverse(s.begin(), s.end());
    return s;
}

int getColFromId(std::string s){
    int ind = 0;
    for(char c : s){
        ind = ind * 26 + (std::toupper(c) - 'A' + 1);
    }
    return ind - 1;
}

std::string center(std::string s, int width, char padding=' '){
    if(padding == ' '){
        return std::format("{:^{}}", s, width);
    } else {
        return std::vformat(std::string("{:") + padding + "^{}}", std::make_format_args(s, width));
    }   
}

void Sheet::drawHeader(){
    mvprintw(0, 0, name.c_str());

    //draw tabs
    std::vector<std::string> tabs = {"file", "edit", "view", "insert", "format", "data"};
    move(1,0);
    for(int i = 0; i < tabs.size(); i++){
         printw("|");
        //separated for selection highlighting
        printw(" ");
        printw(tabs.at(i).c_str());
        printw(" ");
    }
    printw("|");
    //should check that this header is not too big

    //draw tool bar
    move(2,0);
    //todo


    //draw column ids
    move(3,DisplayConsts::rowIdWidth);
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    int x = DisplayConsts::rowIdWidth;
    std::string colId = "";
    int ind = 0;
    int width;
    while(x < maxX){
        colId = getColId(ind);
        if(col_widths.find(ind) == col_widths.end()){
            width = DisplayConsts::defaultColWidth;
        } else {
            width = col_widths.at(ind);
        }
        colId = center(colId, width);
        x += colId.size();
        if(x > maxX){
            colId.resize(colId.size() - (x - maxX));    
        }
        printw(colId.c_str());

        ind++;
    }

    //draw row numbers
    for(int y = 4; y < maxY; y++){
        mvprintw(y,0,center(std::to_string(y-3),DisplayConsts::rowIdWidth).c_str());
    }
}

void Sheet::display(){
    drawHeader();
}
