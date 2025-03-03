#include "EightQueensSolver.h"
#include <iostream>

int main() {
    EightQueensSolver solver;
    std::string solution = solver.solve();
    std::cout << "Eight Queens Solution:\n" << solution << std::endl;
    return 0;
}
