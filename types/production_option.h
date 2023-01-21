#include <vector>
#include <iostream>
#include "token.h"

#ifndef PRODUCTION_OPTION_TYPE
#define PRODUCTION_OPTION_TYPE

class ProductionOption{
    public:
        ProductionOption(){

        }
        ProductionOption(std::vector<TokenType> tokensInput){
            /*for(int i=0; i<tokensInput.size(); i++){
                TokenType type = tokensInput[i];
                std::cout<<"Test";
            } */
            tokens = tokensInput;
        }
        std::vector<TokenType> tokens;

        void print_tokens_in_option(){
            std::cout<<"Production with tokens ";
            for(int i=0; i<tokens.size(); i++){
                std::cout<<TokenTools::token_type_to_string(tokens[i]);
                std::cout<<",";
            }
            std::cout<<"\n";
        }
};

#endif