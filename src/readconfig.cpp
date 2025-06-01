#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <tuple>
#include <ncurses.h>

#include "readconfig.h"

//#define DEBUG_COLOR

#ifdef DEBUG_COLOR
#include <filesystem>
#endif

typedef std::unordered_map<std::string, int> curseMap;

//loads colors from colors.txt file, initializes pairs and puts those pairs into col_map
bool loadColors(curseMap& colorMap, curseMap& colorPairMap){
    std::vector<std::string> path = {
        "~/.config/ncell/",
        "../../config/",
        "../config/"
    };

    //try and open colors.txt
    std::ifstream colFile;

    #ifdef DEBUG_COLOR
    std::cout << std::filesystem::current_path() << "\n";
    #endif

    for(std::string pathOption : path){
        #ifdef DEBUG_COLOR
        std::cout << "trying " << std::quoted(pathOption + "colors.txt") << "... ";
        #endif

        colFile.open(pathOption + "colors.txt");
        if(colFile.is_open()){
            #ifdef DEBUG_COLOR
            std::cout << "found\n";
            #endif
            break;
        }
        #ifdef DEBUG_COLOR
        std::cout << "not found\n";
        #endif
    }
    //check if none found
    if(!colFile.is_open()){
        std::cerr << "no valid colors.txt found\n";
        return false;
    }

    //read colors
    std::unordered_map<std::string, std::tuple<short, short, short>> colDefs; //primaryBG -> {1000, 321, 678} or whatever
    std::unordered_map<std::string, std::pair<std::string, std::string>> colPairDefs; //primary -> {defFG, primaryBG}

    std::string line, name, p1, p2;
    char hexDelim;
    short r, g, b;
    std::istringstream linestream;
    bool inColDefs = true;
    
    while(std::getline(colFile, line)){
        //empty line
        if(line.find_first_not_of(' ') == std::string::npos){
            continue;
        }
        if(inColDefs){ //first section of file
            //line contains ';' which switches from color
            //definitions to pair definitions
            if(line.find(';') != std::string::npos){
                inColDefs = false;
                continue;
            }

            linestream.clear();
            linestream.str(line);

            linestream >> name >> hexDelim >> p1;
           
            #ifdef DEBUG_COLOR
            std::cout << name << ": " << p1 << "\n";
            #endif

            r = static_cast<short>(std::stoi(p1.substr(0,2), nullptr, 16) * 1000 / 255);
            g = static_cast<short>(std::stoi(p1.substr(2,2), nullptr, 16) * 1000 / 255);
            b = static_cast<short>(std::stoi(p1.substr(4,2), nullptr, 16) * 1000 / 255);
            
            colDefs.insert({name, std::make_tuple(r, g, b)});
        
        //color pair definitions
        } else {
            linestream.clear();
            linestream.str(line);
            linestream >> name >> p1 >> p2;

            colPairDefs.insert({name, std::make_pair(p1, p2)});
        }
    }

    //debug
    #ifdef DEBUG_COLOR
    std::cout << "colors: \n";
    for(const auto & [key, value] : colDefs){
        std::cout << key << ": " << std::get<0>(value) << ", " << std::get<1>(value) << ", " << std::get<2>(value) << "\n";
    }
    std::cout << "pairs: \n";
    for(const auto & [key, value] : colPairDefs){
        std::cout << key << ": " << std::get<0>(value) << ", " << std::get<1>(value) << "\n";
    }
    #endif


    //initialize colors
    int colorId = 10;
    for(const auto & [colorName, rgb] : colDefs){
        init_color(colorId, std::get<0>(rgb), std::get<0>(rgb), std::get<0>(rgb)); 
        colorMap.insert({colorName, colorId});
        colorId++;
    }

    int pairId = 1;
    for(const auto & [pairName, colors] : colPairDefs){
        init_pair(pairId, colorMap.at(std::get<0>(colors)), colorMap.at(std::get<1>(colors)));
        colorPairMap.insert({pairName, pairId});
        pairId++;
    }

    return true;
}

//display test colors to screen
void testColors(curseMap& colorPairMap){
    move(0,0);
    for(const auto & [pairName, pairId] : colorPairMap){
        attron(pairId);
        printw(pairName.c_str());
        printw("\n");
        attroff(pairId);
    }
    refresh();
}


