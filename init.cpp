#include <iostream>
#include <fstream>
#include "scanner.h"
#include "parser.h"
#include "compiler_types.h"

void compile_file(std::istream* file){
    std::string line;
    CommentStatus* commentStatus = new CommentStatus();
    while (std::getline(*file, line)){
        TokenStream* tokenStream = scanLine(line, commentStatus);
    }
}

int main(int argc, char** argv){
    std::ifstream ifs;
    ifs.open("testPgms/correct/test1.src");
    compile_file(&ifs);
    return 0;
}

