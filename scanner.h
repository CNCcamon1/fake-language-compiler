#include <string>
#include "compiler_types.h"

Token* scan(InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporting* errorReporter);
