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
            option1 = ProductionOption({ARITH_OP_NT, PLUS_OP_T, RELATION_NT});
            options->push_back(option1);
            option2 = ProductionOption({ARITH_OP_NT, MINUS_OP_T, RELATION_NT});
            options->push_back(option2);
            option3 = ProductionOption({RELATION_NT});
            options->push_back(option3);
            break;
        case RELATION_NT:
            option1 = ProductionOption({RELATION_NT, LESSTHAN_OP_T, TERM_NT});
            options->push_back(option1);
            option2 = ProductionOption({RELATION_NT, GREATER_EQUAL_OP_T, TERM_NT});
            options->push_back(option2);
            option3 = ProductionOption({RELATION_NT, LESS_EQUAL_OP_T, TERM_NT});
            options->push_back(option3);
            option4 = ProductionOption({RELATION_NT, GREATERTHAN_OP_T, TERM_NT});
            options->push_back(option4);
            option5 = ProductionOption({RELATION_NT, EQUALITY_OP_T, TERM_NT});
            options->push_back(option5);
            option6 = ProductionOption({RELATION_NT, INEQUALITY_OP_T, TERM_NT});
            options->push_back(option6);
            option7 = ProductionOption({TERM_NT});
            options->push_back(option7);
            break;
        case TERM_NT:
            option1 = ProductionOption({TERM_NT, MULTIPLY_OP_T, FACTOR_NT});
            options->push_back(option1);
            option2 = ProductionOption({TERM_NT, DIVIDE_OP_T, FACTOR_NT});
            options->push_back(option2);
            option3 = ProductionOption({FACTOR_NT});
            options->push_back(option3);
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

Token* get_token_at_current_index(std::vector<Token*>* encounteredTokens, int currentTokenIndex,
    InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter){

        Token* currentToken;
        try{
            currentToken = encounteredTokens->at(currentTokenIndex);
        }
        catch(std::out_of_range e){
            encounteredTokens->push_back(scan(file, symbolTable, commentStatus, errorReporter));
            currentToken = encounteredTokens->at(currentTokenIndex);
        }
        return currentToken;

}

ProductionOption choose_production(std::vector<ProductionOption>* productionOptions, 
    std::vector<Token*>* encounteredTokens, int currentTokenIndex, int failedAttempts,
    InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter){
        if(productionOptions->size() == 1){
            return productionOptions->at(0);
        }
        else{
            Token* currentToken = get_token_at_current_index(encounteredTokens, currentTokenIndex, file, symbolTable,
                commentStatus, errorReporter);
            Token* lookaheadToken = get_token_at_current_index(encounteredTokens, currentTokenIndex+1, file, symbolTable,
                commentStatus, errorReporter);
           for(int i=0; i<productionOptions->size(); i++){
                if(productionOptions->at(i).tokens.at(0) == currentToken->type){
                        if(productionOptions->at(i).tokens.size() == 1){
                            return productionOptions->at(i);
                        }
                        else if(productionOptions->at(i).tokens.at(1) == lookaheadToken->type){
                            return productionOptions->at(i);
                        }
                    }
           }
           return productionOptions->at(failedAttempts);
        }

}

void parse_node(ParseTreeNode* node, std::vector<Token*>* encounteredTokens, 
    int currentTokenIndex, InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter){
        std::cout<<"Parsing node of type "<<TokenTools::token_type_to_string(node->type)<<"\n";
        //std::cout<<"Made it to line "<< std::to_string(file->get_line_count()) <<"\n";
        Token* currentToken = get_token_at_current_index(encounteredTokens, currentTokenIndex,
                file, symbolTable, commentStatus,errorReporter);
        if(currentToken->type == END_OF_FILE){
            std::cout<<"Here";
        }
        //Check if node is terminal.
        if(node->type < 42){
            //Make sure it matches the current token
            if(node->type != currentToken->type){
                throw TerminalMismatchException();
            };
            std::cout<<"Terminal matches current token. \n";
        }
        else if(node->type == IDENTIFIER_NT){
            //If the token is an identifier, set its data to the token string

            node->data = currentToken->tokenString;
            std::cout<<"Processed identifier " << currentToken->tokenString << "\n";
        }
        else if(node-> type == NUMBER_NT){
            std::string tokenString = currentToken->tokenString;
            if(check_if_number(tokenString)){
                node->data = tokenString;
            }
            else{
                throw TerminalMismatchException();
            }
        }
        else if(node->type == STRING_LITERAL_NT){
            node->data = currentToken->tokenString;
        }
        else{
            int failedAttempts = 0;
            std::vector<ProductionOption>* productionOptions = get_production_options(node->type);
            while(failedAttempts < productionOptions->size()){
                try{
                    ProductionOption selectedOption = choose_production(productionOptions, 
                        encounteredTokens, currentTokenIndex, failedAttempts, file, symbolTable,
                        commentStatus, errorReporter);
                    std::cout<<"Chose ";
                    selectedOption.print_tokens_in_option();
                    for(int i=0; i<selectedOption.tokens.size(); i++){
                        ParseTreeNode* newNode = new ParseTreeNode(selectedOption.tokens[i]);
                        node->add_child(newNode);
                    }
                    for(int i=0; i<node->get_children_count(); i++){
                        parse_node(node->get_child(i), encounteredTokens, currentTokenIndex, file, symbolTable,
                            commentStatus, errorReporter);
                        if(i < node->get_children_count() - 1){
                            std::cout<<"Moving to next token. \n";
                            currentTokenIndex++;
                            try{
                                encounteredTokens->at(i);
                            }
                            catch(std::out_of_range e){
                                encounteredTokens->push_back(scan(file, symbolTable, commentStatus, errorReporter));
                            }
                        }
                    }
                    break;
                }
                catch(TerminalMismatchException e){
                    std::cout<<"Terminal mismatch. \n";
                    failedAttempts++;
                }
                catch(NoValidDerivationsException e){
                    std::cout<<"No Valid derivations. \n";
                    failedAttempts++;
                }
            }
        }
};

ParseTree* parse_file(InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        std::vector<Token*> encounteredTokens;
        encounteredTokens.push_back(scan(file, symbolTable, commentStatus, errorReporter));
        encounteredTokens.push_back(scan(file, symbolTable, commentStatus, errorReporter));
        try{
            parse_node(parsedTree->rootNode, &encounteredTokens, 0, file, symbolTable, commentStatus,
                errorReporter);
        }
        catch(EndOfFileException e){
            std::cout<<"Made it to end of file. Parsed " << std::to_string(file->get_line_count()) << " lines. \n";
        }
};
