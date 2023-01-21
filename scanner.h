#include "token.h"
#include "in_file.h"
#include "symbol_table.h"
#include "comment_status.h"
#include "error_reporter.h"

Token* scan(InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter);
