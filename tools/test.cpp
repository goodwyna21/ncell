#include <iostream>
#include <sstream>

int main(){
    std::string test = "primaryBG #ff52ad";

    std::istringstream linestream;

    linestream.str(test);
    std::string name, p1, p2;
    char hexDelim;
    short r, g, b;

    linestream >> name >> hexDelim >> p1;

    std::cout << "(" << name << ") (" << hexDelim << ") ("<< p1 << ")\n";

    r = static_cast<short>(std::stoi(p1.substr(0,2), nullptr, 16) * 1000 / 255);
    g = static_cast<short>(std::stoi(p1.substr(2,2), nullptr, 16) * 1000 / 255);
    b = static_cast<short>(std::stoi(p1.substr(4,2), nullptr, 16) * 1000 / 255);

    std::cout << r << " " << g << " " << b << "\n";
}
