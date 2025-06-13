#ifndef READCONFIG_H
#define READCONFIG_H

#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, int> curseMap;
typedef std::unordered_map<std::string, std::string> keymapMap;
struct errType {
    bool success = true;
    std::string errMessage = "";  
    errType(){}
    errType(std::string _msg) : success(false), errMessage(_msg) {}
    errType(const char* _msg) : success(false), errMessage(std::string(_msg)) {}
};

errType loadColors(curseMap& colorMap, curseMap& colorPairMap);

void testColors(curseMap& colorPairMap);

errType loadKeymap(keymapMap& keymap);

#endif
