#ifndef WORKSHEET
#define WORKSHEET

#include "enums.h"
#include <unordered_map>
#include <memory>

typedef std::unordered_map<int, std::shared_ptr<cell>> column;
typedef std::unordered_map<int, column> cellMap;
            
class Sheet{
public:
    Sheet(std::string);
    Sheet();
    std::string getName();

    void display();

    std::shared_ptr<cell> at(int, int);
    void set(int, int, const std::string&);

    void insertRow(int);
    void insertCol(int);
    void deleteRow(int);
    void deleteCol(int);

    void updateWidth(int);
private:
    cellMap cells; //cells[col][row]
    std::string name;
    void drawHeader();
    void drawCells();

    std::unordered_map<int, int> col_widths;
};

#endif
