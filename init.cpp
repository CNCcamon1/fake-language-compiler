#include "parser.h"

void compile_file(){
    InFile* file = new InFile("testPgms/correct/logicals.src");
    SymbolTable* symbolTable = new SymbolTable();
    CommentStatus* commentStatus = new CommentStatus();
    ErrorReporter* reporter = new ErrorReporter();
    Token* nextToken = new Token(NONE);
    ScannerParams* scannerParams = new ScannerParams();
    scannerParams->file = file;
    scannerParams->errorReporter = reporter;
    scannerParams->symbolTable = symbolTable;
    scannerParams->commentStatus = commentStatus;
    scannerParams->nextToken = NONE;
   parse_file(scannerParams);
    std::cout<<"Successfully parsed file. \n";
};

int main(int argc, char** argv){
    compile_file();
    return 0;
}

