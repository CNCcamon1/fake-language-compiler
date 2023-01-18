#include <iostream>
#include <fstream>
#include <map>
#include "scanner.h"
#include "parser.h"
#include "compiler_types.h"

void compile_file(std::istream* file){
    std::string line;
    CommentStatus* commentStatus = new CommentStatus();
    std::map<std::string, enum TokenType>* stringToTypeDict = nullptr;
    initialize_scanner(stringToTypeDict);
    while (std::getline(*file, line)){
        TokenStream* tokenStream = scan_line(line, commentStatus, stringToTypeDict);
    }
}

int main(int argc, char** argv){
    std::ifstream ifs;
    ifs.open("testPgms/correct/test1.src");
    compile_file(&ifs);
    return 0;
}

