#include <iostream>
#include <fstream>
#include "scanner.h"
#include "parser.h"
#include "compiler_types.h"

void compile_file(std::istream* file){
    std::string line;
    while (std::getline(*file, line)){
        TokenStream* tokenStream = scanLine(line);
    }
}

int main(int argc, char** argv){
    std::ifstream ifs;
    ifs.open("testPgms/correct/logicals.src");
    compile_file(&ifs);
    return 0;
}

