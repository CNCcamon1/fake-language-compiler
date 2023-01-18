#include <string>
#include "compiler_types.h"

TokenStream* scan_line(std::string line, CommentStatus* commentStatus, 
    std::map<std::string, enum TokenType>* stringToTypeDict);

void initialize_scanner(std::map<std::string, enum TokenType>* stringToTypeDict);