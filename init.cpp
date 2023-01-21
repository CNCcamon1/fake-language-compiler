#include "parser.h"

void compile_file(){
    InFile* file = new InFile("testPgms/correct/math.src");
    SymbolTable* symbolTable = new SymbolTable();
    CommentStatus* commentStatus = new CommentStatus();
    ErrorReporter* errorReporter = new ErrorReporter();
    Token* nextToken = new Token(NONE);

    ParseTree* parsedTree = parse_file(file, symbolTable, commentStatus, errorReporter);
};

int main(int argc, char** argv){
    compile_file();
    return 0;
}

