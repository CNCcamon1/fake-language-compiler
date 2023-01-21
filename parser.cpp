#include <vector>
#include "types/production_option.h"
#include "parser.h"

std::vector<ProductionOption>* get_production_options(TokenType type){
    std::vector<ProductionOption>* options = new std::vector<ProductionOption>;
    switch(type){
        case PROGRAM_NT:
            ProductionOption option1 = ProductionOption({PROGRAM_HEADER_NT, PROGRAM_BODY_NT});
            options->push_back(option1);
            break;
        case PROGRAM_HEADER_NT:
            ProductionOption option1 = ProductionOption({PROGRAM_T, IDENTIFIER_NT, IS_T});
            options->push_back(option1);
            break;
        case PROGRAM_BODY_NT:
            ProductionOption option1 = ProductionOption({DECLARATION_ARRAY_NT, BEGIN_T, STATEMENT_ARRAY_NT, END_T, PROGRAM_T});
            options->push_back(option1);
            break;
        case DECLARATION_ARRAY_NT:
            ProductionOption option1 = ProductionOption({DECLARATION_NT, SEMICOLON_T, DECLARATION_ARRAY_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({DECLARATION_NT, SEMICOLON_T});
            options->push_back(option2);
            break;
        case STATEMENT_ARRAY_NT:
            ProductionOption option1 = ProductionOption({STATEMENT_NT, SEMICOLON_T, STATEMENT_ARRAY_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({STATEMENT_NT, SEMICOLON_T});
            options->push_back(option2);
            break;
        case DECLARATION_NT:
            ProductionOption option1 = ProductionOption({GLOBAL_T, PROCEDURE_DECLARATION_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({PROCEDURE_DECLARATION_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({GLOBAL_T, VARIABLE_DECLARATION_NT});
            options->push_back(option3);
            ProductionOption option4 = ProductionOption({VARIABLE_DECLARATION_NT});
            options->push_back(option4);
            break;
        case PROCEDURE_DECLARATION_NT:
            ProductionOption option1 = ProductionOption({PROCEDURE_HEADER_NT, PROCEDURE_BODY_NT});
            options->push_back(option1);
            break;
        case PROCEDURE_HEADER_NT:
            ProductionOption option1 = ProductionOption({PROCEDURE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_PARENTHESIS_T, PARAMETER_LIST_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({PROCEDURE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_PARENTHESIS_T, CLOSE_PARENTHESIS_T});
            options->push_back(option2);
            break;
        case PARAMETER_LIST_NT:
            ProductionOption option1 = ProductionOption({PARAMETER_NT, COMMA_T, PARAMETER_LIST_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({PARAMETER_NT});
            options->push_back(option2);
            break;
        case PARAMETER_NT:
            ProductionOption option1 = ProductionOption({VARIABLE_DECLARATION_NT});
            options->push_back(option1);
            break;
        case PROCEDURE_BODY_NT:
            ProductionOption option1 = ProductionOption({DECLARATION_ARRAY_NT, BEGIN_T, STATEMENT_ARRAY_NT, END_T, PROCEDURE_T});
            options->push_back(option1);
            break;
        case VARIABLE_DECLARATION_NT:
            ProductionOption option1 = ProductionOption({VARIABLE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT, OPEN_BRACKET_T, BOUND_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({VARIABLE_T, IDENTIFIER_NT, COLON_T, TYPE_MARK_NT});
            options->push_back(option2);
            break;
        case TYPE_MARK_NT:
            ProductionOption option1 = ProductionOption({INTEGER_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({FLOAT_T});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({STRING_T});
            options->push_back(option3);
            ProductionOption option4 = ProductionOption({BOOL_T});
            options->push_back(option4);
            break;
        case BOUND_NT:
            ProductionOption option1 = ProductionOption({NUMBER_NT});
            options->push_back(option1);
            break;
        case STATEMENT_NT:
            ProductionOption option1 = ProductionOption({ASSIGNMENT_STATEMENT_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({IF_STATEMENT_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({LOOP_STATEMENT_NT});
            options->push_back(option3);
            ProductionOption option4 = ProductionOption({RETURN_STATEMENT_NT});
            options->push_back(option4);
        case PROCEDURE_CALL_NT:
            ProductionOption option1 = ProductionOption({IDENTIFIER_NT, OPEN_PARENTHESIS_T, ARGUMENT_LIST_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({IDENTIFIER_NT, OPEN_PARENTHESIS_T, CLOSE_PARENTHESIS_T});
            options->push_back(option2);
            break;
        case ASSIGNMENT_STATEMENT_NT:
            ProductionOption option1 = ProductionOption({DESTINATION_NT, ASSIGNMENT_OP_T, EXPRESSION_NT});
            options->push_back(option1);
            break;
        case DESTINATION_NT:
            ProductionOption option1 = ProductionOption({IDENTIFIER_NT, OPEN_BRACKET_T, EXPRESSION_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({IDENTIFIER_NT});
            options->push_back(option2);
            break;
        case IF_STATEMENT_NT:
            ProductionOption option1 = ProductionOption({IF_T, OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T, 
                THEN_T, STATEMENT_ARRAY_NT, END_T, IF_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({IF_T, OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T, 
                THEN_T, STATEMENT_ARRAY_NT, ELSE_T, STATEMENT_ARRAY_NT, END_T, IF_T});
            options->push_back(option2);
            break;
        case LOOP_STATEMENT_NT:
            ProductionOption option1 = ProductionOption({FOR_T, OPEN_PARENTHESIS_T, ASSIGNMENT_STATEMENT_NT, SEMICOLON_T, 
            EXPRESSION_NT, CLOSE_PARENTHESIS_T, STATEMENT_ARRAY_NT, END_T, FOR_T});
            options->push_back(option1);
            break;
        case RETURN_STATEMENT_NT:
            ProductionOption option1 = ProductionOption({RETURN_T, EXPRESSION_NT});
            options->push_back(option1);
            break;
        case EXPRESSION_NT:
            ProductionOption option1 = ProductionOption({EXPRESSION_NT, AND_OP_T, ARITH_OP_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({EXPRESSION_NT, OR_OP_T, ARITH_OP_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({NOT_OP_T, ARITH_OP_NT});
            options->push_back(option3);
            break;
        case ARITH_OP_NT:
            ProductionOption option1 = ProductionOption({ARITH_OP_NT, PLUS_OP_T, RELATION_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({ARITH_OP_NT, MINUS_OP_T, RELATION_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({RELATION_NT});
            options->push_back(option3);
            break;
        case RELATION_NT:
            ProductionOption option1 = ProductionOption({RELATION_NT, LESSTHAN_OP_T, TERM_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({RELATION_NT, GREATER_EQUAL_OP_T, TERM_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({RELATION_NT, LESS_EQUAL_OP_T, TERM_NT});
            options->push_back(option3);
            ProductionOption option4 = ProductionOption({RELATION_NT, GREATERTHAN_OP_T, TERM_NT});
            options->push_back(option4);
            ProductionOption option5 = ProductionOption({RELATION_NT, EQUALITY_OP_T, TERM_NT});
            options->push_back(option5);
            ProductionOption option6 = ProductionOption({RELATION_NT, INEQUALITY_OP_T, TERM_NT});
            options->push_back(option6);
            ProductionOption option7 = ProductionOption({TERM_NT});
            options->push_back(option7);
            break;
        case TERM_NT:
            ProductionOption option1 = ProductionOption({TERM_NT, MULTIPLY_OP_T, FACTOR_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({TERM_NT, DIVIDE_OP_T, FACTOR_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({FACTOR_NT});
            options->push_back(option3);
            break;
        case FACTOR_NT:
            ProductionOption option1 = ProductionOption({OPEN_PARENTHESIS_T, EXPRESSION_NT, CLOSE_PARENTHESIS_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({PROCEDURE_CALL_NT});
            options->push_back(option2);
            ProductionOption option3 = ProductionOption({MINUS_OP_T, NAME_NT});
            options->push_back(option3);
            ProductionOption option4 = ProductionOption({NAME_NT});
            options->push_back(option4);
            ProductionOption option5 = ProductionOption({MINUS_OP_T, NUMBER_NT});
            options->push_back(option5);
            ProductionOption option6 = ProductionOption({NUMBER_NT});
            options->push_back(option6);
            ProductionOption option7 = ProductionOption({STRING_NT});
            options->push_back(option7);
            ProductionOption option8 = ProductionOption({TRUE_T});
            options->push_back(option8);
            ProductionOption option9 = ProductionOption({FALSE_T});
            options->push_back(option9);
            break;
        case NAME_NT:
            ProductionOption option1 = ProductionOption({IDENTIFIER_NT, OPEN_BRACKET_T, EXPRESSION_NT, CLOSE_BRACKET_T});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({IDENTIFIER_NT});
            options->push_back(option2);
            break;
        case ARGUMENT_LIST_NT:
            ProductionOption option1 = ProductionOption({EXPRESSION_NT, COMMA_T, ARGUMENT_LIST_NT});
            options->push_back(option1);
            ProductionOption option2 = ProductionOption({EXPRESSION_NT});
            options->push_back(option2);
            break;
        default:
            break;
    }

    return options;
}

ProductionOption choose_production(std::vector<ProductionOption>* productionOptions, 
    Token* currentToken, Token* lookaheadToken){


}

ParseTreeNode* parse_node(ParseTreeNode* node, 
    InFile* file, SymbolTable* symbolTable, CommentStatus* commentStatus, 
    ErrorReporter* errorReporter){

    //Get the list of possible productions based on the node type
    std::vector<ProductionOption>* productionOptions = get_production_options(node->type);
    //Get the current token and lookahead token, and use them to choose a possible production
    Token* currentToken = nextToken;
    Token* lookaheadToken = scan(file, symbolTable, commentStatus, errorReporter);

    ProductionOption chosenProduction = choose_production(productionOptions, currentToken, lookaheadToken);
    //Create nodes for the children (based on the production selected)
    for(int i=0; i<chosenProduction.tokens.size(); i++){
        ParseTreeNode* childNode = new ParseTreeNode(chosenProduction.tokens[i]);
        node->add_child(childNode);
    }
    //Go through the children and parse them, recursively
    for(int i=0; i<node->get_children_count(); i++){
        parse_node(node->get_child(i), )
    }

}

ParseTree* parse_file(InFile* file, SymbolTable* symbolTable, 
    CommentStatus* commentStatus, ErrorReporter* errorReporter){

        ParseTree* parsedTree = new ParseTree(new ParseTreeNode(PROGRAM_NT));
        Token* lookaheadToken = scan(file, symbolTable, commentStatus, errorReporter);
        parsedTree->rootNode = parse_node(parsedTree->rootNode, lookaheadToken, 
            file, symbolTable, commentStatus, errorReporter);



};
