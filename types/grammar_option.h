#include "token.h"

#ifndef GRAMMAR_OPTION
#define GRAMMAR_OPTION

enum OptionType{
    NONE_C = 0,
    ARRAY_C = 1,
    OPTIONAL_C = 2,
};

class GrammarOption{
    public:
        TokenType tokenType;
        OptionType optionType;
        GrammarOption(TokenType typeInput, OptionType optionInput){
            tokenType = typeInput;
            optionType = optionInput;
        };
        GrammarOption(TokenType typeInput){
            tokenType = typeInput;
            optionType = NONE_C;
        };
};
#endif