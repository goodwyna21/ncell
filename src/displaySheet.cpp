#include <ncurses.h>
#include <format>

#include "readconfig.h"
#include "worksheet.h"

typedef std::unordered_map<std::string, int> cursesMap;

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
       
        if(ind % 2){
            attron(COLOR_PAIR(colorPairMap.at("default")));
        } else {
            attron(COLOR_PAIR(colorPairMap.at("alternate")));
        }
        printw(colId.c_str());
        if(ind % 2){
            attroff(COLOR_PAIR(colorPairMap.at("default")));
        } else {
            attroff(COLOR_PAIR(colorPairMap.at("alternate")));
        }

        ind++;
    }

    //draw row numbers
    for(int y = 4; y < maxY; y++){
        mvprintw(y,0,center(std::to_string(y-3),DisplayConsts::rowIdWidth).c_str());
    }
}

void Sheet::drawCells(){
    int xPos = DisplayConsts::cellsBeginX;
    int yPos, colWidth;
    for(int col = onScreenColBegin; col <= onScreenColEnd; col++){
        attron(COLOR_PAIR(colorPairMap.at(col%2 ? "default" : "alternate")));

        if(col_widths.find(col) != col_widths.end()){
            colWidth = col_widths.at(col);
        } else {
            colWidth = DisplayConsts::defaultColWidth;
        }
        
        if(cells.find(col) == cells.end()){
            yPos = DisplayConsts::cellsBeginY;
            
            for(int y = onScreenRowBegin; y <= onScreenRowEnd; y++){
                mvprintw(yPos, xPos, std::string(colWidth, '.').c_str());
                yPos++;
            }
        } else {
            //TODO draw columns that actually have values
        }

        attroff(COLOR_PAIR(colorPairMap.at(col%2 ? "default" : "alternate")));

        xPos += colWidth;
    }  
}

void Sheet::drawCell(int row, int col, bool selected){
    int xPos = DisplayConsts::cellsBeginX;
    int colWidth;
    for(int colInd = onScreenColBegin; colInd < col; colInd++){
        if(col_widths.find(colInd) != col_widths.end()){
            colWidth = col_widths.at(colInd);
        } else {
            colWidth = DisplayConsts::defaultColWidth;
        }
        xPos += colWidth;
    }
    if(selected){
        attron(COLOR_PAIR(colorPairMap.at("primary")));
    } else {
        attron(COLOR_PAIR(colorPairMap.at(col%2 ? "default" : "alternate")));
    }
    mvprintw(row + DisplayConsts::cellsBeginY, xPos, std::string(DisplayConsts::defaultColWidth, '.').c_str());
    if(selected){
        attroff(COLOR_PAIR(colorPairMap.at("primary")));
    } else {
        attroff(COLOR_PAIR(colorPairMap.at(col%2 ? "default" : "alternate")));
    }
}

void Sheet::display(){
    drawHeader();
    drawCells();
    drawCell(cursRow, cursCol, true);
}
