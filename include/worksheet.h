#ifndef WORKSHEET
#define WORKSHEET

#include "enums.h"
#include <unordered_map>
#include <memory>

typedef std::unordered_map<int, std::shared_ptr<cell>> column;
typedef std::unordered_map<int, column> cellMap;
typedef std::unordered_map<std::string, int> cursesMap;

namespace DisplayConsts {
    const int rowIdWidth = 5; //chars in row ids (6 allows for whitespace around up to 9999)
    const int cellsBeginX = rowIdWidth; //x of first cell
    const int cellsBeginY = 4; //y of first cell
    const int defaultColWidth = 9;
}

class Sheet{
public:
    Sheet(std::string); //done
    Sheet(); //done

    void setColors(cursesMap& _colorPairMap); //done
    void startMainLoop();

private:
    void display(); //done-ish

    std::shared_ptr<cell> at(int, int); //done
    void set(int, int, const std::string&); //done-ish

    void setCurs(int col, int row); //done
    void mvCurs(int dx, int dy); //done

/*
    void insertRow(int);
    void insertCol(int);
    void deleteRow(int);
    void deleteCol(int);
*/

//    void updateWidth(int);
    cellMap cells; //cells[col][row]
    std::string name;
    void drawHeader();
    void drawCells();
    void drawCell(int row, int col, bool selected=false);

    int onScreenColBegin;
    int onScreenColEnd;
    int onScreenRowBegin;
    int onScreenRowEnd;
    std::unordered_map<int, int> col_widths;
    cursesMap colorPairMap;
    bool colorsSet = false;

    int cursCol = 0;
    int cursRow = 0;
};

#endif
