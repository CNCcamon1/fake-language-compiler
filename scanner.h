#include <string>
#include "compiler_types.h"

TokenStream* scan_line(std::string line, CommentStatus* commentStatus, 
    std::map<std::string, enum TokenType>* terminalDict,
    std::map<std::string, enum TokenType>* literalDict);

std::map<std::string, enum TokenType> make_terminal_dict();

std::map<std::string, enum TokenType> make_literal_dict();