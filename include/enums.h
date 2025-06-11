#ifndef ENUMS_H
#define ENUMS_H
#include "enum_definitions.h" // IWYU pragma: export
#include <ostream>

namespace enumPrints{
    const std::string celltypeStrings[] = {"number","text","formula","date","time","none"};
    const std::string cellformatStrings[] = {"normal","money","specified"};
}

inline std::ostream& operator<<(std::ostream& out, cell::type t){ return out << enumPrints::celltypeStrings[(int)t]; }
inline std::ostream& operator<<(std::ostream& out, cell::format t){ return out << enumPrints::cellformatStrings[(int)t]; }

#endif
