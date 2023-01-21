#include <vector>
#include "token.h"

#ifndef PRODUCTION_OPTION_TYPE
#define PRODUCTION_OPTION_TYPE

class ProductionOption{
    public:
        ProductionOption(std::vector<TokenType> tokensInput){
            tokens = tokensInput;
        }
        std::vector<TokenType> tokens;
};

#endif