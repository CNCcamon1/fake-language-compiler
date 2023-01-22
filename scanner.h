#include "types/token.h"
#include "types/in_file.h"
#include "types/symbol_table.h"
#include "types/comment_status.h"
#include "types/error_reporter.h"

struct ScannerParams{
    InFile* file;
    SymbolTable* symbolTable;
    CommentStatus* commentStatus;
    ErrorReporter* errorReporter;
};

Token* scan(struct ScannerParams* scannerParams);
