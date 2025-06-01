#ifndef ENUM_DEF_H
#define ENUM_DEF_H

#include <string>

struct cell{
    enum class type{
        number,
        text,
        formula,
        date,
        time,
        none,
    };

    enum class format{
        normal,
        money,
        specified,
    };

    std::string value;
    type t;
    format f = format::normal;
};

#endif