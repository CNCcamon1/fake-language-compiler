#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "scanner.h"

const std::vector<std::vector<TokenType>> FIRST_SET{

};

const std::vector<std::vector<TokenType>> FOLLOW_SET{

};

Token* get_token_at_index(std::vector<Token*>* encounteredTokens, int currentTokenIndex,
    struct ScannerParams* scannerParams){

        Token* currentToken;
        try{
            currentToken = encounteredTokens->at(currentTokenIndex);
        }
        catch(std::out_of_range e){
            encounteredTokens->push_back(scan(scannerParams));
            currentToken = encounteredTokens->at(currentTokenIndex);
        }
        return currentToken;

}

bool child_choice_valid(TokenType currentType, Token* currentToken, Token* lookaheadToken){
    bool currentTokenInFirst = false;
    for(int i=0; i < )
}

void parse_node(ParseTreeNode* node, ScannerParams* scannerParams, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex){
        bool lastChildProcessed = false;
        while(lastChildProcessed == false){
            if(child_choice_valid(currentToken, lookaheadToken)){
                parse_node();
                lastChildProcessed = is_last_child_for_type();
            }
        }
}

ParseTree* parse_file(struct ScannerParams* scannerParams){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        std::vector<Token*> encounteredTokens;
        encounteredTokens.push_back(scan(scannerParams));
        encounteredTokens.push_back(scan(scannerParams));
};
