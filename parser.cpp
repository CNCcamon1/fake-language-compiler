#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "types/grammar_option.h"
#include "types/grammar.h"
#include "scanner.h"

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

int parse_nonterminal(ParseTreeNode* node, ScannerParams* scannerParams, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex,
    Grammar* grammar){
        std::vector<GrammarOption*>* childOptions = grammar->get_possible_children_for_type(node->type);
        int childOptionIndex = 0;
        bool allChildrenParsed = false;
        while(allChildrenParsed == false){
            GrammarOption* childOption = childOptions->at(childOptionIndex);
            if(childOption == nullptr){
                allChildrenParsed = true;
            }
            else{
                Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
                Token* lookaheadToken = get_token_at_index(encounteredTokens, currentTokenIndex+1, scannerParams);
                if(grammar->child_choice_valid(childOption->tokenType, currentToken, lookaheadToken)){
                    ParseTreeNode* newChild = new ParseTreeNode(childOption->tokenType);
                    currentTokenIndex = parse_node(newChild, scannerParams, encounteredTokens, currentTokenIndex, grammar);
                    node->add_child(newChild);
                    if(childOption->optionType != ARRAY_C){
                        childOptionIndex++;
                    }
                }
                else{
                    if(childOption->optionType == ARRAY_C || childOption->optionType == OPTIONAL_C){
                        childOptionIndex++;
                    }
                    else{
                        throw NoValidDerivationsException();
                    }
                }
            }

        }
        return currentTokenIndex;
}

int parse_identifier(ParseTreeNode* node, ScannerParams* scannerParams, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex){
        Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
        node->data = currentToken->tokenString;
        return currentTokenIndex+1;
}

int parse_node(ParseTreeNode* node, ScannerParams* scannerParams, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex,
    Grammar* grammar){
        if(grammar->is_terminal(node->type)){
            return currentTokenIndex+1;
        }
        else if(node->type == IDENTIFIER_NT){
            return parse_identifier(node, scannerParams, encounteredTokens, currentTokenIndex);
        }
        else if(node->type == STRING_LITERAL_NT){
            return parse_identifier(node, scannerParams, encounteredTokens, currentTokenIndex);
        }
        else if(node->type == NUMBER_NT){
            return parse_identifier(node, scannerParams, encounteredTokens, currentTokenIndex);
        }
        else{
            return parse_nonterminal(node, scannerParams, encounteredTokens, currentTokenIndex, grammar);
        }

}

ParseTree* parse_file(struct ScannerParams* scannerParams){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        std::vector<Token*> encounteredTokens;
        Grammar* grammar = new Grammar();
        encounteredTokens.push_back(scan(scannerParams));
        encounteredTokens.push_back(scan(scannerParams));
        parse_node(parsedTree->rootNode, scannerParams, &encounteredTokens, 0, grammar);
};
