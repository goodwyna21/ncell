#include <sstream>
#include <fstream>
#include <tuple>

#include <ncurses.h>

#include "readconfig.h"

//#define DEBUG_COLOR

#ifdef DEBUG_COLOR
#include <filesystem>
#endif

std::vector<std::string> CONFIG_PATH = {
    "~/.config/ncell/",
    "../../config/",
    "../config/"
};

//loads colors from colors.txt file, initializes pairs and puts those pairs into col_map
errType loadColors(curseMap& colorMap, curseMap& colorPairMap){
    

    //try and open colors.txt
    std::ifstream colFile;

    #ifdef DEBUG_COLOR
    std::cout << std::filesystem::current_path() << "\n";
    #endif

    for(std::string pathOption : CONFIG_PATH){
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
        return "no valid colors.txt found\n";
    }

    //read colors
    std::string line, name, p1, p2;
    char hexDelim;
    short r, g, b;
    std::istringstream linestream;
    bool inColDefs = true;
    short colorId = 16;
    short pairId = 1;

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
            
            init_color(colorId, r, g, b);
            colorMap.insert({name, colorId});
            colorId++;

            #ifdef DEBUG_COLOR
            std::cout << name << ": " << r << ", " << g << ", " << b << "\n";
            #endif

        //color pair definitions
        } else {
            linestream.clear();
            linestream.str(line);
            linestream >> name >> p1 >> p2;

            init_pair(pairId, colorMap.at(p1), colorMap.at(p2));
            colorPairMap.insert({name, pairId});
            pairId++;
        }
    }

    return {};
}

//display test colors to screen
void testColors(curseMap& colorPairMap){
    move(1,0);
    for(const auto & [pairName, pairId] : colorPairMap){
        attron(COLOR_PAIR(pairId));
        printw(pairName.c_str());
        printw("\n");
        attroff(COLOR_PAIR(pairId));
    }
    refresh();
}

errType loadKeymap(keymapMap& keymap){
    std::ifstream keyFile;

    for(std::string pathOption : CONFIG_PATH){
        keyFile.open(pathOption + "keymap.txt");
        if(keyFile.is_open()){ 
            break;
        }
    }
    if(!keyFile.is_open()){
        return "No keymap file found\n";   
    }

    std::istringstream linestream;
    std::string line;
    std::string sequence;
    std::string action;

    while(std::getline(keyFile, line)){
        if(line.find_first_not_of(' ') == std::string::npos){
            continue;
        }
        linestream.clear();
        linestream.str(line);

        std::getline(linestream, sequence, ' ');
        std::getline(linestream, action);

        keymap.insert({sequence, action});
    }
    return {};
}
