#include <iostream>
#include <fstream>
#include <map>
#include "scanner.h"
#include "compiler_types.h"
#include "compiler_exceptions.h"

void compile_file(){
    InFile* file = new InFile("testPgms/correct/math.src");
    SymbolTable* symbolTable = new SymbolTable();
    CommentStatus* commentStatus = new CommentStatus();
    ErrorReporting* errorReporter = new ErrorReporting();
    Token* nextToken = new Token(NONE);
    while(nextToken->type != END_OF_FILE){
        nextToken = scan(file, symbolTable, commentStatus, errorReporter);
    }
    std::cout<<"Scanned " << std::to_string(file->get_line_count()) << " lines. \n";
};

int main(int argc, char** argv){
    compile_file();
    return 0;
}

