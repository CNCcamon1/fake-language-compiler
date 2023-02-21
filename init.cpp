#include "parser.h"

void compile_file(){
    InFile* file = new InFile("testPgms/correct/math.src");
    SymbolTable* symbolTable = new SymbolTable();
    CommentStatus* commentStatus = new CommentStatus();
    ErrorReporter* errorReporter = new ErrorReporter();
    Token* nextToken = new Token(NONE);
    struct ScannerParams* scannerParams;
    scannerParams->file = file;
    scannerParams->symbolTable = symbolTable;
    scannerParams->commentStatus = commentStatus;
    scannerParams->errorReporter = errorReporter;
    scannerParams->nextToken = NONE;
   parse_file(scannerParams);
    std::cout<<"Successfully parsed file. \n";
};

int main(int argc, char** argv){
    compile_file();
    return 0;
}

