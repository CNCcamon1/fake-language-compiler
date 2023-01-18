#include <iostream>
#include <fstream>
#include <map>
#include "scanner.h"
#include "parser.h"
#include "compiler_types.h"

void compile_file(std::istream* file){
    std::string line;
    CommentStatus* commentStatus = new CommentStatus();
    std::map<std::string, enum TokenType> terminalDict = make_terminal_dict();
    std::map<std::string, enum TokenType> literalDict = make_literal_dict();
    while (std::getline(*file, line)){
        TokenStream* tokenStream = scan_line(line, commentStatus, &terminalDict, &literalDict);
        std::cout<<"End";
    }
}

int main(int argc, char** argv){
    std::ifstream ifs;
    ifs.open("testPgms/correct/math.src");
    compile_file(&ifs);
    return 0;
}

