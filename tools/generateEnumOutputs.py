import re

namespace_pattern = r"^(?:namespace|struct|class) ([\w\d_-]+){\n([\s\S]+?)\n^}"
enum_pattern = r"enum(?: class)? ([\w\d_-]+){\n([^}]+)?\n\s*?};"
enum_nonIndent =    r"enum(?: class)? ([\w\d_-]+){\n([^}]+)\n}"

s = """#ifndef ENUMS_H
#define ENUMS_H
#include "enum_definitions.h"
#include <ostream>

namespace enumPrints{
"""

strArrs = ""
outFuncs = ""

def processEnum(name, elems, namespace=''):
    arr = '    const std::string '
    if namespace != '':
        arr += namespace
    arr += name + 'Strings[] = {'
    arr += ','.join(["\"" + s + "\"" for s in elems.replace(' ','').replace('\n','').split(',') if s != ''])
    arr += '};\n'
    
    func = 'inline std::ostream& operator<<(std::ostream& out, '
    if namespace != '':
        func += namespace + "::"
    func += name
    func += ' t){ return out << enumPrints::'
    if namespace != '':
        func += namespace
    func += name + 'Strings[(int)t]; }\n'

    #print("strArrs: $", arr, "$", sep='')
    #print("func: $", func, "$", sep='')

    return arr, func

with open("include/enum_definitions.h", "r") as f:
    text = f.read()
    #handles namespaced enums
    namespaces = re.findall(namespace_pattern, text, re.MULTILINE)
    
    for n in namespaces:
        namespace, body = n
        matches = re.findall(enum_pattern, body, re.MULTILINE)
        for m in matches:
            name, elems = m
            arr, func = processEnum(name, elems, namespace)
            strArrs += arr
            outFuncs += func

    #handles non-namespaced enums
    matches = re.findall(enum_nonIndent, text, re.MULTILINE)
    for m in matches:
        name, elems = m
        processEnum(name, elems)
        arr, func = processEnum(name, elems)
        strArrs += arr
        outFuncs += func

s += strArrs
s += "}\n\n"
s += outFuncs
s += "\n#endif"

with open("include/enums.h", "w") as f:
    f.write(s)
