#include "worksheet.h"

#include <sstream>


Sheet::Sheet(std::string _name) : name(_name) {

}
Sheet::Sheet() : Sheet("unnamed sheet") {}

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

//sets value of cell, and updates its type
bool updateCell(std::shared_ptr<cell> c, const std::string& value){
    if(value == ""){
        c->t = cell::type::none;
        c->value = "";
        return false;
    }
    c->value = value;
    if(isNumber(value)){
        c->t = cell::type::number;
    } else if(value[0] == '='){
        c->t = cell::type::formula;
    } else {
        c->t = cell::type::text;
    }
    return true;
}

void Sheet::set(int row, int col, const std::string& value){
    //no need to update if no value and cell doesnt exist
    if( value == "" || 
        cells.find(col) == cells.end() || 
        cells.at(col).find(row) == cells.at(col).end()){
        return;
    }
    
    //update cell, remove if it is empty now
    if(!updateCell(cells[col][row], value)){
        cells.at(col).erase(row); //remove cell
        if(cells.at(col).empty()){ //if col empty, erase col
            cells.erase(col); 
        }
    }
}
