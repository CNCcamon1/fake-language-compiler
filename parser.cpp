#include <vector>
#include <iostream>
#include "types/parse_tree.h"
#include "types/grammar_option.h"
#include "types/grammar.h"
#include "scanner.h"

int parse_node(ParseTreeNode* node, ScannerParams* scannerParams, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex,
    Grammar* grammar);

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
        std::vector<std::vector<GrammarOption*>>* possibleChildrenArrangements = grammar->get_possible_children_for_type(node->type);
        for(int i=0; i<possibleChildrenArrangements->size(); i++){
            //For each derivation option for the nonterminal
            Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
            //First check if the current token is a valid first choice for this derivation option
            if(grammar->child_choice_valid(possibleChildrenArrangements->at(i).at(0)->tokenType, currentToken)){
                //If it is, use this derivation option and parse it
                std::vector<GrammarOption*>* chosenDerivationOption = &possibleChildrenArrangements->at(i);
                int grammarOptionIndex = 0;
                while(grammarOptionIndex < chosenDerivationOption->size()){
                    //For each token in the chosen derivation option, parse it and add it as a child to the current node
                    GrammarOption* currentGrammarOption = chosenDerivationOption->at(grammarOptionIndex);
                    currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
                    if(grammar->child_choice_valid(currentGrammarOption->tokenType, currentToken)){
                        //If the current token is a valid first choice for the current grammar option, parse it
                        ParseTreeNode* newChild = new ParseTreeNode(currentGrammarOption->tokenType);
                        currentTokenIndex = parse_node(newChild, scannerParams, encounteredTokens, currentTokenIndex, grammar);
                        node->add_child(newChild);
                        if(currentGrammarOption->optionType != ARRAY_C){
                            grammarOptionIndex++;
                        }
                    }
                    else if(currentGrammarOption->optionType == ARRAY_C || currentGrammarOption->optionType == OPTIONAL_C){
                        //If a mismatch occurs with an array or optional grammar option, then just advance to the next grammar option
                        grammarOptionIndex++;
                    }
                    else{
                        //
                        throw NoValidDerivationsException();
                    }
                }

                return currentTokenIndex;
            }
        }

        throw NoValidDerivationsException();
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
        grammar->build_grammar();
        encounteredTokens.push_back(scan(scannerParams));
        encounteredTokens.push_back(scan(scannerParams));
        parse_node(parsedTree->rootNode, scannerParams, &encounteredTokens, 0, grammar);
};
