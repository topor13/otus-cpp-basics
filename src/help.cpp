#include "include/help.h"
#include <iostream>

namespace help {
	void print() {
        std::cout << std::endl;
        std::cout << " Homework03: guess the number game" << std::endl;
        std::cout << std::endl;
        std::cout << " Usage: guess [argument]" << std::endl;
        std::cout << std::endl;
        std::cout << " Arguments:" << std::endl;
        std::cout << "   -help       - print this message and exit." << std::endl;
        std::cout << "   -max number - upper number for randomize. Optional. Default 100." << std::endl;
        std::cout << "                 Example: `guess -max 200`. " << std::endl;
        std::cout << "   -table      - print high scores table and exit." << std::endl;
        std::cout << std::endl;
    }
}