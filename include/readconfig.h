#ifndef READCONFIG_H
#define READCONFIG_H

#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, int> curseMap;

bool loadColors(curseMap& colorMap, curseMap& colorPairMap);

void testColors(curseMap& colorPairMap);

#endif
