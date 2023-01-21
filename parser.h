#include "types/parse_tree.h"
#include "types/in_file.h"
#include "types/symbol_table.h"
#include "types/comment_status.h"
#include "types/error_reporter.h"
#include "scanner.h"

ParseTree* parse_file(InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter);