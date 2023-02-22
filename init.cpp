#include "parser.h"

void compile_file(){
    InFile* file = new InFile("testPgms/correct/source.src");
    SymbolTable* symbolTable = new SymbolTable();
    CommentStatus* commentStatus = new CommentStatus();
    ErrorReporter* reporter = new ErrorReporter();
    ScannerParams* scannerParams = new ScannerParams();
    scannerParams->file = file;
    scannerParams->errorReporter = reporter;
    scannerParams->symbolTable = symbolTable;
    scannerParams->commentStatus = commentStatus;
    std::string nothing = "";
    scannerParams->preBuffered = &nothing;
   parse_file(scannerParams);
    std::cout<<"Successfully parsed file. \n";
};

int main(int argc, char** argv){
    compile_file();
    return 0;
}

