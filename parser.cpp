#include <vector>
#include <iostream>
#include "types/production_option.h"
#include "parser.h"

std::vector<ProductionOption>* get_production_options(TokenType type){
    std::vector<ProductionOption>* options = new std::vector<ProductionOption>;
    ProductionOption option1;
    ProductionOption option2;
    ProductionOption option3;
    ProductionOption option4;
    ProductionOption option5;
    ProductionOption option6;
    ProductionOption option7;
    ProductionOption option8;
    ProductionOption option9;
    switch(type){
        case PROGRAM_NT:
            option1 = ProductionOption({PROGRAM_HEADER_NT, PROGRAM_BODY_NT, PERIOD_T, END_OF_FILE});
            options->push_back(option1);
            break;
        case PROGRAM_HEADER_NT:
            option1 = ProductionOption({PROGRAM_T, IDENTIFIER_NT, IS_T});
            options->push_back(option1);
            break;
        case PROGRAM_BODY_NT:
            option1 = ProductionOption({DECLARATION_ARRAY_NT, BEGIN_T, STATEMENT_ARRAY_NT, END_T, PROGRAM_T});
            options->push_back(option1);
            break;
        case DECLARATION_ARRAY_NT:
            option1 = ProductionOption({DECLARATION_NT, SEMICOLON_T, DECLARATION_ARRAY_NT});
            options->push_back(option1);
            option2 = ProductionOption({DECLARATION_NT, SEMICOLON_T});
            options->push_back(option2);
            break;
        case STATEMENT_ARRAY_NT:
            option1 = ProductionOption({STATEMENT_NT, SEMICOLON_T, STATEMENT_ARRAY_NT});
            options->push_back(option1);
            option2 = ProductionOption({STATEMENT_NT, SEMICOLON_T});
            options->push_back(option2);
            break;
        case DECLARATION_NT:
            option1 = ProductionOption({GLOBAL_T, PROCEDURE_DECLARATION_NT});
            options->push_back(option1);
            option2 = ProductionOption({PROCEDURE_DECLARATION_NT});
            options->push_back(option2);
            option3 = ProductionOption({GLOBAL_T, VARIABLE_DECLARATION_NT});
            options->push_back(option3);
            option4 = ProductionOption({VARIABLE_DECLARATION_NT});
            options->push_back(option4);
            break;
        case PROCEDURE_DECLARATION_NT:
            option1 = ProductionOption({PROCEDURE_HEADER_NT, PROCEDURE_BODY_NT});
            options->push_back(option1);
            break;
        case PROCEDURE_HEADER_NT:
            option1 = ProductionOption({PROCEDURE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_PARENTHESIS_T, PARAMETER_LIST_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            option2 = ProductionOption({PROCEDURE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_PARENTHESIS_T, CLOSE_PARENTHESIS_T});
            options->push_back(option2);
            break;
        case PARAMETER_LIST_NT:
            option1 = ProductionOption({PARAMETER_NT, COMMA_T, PARAMETER_LIST_NT});
            options->push_back(option1);
            option2 = ProductionOption({PARAMETER_NT});
            options->push_back(option2);
            break;
        case PARAMETER_NT:
            option1 = ProductionOption({VARIABLE_DECLARATION_NT});
            options->push_back(option1);
            break;
        case PROCEDURE_BODY_NT:
            option1 = ProductionOption({DECLARATION_ARRAY_NT, BEGIN_T, STATEMENT_ARRAY_NT, END_T, PROCEDURE_T});
            options->push_back(option1);
            break;
        case VARIABLE_DECLARATION_NT:
            option1 = ProductionOption({VARIABLE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_BRACKET_T, BOUND_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            option2 = ProductionOption({VARIABLE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT});
            options->push_back(option2);
            break;
        case TYPE_MARK_NT:
            option1 = ProductionOption({INTEGER_T});
            options->push_back(option1);
            option2 = ProductionOption({FLOAT_T});
            options->push_back(option2);
            option3 = ProductionOption({STRING_T});
            options->push_back(option3);
            option4 = ProductionOption({BOOL_T});
            options->push_back(option4);
            break;
        case BOUND_NT:
            option1 = ProductionOption({NUMBER_NT});
            options->push_back(option1);
            break;
        case STATEMENT_NT:
            option1 = ProductionOption({ASSIGNMENT_STATEMENT_NT});
            options->push_back(option1);
            option2 = ProductionOption({IF_STATEMENT_NT});
            options->push_back(option2);
            option3 = ProductionOption({LOOP_STATEMENT_NT});
            options->push_back(option3);
            option4 = ProductionOption({RETURN_STATEMENT_NT});
            options->push_back(option4);
        case PROCEDURE_CALL_NT:
            option1 = ProductionOption({IDENTIFIER_NT, OPEN_PARENTHESIS_T, ARGUMENT_LIST_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            option2 = ProductionOption({IDENTIFIER_NT, OPEN_PARENTHESIS_T, CLOSE_PARENTHESIS_T});
            options->push_back(option2);
            break;
        case ASSIGNMENT_STATEMENT_NT:
            option1 = ProductionOption({DESTINATION_NT, ASSIGNMENT_OP_T, EXPRESSION_NT});
            options->push_back(option1);
            break;
        case DESTINATION_NT:
            option1 = ProductionOption({IDENTIFIER_NT, OPEN_BRACKET_T, EXPRESSION_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            option2 = ProductionOption({IDENTIFIER_NT});
            options->push_back(option2);
            break;
        case IF_STATEMENT_NT:
            option1 = ProductionOption({IF_T, OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T, 
                THEN_T, STATEMENT_ARRAY_NT, END_T, IF_T});
            options->push_back(option1);
            option2 = ProductionOption({IF_T, OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T, 
                THEN_T, STATEMENT_ARRAY_NT, ELSE_T, STATEMENT_ARRAY_NT, END_T, IF_T});
            options->push_back(option2);
            break;
        case LOOP_STATEMENT_NT:
            option1 = ProductionOption({FOR_T, OPEN_PARENTHESIS_T, ASSIGNMENT_STATEMENT_NT, SEMICOLON_T, 
            EXPRESSION_NT, CLOSE_PARENTHESIS_T, STATEMENT_ARRAY_NT, END_T, FOR_T});
            options->push_back(option1);
            break;
        case RETURN_STATEMENT_NT:
            option1 = ProductionOption({RETURN_T, EXPRESSION_NT});
            options->push_back(option1);
            break;
        case EXPRESSION_NT:
            option1 = ProductionOption({NOT_OP_T, ARITH_OP_NT, EXPRESSION_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({ARITH_OP_NT, EXPRESSION_RECURSE_NT});
            options->push_back(option2);
            option3 = ProductionOption({NOT_OP_T, ARITH_OP_NT});
            options->push_back(option3);
            option4 = ProductionOption({ARITH_OP_NT});
            options->push_back(option4);
            break;
        case EXPRESSION_RECURSE_NT:
            option1 = ProductionOption({AND_OP_T, ARITH_OP_NT});
            options->push_back(option1);
            option2 = ProductionOption({OR_OP_T, ARITH_OP_NT});
            options->push_back(option3);
            break;
        case ARITH_OP_NT:
            option1 = ProductionOption({RELATION_NT, ARITH_OP_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({RELATION_NT});
            options->push_back(option2);
            break;
        case ARITH_OP_RECURSE_NT:
            option1 = ProductionOption({PLUS_OP_T, RELATION_NT, ARITH_OP_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({MINUS_OP_T, RELATION_NT, ARITH_OP_RECURSE_NT});
            options->push_back(option2);
        case RELATION_NT:
            option1 = ProductionOption({TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({TERM_NT});
            options->push_back(option2);
            break;
        case RELATION_RECURSE_NT:
            option1 = ProductionOption({LESSTHAN_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({GREATER_EQUAL_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option2);
            option3 = ProductionOption({LESS_EQUAL_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option3);
            option4 = ProductionOption({GREATERTHAN_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option4);
            option5 = ProductionOption({EQUALITY_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option5);
            option6 = ProductionOption({INEQUALITY_OP_T, TERM_NT, RELATION_RECURSE_NT});
            options->push_back(option6);
            break;
        case TERM_NT:
            option1 = ProductionOption({FACTOR_NT, TERM_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({FACTOR_NT});
            options->push_back(option2);
            break;
        case TERM_RECURSE_NT:
            option1 = ProductionOption({MULTIPLY_OP_T, FACTOR_NT, TERM_RECURSE_NT});
            options->push_back(option1);
            option2 = ProductionOption({DIVIDE_OP_T, FACTOR_NT, TERM_RECURSE_NT});
            options->push_back(option2);
            break;
        case FACTOR_NT:
            option1 = ProductionOption({OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            option2 = ProductionOption({PROCEDURE_CALL_NT});
            options->push_back(option2);
            option3 = ProductionOption({MINUS_OP_T, NAME_NT});
            options->push_back(option3);
            option4 = ProductionOption({NAME_NT});
            options->push_back(option4);
            option5 = ProductionOption({MINUS_OP_T, NUMBER_NT});
            options->push_back(option5);
            option6 = ProductionOption({NUMBER_NT});
            options->push_back(option6);
            option7 = ProductionOption({STRING_NT});
            options->push_back(option7);
            option8 = ProductionOption({TRUE_T});
            options->push_back(option8);
            option9 = ProductionOption({FALSE_T});
            options->push_back(option9);
            break;
        case NAME_NT:
            option1 = ProductionOption({IDENTIFIER_NT, OPEN_BRACKET_T, EXPRESSION_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            option2 = ProductionOption({IDENTIFIER_NT});
            options->push_back(option2);
            break;
        case ARGUMENT_LIST_NT:
            option1 = ProductionOption({EXPRESSION_NT, COMMA_T, ARGUMENT_LIST_NT});
            options->push_back(option1);
            option2 = ProductionOption({EXPRESSION_NT});
            options->push_back(option2);
            break;
        case STRING_NT:
            option1 = ProductionOption({QUOTE_T, STRING_LITERAL_NT, QUOTE_T});
            options->push_back(option1);

        default:
            break;
    }

    return options;
}

int parse_node(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams);

bool check_if_number(std::string tokenString){
    std::string::const_iterator it = tokenString.begin();
    bool decimalEncountered = false;
    while (it != tokenString.end()){
        if(*it == '.'){
            if(decimalEncountered == true){
                return false;
            }
            else{
                decimalEncountered = true;
            }
        }
        else if(isdigit(*it)){
            it++;
        }
        else{
            return false;
        }
    }
    return true;
}

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

ProductionOption choose_production(std::vector<ProductionOption>* productionOptions, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex, int failedAttempts,
    struct ScannerParams* scannerParams){
        //If only one option, no choice but to return it
        if(productionOptions->size() == 1){
            //std::cout<<"Only one production option. \n";
            return productionOptions->at(0);
        }
        else{
            //Get current token and lookahead token
            Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
            Token* lookaheadToken = get_token_at_index(encounteredTokens, currentTokenIndex+1, scannerParams);
            //See how many options have a first token which matches the current token
            std::vector<int> matchIndexes;
            for(int i=0; i<productionOptions->size(); i++){
                if(productionOptions->at(i).tokens.at(0) == currentToken->type){
                    //std::cout<<"Single token match found at option index " << std::to_string(i)<<"\n";
                    matchIndexes.push_back(i);
                }
            }
            //If only one option is found which matches the first token, return it
            if(matchIndexes.size() == 0){
                return productionOptions->at(failedAttempts);
            }
            else if(matchIndexes.size() == 1){
                //std::cout<<"Only one option matches the first token. \n";
                return productionOptions->at(matchIndexes[0]);
            }
            else{
                //Check how many of those options match the second token as well
                std::vector<int> doubleMatchIndexes;
                for(int i=0; i<matchIndexes.size(); i++){
                    int matchIndex = matchIndexes[i];
                    if(productionOptions->at(matchIndex).tokens.size() > 1){
                        if(productionOptions->at(matchIndex).tokens.at(1) == lookaheadToken->type){
                            //std::cout<<"Double token match found at option index " << std::to_string(matchIndex)<<"\n";
                            doubleMatchIndexes.push_back(matchIndex);
                        }
                    }

                }
                if(doubleMatchIndexes.size() == 0){
                    return productionOptions->at(matchIndexes[failedAttempts]);
                }
                //If only one double match, return it
                else if(doubleMatchIndexes.size() == 1){
                    //std::cout<<"Only one option matches two tokens. \n";
                    return productionOptions->at(doubleMatchIndexes[0]);
                }
                else{
                    //If more than one double match, return the nth match based on the number of failed attempts
                    //std::cout<<"Multiple options match both tokens. Returning the one at index "<< std::to_string(doubleMatchIndexes[failedAttempts])<<"\n";
                    return productionOptions->at(doubleMatchIndexes[failedAttempts]);
                }
            }
            //If there are no matches, return the nth option based on the number of failed attempts

            //std::cout<<"No matches found. \n";
            return productionOptions->at(failedAttempts);
        }

}

int parse_terminal(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams){ 
        //Check that the node being processed matches the current token
        Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
        if(node->type != currentToken->type){
            std::cout<<"Terminal mismatch. " << TokenTools::token_type_to_string(currentToken->type) << 
            " is not " << TokenTools::token_type_to_string(node->type) << "\n";
            throw TerminalMismatchException();
        }
        else{
            std::cout<<"Terminal matches. \n";
            return currentTokenIndex;
        }
}

int parse_identifier(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams){ 
        Token* currentToken = get_token_at_index(encounteredTokens, currentTokenIndex, scannerParams);
        node->data = currentToken->tokenString;
        std::cout<<"Processed identifier " << currentToken->tokenString << "\n";
        return currentTokenIndex;
}

int try_production_option(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams, ProductionOption optionToTry){
        //Populate Children
        for(int i=0; i<optionToTry.tokens.size(); i++){
            ParseTreeNode* newNode = new ParseTreeNode(optionToTry.tokens[i]);
            node->add_child(newNode);
        }
        //Parse each child
        for(int i=0; i<node->get_children_count(); i++){
            currentTokenIndex = parse_node(node->get_child(i), encounteredTokens, currentTokenIndex, scannerParams);
            if(i < node->get_children_count() - 1){
                std::cout<<"Advancing to next token. \n";
                currentTokenIndex++;
            }

        }
        return currentTokenIndex;
}

int parse_nonterminal(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams){ 
        std::vector<ProductionOption>* productionOptions = get_production_options(node->type);
        int failedAttempts = 0;
        while(failedAttempts < productionOptions->size()){
            ProductionOption optionToTry = choose_production(productionOptions, 
                encounteredTokens, currentTokenIndex, failedAttempts, scannerParams);
            std::cout<<"Node of type " << TokenTools::token_type_to_string(node->type) << " is trying ";
            optionToTry.print_tokens_in_option();
            try{
                return try_production_option(node, encounteredTokens, currentTokenIndex, scannerParams, optionToTry);
            }
            catch(TerminalMismatchException e){
                std::cout<<"Incrementing failed attempts on node with type " << TokenTools::token_type_to_string(node->type) << "\n";
                node->delete_children();
                failedAttempts++;
            }
            catch(NoValidDerivationsException e){
                std::cout<<"Incrementing failed attempts on node with type " << TokenTools::token_type_to_string(node->type) << "\n";
                node->delete_children();
                failedAttempts++;
            }
        }
        std::cout<<"No valid derivations. \n";
        throw NoValidDerivationsException();
}

int parse_node(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, struct ScannerParams* scannerParams){
        std::cout<<"Parsing node of type " << TokenTools::token_type_to_string(node->type) << 
        ". Current token index is " << std::to_string(currentTokenIndex) << "\n";
        std::cout<<"Made it to line "<<std::to_string(scannerParams->file->get_line_count())<<"\n";
        if(node->type == NAME_NT){
            std::cout<<"Here";
        }
        if(node->type < 42){
            return parse_terminal(node, encounteredTokens, currentTokenIndex, scannerParams);
        }
        else if(node->type == IDENTIFIER_NT){
            return parse_identifier(node, encounteredTokens, currentTokenIndex, scannerParams);
        }
        else{
            return parse_nonterminal(node, encounteredTokens, currentTokenIndex, scannerParams);
        }
};

ParseTree* parse_file(struct ScannerParams* scannerParams){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        std::vector<Token*> encounteredTokens;
        encounteredTokens.push_back(scan(scannerParams));
        encounteredTokens.push_back(scan(scannerParams));
        try{
            parse_node(parsedTree->rootNode, &encounteredTokens, 0, scannerParams);
        }
        catch(EndOfFileException e){
            std::cout<<"Made it to end of file. Parsed " << std::to_string(scannerParams->file->get_line_count()) << " lines. \n";
        }
};
