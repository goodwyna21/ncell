#include "worksheet.h"

#include <ncurses.h>
#include <sstream>

Sheet::Sheet(std::string _name) : name(_name) {
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    onScreenColBegin = 0;
    onScreenRowBegin = 0;
    onScreenColEnd = (maxX - DisplayConsts::cellsBeginX) / DisplayConsts::defaultColWidth - 1;
    onScreenRowEnd = (maxY - DisplayConsts::cellsBeginY) - 1;
}
Sheet::Sheet() : Sheet("unnamed sheet") {}

void Sheet::setColors(cursesMap& _colorPairMap){
    colorPairMap = _colorPairMap;
    colorsSet = true;
}


std::shared_ptr<cell> Sheet::at(int row, int col){
    if(cells.find(col) == cells.end()){
        return nullptr;
    }
    if(cells.at(col).find(row) == cells.at(col).end()){
        return nullptr;
    }
    return cells.at(col).at(row);
}

bool isNumber(const std::string& s) {
    std::istringstream iss(s);
    double d;
    char c;

    // Try to read a double, and make sure the entire string was consumed
    return iss >> d && !(iss >> c);
}

void Sheet::set(int row, int col, const std::string& value){
    //no need to update if no value and cell doesnt exist
    if( value == "" || 
    cells.find(col) == cells.end() || 
        cells.at(col).find(row) == cells.at(col).end()){
        return;
    }

    std::shared_ptr<cell> c = cells[col][row];
    bool dontDelete = true;
    if(value == ""){
        c->t = cell::type::none;
        c->value = "";
        dontDelete = false;
    } else {
        c->value = value;
        if(isNumber(value)){
            c->t = cell::type::number;
        } else if(value[0] == '='){
            c->t = cell::type::formula;
        } else {
            c->t = cell::type::text;
        }
    }

    //update cell, remove if it is empty now
    if(!dontDelete){
        cells.at(col).erase(row); //remove cell
        if(cells.at(col).empty()){ //if col empty, erase col
            cells.erase(col); 
        }
    }
}
 
void Sheet::setCurs(int row, int col){
    drawCell(cursRow, cursCol);
    cursRow = row;
    cursCol = col;
    drawCell(cursRow, cursCol, true);
}

void Sheet::mvCurs(int dx, int dy){
    if(cursRow + dy > onScreenRowEnd || cursRow + dy < onScreenRowBegin ||
       cursCol + dx > onScreenColEnd || cursCol + dx < onScreenRowBegin){
        return; //TODO scroll screen when this happens
    }
    setCurs(cursRow + dy, cursCol + dx);
}
